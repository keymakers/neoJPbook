package main

import (
	"bytes"
	"crypto/rand"
	"crypto/sha256"
	"encoding/hex"
	"errors"
	"fmt"
	"golang.org/x/crypto/ripemd160"
	"io"
	"log"
	"math/big"
)

type (
	// EllipticCurve represents the parameters of a short Weierstrass equation elliptic
	// curve.
	EllipticCurve struct {
		A *big.Int
		B *big.Int
		P *big.Int
		G ECPoint
		N *big.Int
		H *big.Int
	}

	// ECPoint represents a point on the EllipticCurve.
	ECPoint struct {
		X *big.Int
		Y *big.Int
	}
)

type PrivateKey struct {
	b []byte
}

func main() {
	//ランダムなプライベートキーの生成
	privateKey, err := NewPrivateKey()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(hex.EncodeToString(privateKey.b))

	//プライベートキーからアドレスの生成
	//1. PrivateKey→PublicKey
	//2. PublicKeyHashの生成（20byteに圧縮）
	//3. versionの追加
	//4. checksumの追加
	//5. base58でエンコード
	address, err := privateKey.Address()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println(address)
}

func NewPrivateKey() (*PrivateKey, error) {
	c := NewEllipticCurve()
	b := make([]byte, c.N.BitLen()/8+8)
	if _, err := io.ReadFull(rand.Reader, b); err != nil {
		return nil, err
	}

	d := new(big.Int).SetBytes(b)
	d.Mod(d, new(big.Int).Sub(c.N, big.NewInt(1)))
	d.Add(d, big.NewInt(1))

	p := &PrivateKey{b: d.Bytes()}
	return p, nil
}

// NewEllipticCurve returns a ready to use EllipticCurve with preconfigured
// fields for the NEO protocol.
func NewEllipticCurve() EllipticCurve {
	c := EllipticCurve{}

	c.P, _ = new(big.Int).SetString(
		"FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF", 16,
	)
	c.A, _ = new(big.Int).SetString(
		"FFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC", 16,
	)
	c.B, _ = new(big.Int).SetString(
		"5AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B", 16,
	)
	c.G.X, _ = new(big.Int).SetString(
		"6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296", 16,
	)
	c.G.Y, _ = new(big.Int).SetString(
		"4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5", 16,
	)
	c.N, _ = new(big.Int).SetString(
		"FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551", 16,
	)
	c.H, _ = new(big.Int).SetString("01", 16)

	return c
}

// Address derives the public NEO address that is coupled with the private key, and
// returns it as a string.
func (p *PrivateKey) Address() (string, error) {
	b, err := p.Signature()
	if err != nil {
		return "", err
	}

	b = append([]byte{0x17}, b...)

	sha := sha256.New()
	sha.Write(b)
	hash := sha.Sum(nil)

	sha.Reset()
	sha.Write(hash)
	hash = sha.Sum(nil)

	b = append(b, hash[0:4]...)

	address := Base58Encode(b)

	return address, nil
}

// Signature creates the signature using the private key.
func (p *PrivateKey) Signature() ([]byte, error) {
	b, err := p.PublicKey()
	if err != nil {
		return nil, err
	}

	b = append([]byte{0x21}, b...)
	b = append(b, 0xAC)

	sha := sha256.New()
	sha.Write(b)
	hash := sha.Sum(nil)

	ripemd := ripemd160.New()
	ripemd.Reset()
	ripemd.Write(hash)
	hash = ripemd.Sum(nil)

	return hash, nil
}

// PublicKey derives the public key from the private key.
func (p *PrivateKey) PublicKey() ([]byte, error) {
	var (
		c = NewEllipticCurve()
		q = new(big.Int).SetBytes(p.b)
	)

	point := c.ScalarBaseMult(q)
	if !c.IsOnCurve(point) {
		return nil, errors.New("failed to derive public key using elliptic curve")
	}

	bx := point.X.Bytes()
	padded := append(
		bytes.Repeat(
			[]byte{0x00},
			32-len(bx),
		),
		bx...,
	)

	prefix := []byte{0x03}
	if point.Y.Bit(0) == 0 {
		prefix = []byte{0x02}
	}
	b := append(prefix, padded...)

	return b, nil
}

// Base58Encode encodes a byte slice to be a base58 encoded string.
func Base58Encode(bytes []byte) string {
	var (
		lookupTable = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"
		x           = new(big.Int).SetBytes(bytes)
		r           = new(big.Int)
		m           = big.NewInt(58)
		zero        = big.NewInt(0)
		encoded     string
	)

	for x.Cmp(zero) > 0 {
		x.QuoRem(x, m, r)
		encoded = string(lookupTable[r.Int64()]) + encoded
	}

	return encoded
}

// ScalarBaseMult computes Q = k * G on EllipticCurve ec.
func (c *EllipticCurve) ScalarBaseMult(k *big.Int) (Q ECPoint) {
	return c.ScalarMult(k, c.G)
}

// ScalarMult computes Q = k * P on EllipticCurve ec.
func (c *EllipticCurve) ScalarMult(k *big.Int, P ECPoint) (Q ECPoint) {
	// Implementation based on pseudocode here:
	// https://en.wikipedia.org/wiki/Elliptic_curve_point_multiplication#Montgomery_ladder
	var R0 ECPoint
	var R1 ECPoint

	R0.X = nil
	R0.Y = nil
	R1.X = new(big.Int).Set(P.X)
	R1.Y = new(big.Int).Set(P.Y)

	for i := c.N.BitLen() - 1; i >= 0; i-- {
		if k.Bit(i) == 0 {
			R1 = c.Add(R0, R1)
			R0 = c.Add(R0, R0)
		} else {
			R0 = c.Add(R0, R1)
			R1 = c.Add(R1, R1)
		}
	}
	return R0
}

// IsOnCurve checks if point P is on EllipticCurve ec.
func (c *EllipticCurve) IsOnCurve(P ECPoint) bool {
	if c.IsInfinity(P) {
		return false
	}
	lhs := mulMod(P.Y, P.Y, c.P)
	rhs := addMod(
		addMod(
			expMod(P.X, big.NewInt(3), c.P),
			mulMod(c.A, P.X, c.P), c.P),
		c.B, c.P)

	if lhs.Cmp(rhs) == 0 {
		return true
	}
	return false
}

// IsInfinity checks if point P is infinity on EllipticCurve ec.
func (c *EllipticCurve) IsInfinity(P ECPoint) bool {
	return P.X == nil && P.Y == nil
}

// addMod computes z = (x + y) % p.
func addMod(x *big.Int, y *big.Int, p *big.Int) (z *big.Int) {
	z = new(big.Int).Add(x, y)
	z.Mod(z, p)
	return z
}

// subMod computes z = (x - y) % p.
func subMod(x *big.Int, y *big.Int, p *big.Int) (z *big.Int) {
	z = new(big.Int).Sub(x, y)
	z.Mod(z, p)
	return z
}

// mulMod computes z = (x * y) % p.
func mulMod(x *big.Int, y *big.Int, p *big.Int) (z *big.Int) {
	n := new(big.Int).Set(x)
	z = big.NewInt(0)

	for i := 0; i < y.BitLen(); i++ {
		if y.Bit(i) == 1 {
			z = addMod(z, n, p)
		}
		n = addMod(n, n, p)
	}

	return z
}

// expMod computes z = (x^e) % p.
func expMod(x *big.Int, y *big.Int, p *big.Int) (z *big.Int) {
	z = new(big.Int).Exp(x, y, p)
	return z
}

// invMod computes z = (1/x) % p.
func invMod(x *big.Int, p *big.Int) (z *big.Int) {
	z = new(big.Int).ModInverse(x, p)
	return z
}

// Add computes R = P + Q on EllipticCurve ec.
func (c *EllipticCurve) Add(P, Q ECPoint) (R ECPoint) {
	// See rules 1-5 on SEC1 pg.7 http://www.secg.org/collateral/sec1_final.pdf
	if c.IsInfinity(P) && c.IsInfinity(Q) {
		R.X = nil
		R.Y = nil
	} else if c.IsInfinity(P) {
		R.X = new(big.Int).Set(Q.X)
		R.Y = new(big.Int).Set(Q.Y)
	} else if c.IsInfinity(Q) {
		R.X = new(big.Int).Set(P.X)
		R.Y = new(big.Int).Set(P.Y)
	} else if P.X.Cmp(Q.X) == 0 && addMod(P.Y, Q.Y, c.P).Sign() == 0 {
		R.X = nil
		R.Y = nil
	} else if P.X.Cmp(Q.X) == 0 && P.Y.Cmp(Q.Y) == 0 && P.Y.Sign() != 0 {
		num := addMod(
			mulMod(big.NewInt(3),
				mulMod(P.X, P.X, c.P), c.P),
			c.A, c.P)
		den := invMod(mulMod(big.NewInt(2), P.Y, c.P), c.P)
		lambda := mulMod(num, den, c.P)
		R.X = subMod(
			mulMod(lambda, lambda, c.P),
			mulMod(big.NewInt(2), P.X, c.P),
			c.P)
		R.Y = subMod(
			mulMod(lambda, subMod(P.X, R.X, c.P), c.P),
			P.Y, c.P)
	} else if P.X.Cmp(Q.X) != 0 {
		num := subMod(Q.Y, P.Y, c.P)
		den := invMod(subMod(Q.X, P.X, c.P), c.P)
		lambda := mulMod(num, den, c.P)
		R.X = subMod(
			subMod(
				mulMod(lambda, lambda, c.P),
				P.X, c.P),
			Q.X, c.P)
		R.Y = subMod(
			mulMod(lambda,
				subMod(P.X, R.X, c.P), c.P),
			P.Y, c.P)
	} else {
		panic(fmt.Sprintf("Unsupported point addition: %v + %v", P, Q))
	}

	return R
}
