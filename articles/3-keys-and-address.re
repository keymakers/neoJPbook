= キー、アドレス
#@# 担当者:@EG-easy

//lead{
この章では、前半に公開鍵暗号方式や楕円曲線暗号といった暗号技術の基本を説明するとともに、後半では実際にNEOのアドレス生成の過程をコードベースで辿っていき、よりNEOのアドレスへの理解を深められるように解説していきます。
//}

== 公開鍵暗号
公開鍵暗号は、秘密鍵と公開鍵という2つの鍵を使った暗号のことで、1つの鍵を使う共通鍵暗号@<fn>{common-key}と対をなす暗号技術です。
秘密鍵は自分以外に知られないようにし、公開鍵はオープンにしても問題ない暗号方式です。代表的なものにRSA暗号が挙げられます。
また、通信を暗号化するSSLは公開鍵暗号と共通鍵暗号の両方を利用しています。

公開鍵暗号は次の性質を持ちます。

 * 公開鍵で暗号化した文は秘密鍵のみで復号可能
 * 秘密鍵で暗号化した文は公開鍵のみで復号可能（出来ない公開鍵暗号も存在）
 * 秘密鍵から公開鍵を知ることが可能、公開鍵から秘密鍵を知ることは不可能
 * 秘密鍵でサインした文は公開鍵で本人が作成した文であると証明可能（デジタル署名）

 以上の性質をもつ公開鍵暗号ですが、暗号通貨ではアドレスの作成とアドレスをもつ本人である証明（デジタル署名）に使われます。
 デジタル署名は、主に暗号通貨の送金時に本人が送金した証明に使われます。
 デジタル署名がないと、第三者が誰かの暗号通貨を不正に送金し放題になり通貨として機能しません。

//footnote[common-key][共通鍵暗号は送信者と受信者が共通の鍵を持ち合うことにより秘密通信を行う方式のこと。厳密に分類するとブロックごとに暗号化するブロック暗号と、乱数を用いるストリーム暗号に分けられる。]

暗号通貨ではBitcoinの慣例に倣い楕円曲線デジタル署名アルゴリズムECDSA（Elliptic Curve Digital Signature Algorithm）が用いられることが多いです。

== ハッシュ
次に、暗号化技術を知る上で欠かせない知識であるハッシュについてみていきます。
平文全体に対して秘密鍵で暗号化⇒公開鍵で復号化という処理をすると、平文が長大であるほど演算に時間が掛かってしまい、実用的ではなくなってしまいます。
そこでハッシュ関数を利用し、平文を一定の長さに変換してから署名する仕組みが一般的になっています。
ハッシュはあらゆる入力データから固定長の小さな出力値を一意に求める仕組みのことを指し、この仕組みで得られた出力値をハッシュ値と言います。
代表的なものにMD5やSHA-1があります。
ハッシュの主な用途は受信したデータの破損や改ざんの検証や公開鍵暗号のデジタル署名です。
他にも、パスワードをデータベースに保存するときも普通はパスワードにハッシュを施してから保存します。
ハッシュは次の性質を持ちます。

 * あらゆる長さの入力データから固定長のハッシュ値を出力する
 * 同じ入力データからは必ず同じハッシュ値が得られる
 * 似た入力データからでも、まったく違うハッシュ値が得られる
 * ハッシュ値から入力データを求めることは出来ない
 * 違う入力データから同じハッシュ値が出力される（衝突する)ことはほぼあり得ないがごく稀にあり得る
暗号通貨では、お馴染みブロックチェーンやアドレスの作成、取引（トランザクション）の検証、マークルルートの作成そしてマイニングなどさまざまなところで利用されます。

暗号通貨でよく使われるのはSHA-256（出力32byte）やRIPEMD-160（出力20byte）で、あとでNEOのコードをみる時にも実際に現れます。
NEOアドレスは一方向暗号学的ハッシュ化を使うことで公開鍵から生成されます。
暗号学的ハッシュ関数はNEOの中で広範囲に活用されます。

== 秘密鍵
さて、公開鍵暗号とハッシュについての概要がつかめたところで秘密鍵について掘り下げていきます。
秘密鍵は意図的に指定できるものではなく無作為に選ばれる数値です。
秘密鍵による所有権管理はNEOアドレスに結びついた全ての資金の根幹をなします。
秘密鍵は署名を生成するときに使われ、この署名は資金を使うときに所有権の主張に必要となります。
秘密鍵はいつでも極秘に保っておかなければいけません。
もし他者に秘密鍵が漏れると、秘密鍵に対応したNEOアドレスの資金のコントロールを他者に与えることになってしまうためです。
秘密鍵をバックアップをしておくだけでなく、秘密鍵の偶発的な紛失からも保護しておかなければいけません。
というのは、もし秘密鍵をなくしてしまうと、秘密鍵を復元することはできず、秘密鍵によってセキュリティを担保していた資金も永遠に失ってしまうためです。

NEOの秘密鍵は、ランダム性がある256bitの数値で、ある文字列を先ほどのSHA256関数を使って16進数で表現すると次のような4bitずつ64個の16進数で表現されている256bitの整数になります。
//cmd{
936a185caaa266bb9cbe981e9e05cb78cd732b0b3280eb944412bb6f8f8f07af
//}

ちなみに先ほどの秘密鍵の2^4^64bitとは次のように78桁にも及ぶとてつもなく大きな数で、秘密鍵が他人のものと一致するという確率は天文学的に低いといえるでしょう。
//cmd{
2^4^64=1157920892373161954235709850086879078532699846656405640394575840079131296
39936
//}

NEOのネットワーク上では、秘密鍵は、NEOやGasの送信、または、スマートコントラクトのデプロイをする時のトランザクションに署名するのに使われています。
公開鍵と署名生成に使用する秘密鍵は、ある式（後述）に基づいて導き出されており、このときの署名は、秘密鍵を公開することなく、公開鍵に対する正当性を検証できるようになっています。

NEO所有者は、NEOを送信する時に、公開鍵と署名をトランザクションに記載します。NEOネットワークに参加している参加者は、この公開鍵と署名を確認することで、トランザクションを検証し有効なものとみなします。


==[column] 公開鍵と秘密鍵
公開鍵は、秘密鍵から計算できるため、秘密鍵だけ保存しておけばいつでも公開鍵を導き出すことができます。

==[column] 安全な秘密鍵とは
キーを生成する上で重要かつ一番最初にしなればいけないことは、キー生成の安定的なエントロピー源、つまり十分なランダムさを確保することです。
NEOキーを作ることは、"1から 2^256 までの間の数字を選ぶ"ということと本質的に同じです。
数字を選ぶ厳格な方法は、予測可能であったり再現可能性があったりしない方法です。
NEOの秘密鍵は先述したように単なる数値なので、コインや鉛筆、紙だけを使ってランダムに秘密鍵を選ぶことができます。
たとえば、コインを256回投げてNEOウォレットで使うランダムな秘密鍵の二進数を作り出すことができます。
公開鍵はこの秘密鍵から生成することができます。

== 公開鍵の生成
公開鍵暗号では、「秘密鍵から公開鍵を知ることが可能、公開鍵から秘密鍵を知ることは不可能」という特徴をもつ公開鍵をどのように生成するかが大きな課題になります。
そこには、楕円曲線を利用した暗号化の技術が関わっています。

=== 楕円曲線とは
楕円曲線とは次の形の方程式により定義される平面曲線です。
//indepimage[equation][楕円曲線を表した数式]

このa,bの値を変えることで、楕円曲線はさまざまなな曲線の形状になります。
NEOでは、楕円曲線の中でもSecp256r1と呼ばれる楕円曲線を利用しています。
楕円曲線及び楕円曲線を用いた暗号化にはいくつかのパラメータが存在し、Secp256r1はそれらの各パラメーター（a=0, b=7）が決まっています。
//indepimage[Secp256r1][Secp256r1][scale=0.7]

=== 楕円曲線暗号
楕円曲線暗号（（Elliptic Curve Cryptography：ECC））は、楕円曲線上の点に対する加法とスカラー倍算で表現される離散対数問題をベースに作られた
非対称型暗号方式または公開鍵暗号方式です。
もう少し噛み砕いていうと、楕円曲線上の離散対数問題（EC-DLP）の困難性を安全性の根拠とした、楕円曲線を利用した暗号方式のことをさします。
ここでいう離散対数問題とは、素数pと定数gが与えられたとき、y=g^x mod pをxから計算することは容易だが、
yからxを求めることは困難であるということです。

=== 楕円曲線暗号を利用した公開鍵の生成
秘密鍵を、ランダムに生成された数値'k'とすると、あらかじめ決められた生成元'G'を kに掛けることで楕円曲線上のもう1つの点を得ます。
このもう1つの点は公開鍵Kに対応するものです。
次の式では、kを秘密鍵、Gを生成元、Kは結果として算出される公開鍵となります。
//emlist{
K = k * G
//}
ベースポイントのGはsecp256r1標準で決められており、NEOでの全ての公開鍵に対して常に同じです。
したがって、秘密鍵kが同じであれば、公開鍵は同じになります。
また、公開鍵から生成されたNEOアドレスから秘密鍵kを求めることはできないので、アドレスを他人と共有することも可能です。
この公開鍵から秘密鍵に戻すことができないのは、公開鍵生成プロセスが上述したように数学的に一方向になっているためです。

==[column] アドレスと公開鍵
NEOアドレスは公開鍵は同じではありません 。
NEOアドレスは公開鍵から一方向関数を使って導出されるものです。

== Base58とBase58Checkエンコード
ここから先は、生成した公開鍵をアドレスに変換していく過程になります。公開鍵そのものをアドレスとして使うのではなく、人間がみてもわかりやすい形式に変換する作業になります。
多くのコンピュータでは、大きな数字をコンパクトに表すためにいくつかの記号を使うことで10以上を基数とするアルファベットと数字を混ぜた表現を使っています。
たとえば、伝統的な10進数では0から9までの10個の数字を使う一方、16進数ではAからFの文字を使うことで16個の数字を使います。
16進数で表される数字は10進数で表すよりも短くなります。
バイナリデータをemailのようなテキストベースの通信で送るために、Base-64では26個の小文字、26個の大文字、10個の数字、"+"や "/" のような２種類の文字を使います。
Base58はBitcoinで使うために開発されたテキストベースのエンコード形式で、他の暗号通貨でも使われています。
これはコンパクトな表現、可読性、エラー発見および防止のためです。
Base58はBase64の部分集合でアルファベットの大文字小文字、数字が使われます。
しかし、あるフォントで表示したときに同じように見えて、よく間違えてしまういくつかの文字は省かれています。
Base58はBase64から0（数字の0）、O（大文字o）、l（小文字L）、I（大文字i）、記号"+"や"/"を除いたもの、つまり、(0, O, l, I, +, /）を除いたアルファベットの大文字小文字、数字の集合になっています。

書き間違いや転写間違いをさらに防ぐため、Base58Checkはチェックサムを加えたBase58エンコード形式になっていてNEOで頻繁に使われています。
チェックサムは、エンコードされようとしているデータの最後に追加される4byteです。
このチェックサムはエンコードされたデータのハッシュから作られ、転写間違いやタイピング間違いを検出したり防いだりするのに使われます。
Base58Checkでエンコードされたデータが与えられた場合、デコードソフトウェアはエンコードされようとしているデータのチェックサムを計算し、含まれているチェックサムと比較します。
もし2つが一致しなかった場合、これはエラーが混入してしまったかBase58Checkデータが無効だということを示しています。
これによって、たとえば、ウォレットが有効な送り先だと判断して受け付けてしまった打ち間違いNEOアドレスを無効と判断し、資金を失ってしまうということを防ぐことができます。

公開鍵からNEOアドレスを作るときに使うアルゴリズムは、 Secure Hash Algorithm（SHA）と RACE IntegrityPrimitives Evaluation Message Digest（RIPEMD）で、中でも SHA256 と RIPEMD160 が使われます。
公開鍵KのSHA256ハッシュを計算し、さらにこの結果のRIPEMD160ハッシュを計算することで、160bit（20byte）の数字を作り出します。

NEOアドレスは、 "Base58Check" と呼ばれる形にエンコードされた状態で通常使われます。
"Base58Check"では、58個の文字（Base58）とチェックサムを使いますが、これは人間にとって読みやすくしたり、曖昧さを避けたり、転写時のエラーを防いだりするためです。
さらに、"Base58Check"でprefixを追加することによって、エンコードしたデータの本体の最初に固有の文字（A）が現れるため、NEOのアドレスだと判断しやすくなります。


== NEOのアドレスを作ってみよう！
NEOのアドレスは、`A`から始まる34桁の文字列の羅列になります。
//emlist{
AXJAtEWGNW3EbgJZxoYDe9tL7CafDqdYKY
//}

これから、City Of ZionがGolangで実装したNeo-Goのパッケージを元にAから始まるNEOアドレスの生成方法を辿っていきたいと思います。
参考にしたCity Of Zionのパッケージは次のとおりです。

Neo-Go: @<href>{https://github.com/CityOfZion/neo-go}@<br>{}

また、本章で使用したコードは、全てgithub上に掲載していますので、そちらも合わせてご確認ください。

@<href>{https://github.com/keymakers/neoJPbook/blob/master/code/address/main.go}


NEOのアドレス生成は、次の手順で達成されます。

 1. 秘密鍵（PrivateKey）の生成@<br>{}
 2. 楕円曲線暗号の仕組みを利用して秘密鍵から公開鍵（PublicKey）の生成@<br>{}
 3. RIPEMD-160で公開鍵のハッシュを生成@<br>{}
 3. version byteをつける（NEOアドレスの'A'に該当する)@<br>{}
 4. checksumをつける@<br>{}
 5. base58でencodeする@<br>{}


ここでは、すでに準備されている楕円曲線上の点を選びます。
//emlist[ランダムな秘密鍵の生成]{
type (
// EllipticCurve represents the parameters of a short Weierstrass
// equation elliptic curve.
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
//}

実際に実行してみます。
//emlist{
func main() {
	privateKey, err := NewPrivateKey()
	if err != nil {
	log.Fatal(err)
	}
	fmt.Println(hex.EncodeToString(privateKey.b))
}
//}

秘密鍵が生成されたことがわかります。
前述したとおり256bitの秘密鍵は、16進数では64桁で表示されます。

//cmd{
49dac28b59c9127ede34be6ec3a2ab68475e4619c6f289eef67b0b6ba0014ca6
//}


=== 秘密鍵から公開鍵の生成

//emlist{
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
//}

実際にこの関数を実行してみます。
//emlist{
func main() {
privateKey, err := NewPrivateKey()
if err != nil {
log.Fatal(err)
}

publicKey, err := privateKey.PublicKey()
if err != nil{
log.Fatal(err)
}

fmt.Println(hex.EncodeToString(publicKey))
}
//}

公開鍵が生成されました。もし、これがSecp256r1で定義された楕円曲線上にない場合、エラーが帰ってくるはずなので、正しい公開鍵だと確認できます。

//cmd{
0222c1b83dcfcb3565a09e6beede84732ee14b9c8e2bb5effb2d1c53f575fce16a
//}

=== RIPEMD-160で公開鍵のハッシュを生成
//emlist{
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
//}
関数名は、signatureとなっていますが、関数内で実行していることは、秘密鍵から公開鍵を生成（前述）して、それを元に公開鍵の20byteのハッシュを生成しています。
実際にこの関数を実行してみます。
//emlist{
func main() {
//ランダムなプライベートキーの生成
privateKey, err := NewPrivateKey()
if err != nil {
log.Fatal(err)
}
publicKeyHash, err := privateKey.Signature()
if err != nil {
log.Fatal(err)
}
fmt.Println(hex.EncodeToString(publickeyHash))
}
//}

20byteの公開鍵ハッシュが生成されました。
//cmd{
2dd673f4cdf38741eb0e73c51025e6002fcc44b5
//}

=== base58でエンコード
//emlist{
// Address derives the public NEO address that is coupled with the private
// key, and returns it as a string.
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
//}
先ほどの'Signature'関数以降をみてみると、base58におけるAに当たる0x17を先頭につけるとともに、checksumとして、4byte分を後半にくっつけていることがわかります。
最後に、これをbase58でエンコードすることで、NEOのアドレスが生成されます。

=== 最終コード

//emlist{
package main

import(
	"fmt"
	"log"
	"io"
	"crypto/rand"
	"math/big"
	"crypto/sha256"
	"golang.org/x/crypto/ripemd160"
	"bytes"
	"errors"
	"encoding/hex"
)

type (
// EllipticCurve represents the parameters of a short Weierstrass equation
// elliptic curve.
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

// Address derives the public NEO address that is coupled with the private
// key, and returns it as a string.
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

//Base58Encode encodes a byte slice to be a base58 encoded string.
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
// https://en.wikipedia.org/wiki/Elliptic_curve_point_multiplication
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
//}

実際に、最終コードを実行してみると、次のようなNEOのアドレスと秘密鍵が生成されました。
//cmd{
686adb9235d948078b1aa098e50f369fe4df90e96b3bd5abfb8c0cc972b4d359
AUFkwd7fqQo7uLVoygvFBys9kTCharg9Tr
//}

このアドレスが機能するか、実際にimportしてみてNEOの送金をしてみたいと思います。
今回使用するwalletは、CityOfZionが作っているneon-walletです。
//indepimage[neoscanTxHistory][neoscanの取引履歴][scale=0.7]
//indepimage[test-sending][neon-walletの中身][scale=0.7]

無事送信することができました！取引履歴は、@<href>{https://neoscan.io/transaction/1d3783c59b43197ad33a9ce1868dfabc365fea3ed4de4e5050cb6c724a8821ca, neoscan}で確認することができます。

==[column] アドレスの最初の文字「A」の理由
NEOのアドレスがAから始まるのは、NEOの前身であるAntShareのAからきているといわれています。
