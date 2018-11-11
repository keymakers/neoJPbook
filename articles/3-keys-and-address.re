= キー、アドレス
#@# 担当者:@EG-easy

TODO:リード文をつける

秘密鍵と公開鍵からNEOアドレスが生成されるまでの流れ
アドレス

== 概要

公開鍵暗号は、秘密鍵と公開鍵という2つの鍵を使った暗号のことで、1つの鍵を使う共通鍵暗号と対をなす暗号技術です。代表的なものにRSA暗号が挙げられます。通信を暗号化するSSLは公開鍵暗号と共通鍵暗号の両方を利用しています。
秘密鍵は自分以外に知られないようにし、公開鍵はオープンにしても問題ないという面白い暗号方式です。
公開鍵暗号は次の性質を持ちます。

 * 公開鍵で暗号化した文は秘密鍵のみで復号可能
 * 秘密鍵で暗号化した文は公開鍵のみで復号可能（出来ない公開鍵暗号も存在）
 * 秘密鍵から公開鍵を知ることが可能、公開鍵から秘密鍵を知ることは不可能
 * 秘密鍵でサインした文は公開鍵で本人が作成した文であると証明可能（デジタル署名）
 以上の性質をもつ公開鍵暗号ですが、暗号通貨ではアドレスの作成とアドレスをもつ本人である証明（デジタル署名）に使われます。デジタル署名は、主に暗号通貨の送金時に本人が送金した証明に使われます。これがないと、誰かの暗号通貨を不正に送金し放題になり通貨として機能しません。


暗号通貨ではBitcoinの慣例に倣い楕円曲線デジタル署名アルゴリズムECDSA（Elliptic Curve Digital Signature Algorithm）が用いられることが多いです。

== ハッシュ
平文全体に対して秘密鍵で暗号化⇒公開鍵で復号化という処理をすると、平文が長大であるほど演算に時間が掛かってしまい、実用的ではなくなってしまいます。そこでハッシュ関数を利用し、平文を一定の長さに変換してから署名する仕組みが一般的になっています。
ハッシュはあらゆる入力データから固定長の小さな出力値を一意に求める仕組みのことを指し、この仕組みで得られた出力値をハッシュ値と言います。代表的なものにMD5やSHA-1があります。
ハッシュの主な用途は受信したデータの破損や改ざんの検証や公開鍵暗号のデジタル署名です。あと、パスワードをDBに保存するときも普通はパスワードにハッシュを施してから保存したりします。
ハッシュは次の性質を持ちます。

 * あらゆる長さの入力データから固定長のハッシュ値を出力する
 * 同じ入力データからは必ず同じハッシュ値が得られる
 * 似た入力データからでも、まったく違うハッシュ値が得られる
 * ハッシュ値から入力データを求めることは出来ない
 * 違う入力データから同じハッシュ値が出力される（衝突する)ことはほぼあり得ないがごく稀にあり得る
暗号通貨では、お馴染みブロックチェーンやアドレスの作成、取引（トランザクション）の検証、マークルルートの作成そしてマイニングなどさまざまなところで利用されます。

暗号通貨でよく使われるのはSHA-256（出力32byte）やRIPEMD-160（出力20byte）で、あとでNEOのコードをみる時にも実際に現れます。

NEOのアドレス生成アルゴリズムについて、利用されている既存の暗号化技術とともに解説していきます。
NEOのアドレスを作る手順は大まかにいうといかのようになっており、この記事では各手順を順番に説明していきます。

 * 秘密鍵を作る
 * 公開鍵を秘密鍵から作る
 * 公開鍵のハッシュを公開鍵から作る
 * NEOアドレスを公開鍵ハッシュと公開鍵から作る

NEOのアドレス生成に関しては、Bitcoinのアドレス生成に似ているのところがあるので、そちらも参考にすると理解しやすいです。
秘密鍵と公開鍵と呼ばれるふたつの鍵をペアとして利用します。

もともと、公開鍵暗号自体は、1970年代に開発されたもので、情報セキュリティに関わるさまざまな分野で使用されています。
この、公開鍵暗号が使用されるようになってきたから、素数体上のべき乗演算や楕円曲線上のスカラー倍算などの関数が発見されました。
こうした関数は、一方向性関数と呼ばれており、一方向への計算は簡単ですが、逆方向への計算は現実的には不可能といわれています。NEOでは、Bitcoinと同じように、公開鍵暗号を基盤として、楕円曲線上のスカラー倍算を用いています。

NEOのネットワーク上では、秘密鍵は、NEOやGasの送信、または、スマートコントラクトのデプロイをする時のトランザクションに署名するのに使われています。
公開鍵と署名生成に使用する秘密鍵は、ある式（後述）に基づいて導き出されており、このときの署名は、秘密鍵を公開することなく、公開鍵に対する正当性を検証できるようになっています。

NEO所有者は、NEOを送信する時に、公開鍵と署名をトランザクションに記載します。NEOネットワークに参加している参加者は、この公開鍵と署名を確認することで、トランザクションを検証し有効なものとみなします。

NEOウォレットにはキーペアリストを持っており、それぞれのキーペアは秘密鍵と公開鍵で構成されてい
ます。秘密鍵（k）は数値で、通常ランダムに選ばれます。秘密鍵から不可逆関数である楕円曲線上のスカラー
倍算を用いて公開鍵（k）を生成します。そして、この公開鍵（k）から不可逆ハッシュ関数を用いてNEOアド
レス（A）を生成します。この節では、秘密鍵の生成から始めて、公開鍵の生成に使われる楕円曲線の数学を見
ていき、最後にNEOアドレスを公開鍵から生成します。

== 秘密鍵
秘密鍵は意図的に指定できるものではなく無作為に選ばれる数値です。秘密鍵による所有権管理はNEOア
ドレスに結びついた全ての資金の根幹をなします。秘密鍵は署名を生成するときに使われ、この署名は資金を
使うときに所有権の主張に必要となります。秘密鍵はいつでも極秘に保っておかなければいけません。もし他
者に秘密鍵が漏れると、秘密鍵に対応したNEOアドレスの資金のコントロールを他者に与えることになっ
てしまうためです。秘密鍵をバックアップをしておくだけでなく、秘密鍵の偶発的な紛失からも保護しておか
なければいけません。というのは、もし秘密鍵をなくしてしまうと、秘密鍵を復元することはできず、秘密鍵
によってセキュリティを担保していた資金も永遠に失ってしまうためです。

ちなみに22562256とは次のように78桁にも及ぶとてつもなく大きな数で、観測可能な宇宙にある原子の数とかそういう値に匹敵するくらいの大きさの数です。これだけ大きければ、例え全人類がビットコインを使うようになったとしても十分だといえるでしょう。
2^256=115792089237316195423570985008687907853269984665640564039457584007913129639936


=== Tips
公開鍵は、秘密鍵から計算できるため、秘密鍵だけ保存しておけばいつでも公開鍵を導き出すことができます。


== Tips1
NEO秘密鍵は単なる数値で、コインや鉛筆、紙だけを使ってランダムに秘密鍵を選ぶことが
できます。たとえば、コインを256回投げてNEOウォレットで使うランダムな秘密鍵の二進数
を作り出すことができます。公開鍵はこの秘密鍵から生成することができます。

== ランダムな数値からの秘密鍵の生成
TODO:数式の表示

キーを生成する上で重要かつ一番最初にしなればいけないことは、キー生成の安定的なエントロピー源、つま
り十分なランダムさを確保することです。NEOキーを作ることは、"1から 2^256 までの間の数字を選ぶ
"ということと本質的に同じです。数字を選ぶ厳格な方法は、予測可能であったり再現可能性があったりしな
い方法です。NEOソフトウェアは、256bitのエントロピー（ランダム性）を作り出すOSのランダム値生成器
を使っています。通常OSのランダム値生成器は人間を元にしたランダムさを使って初期化されます。数秒間
だけマウスを小刻みに動かしてくださいとOSからお願いされたことがあるかもしれないですが、それはこの
ランダム値生成が理由です。


== 公開鍵
公開鍵は楕円曲線上のスカラー倍算を使って秘密鍵から計算されるもので、この処理は不可逆な処理になって
います。\（K = k * G\） 但し k は秘密鍵、 G は ベースポイント と呼ばれる定点、 K
は結果として出てくる公開鍵です。逆操作は、離散対数問題 - K を知っていたときに k を導出する問題 -
として知られ、この難しさは k
の全ての可能な値を総当たりで調べるのと同じくらい時間がかかる問題です。秘密鍵から公開鍵を生成する方
法を説明する前に、楕円曲線暗号をもうちょっと細かく見てみましょう。

== 楕円曲線暗号
楕円曲線暗号は、楕円曲線上の点に対する加法とスカラー倍算で表現される離散対数問題をベースに作られた
非対称型暗号方式または公開鍵暗号方式です。
ECC:具体的な暗号方式の名前ではなく、楕円曲線を利用した暗号方式の総称
楕円曲線上の離散対数問題（EC-DLP）の困難性を安全性の根拠とする
Secp256k1

離散対数
素数pと定数gが与えられたとき、y=g^x mod pをxから計算することは容易だが、
yからxを求めることは困難である

TODO:図を入れる

TODO:楕円曲線についての説明をかく

== 公開鍵の生成
秘密鍵をランダムに生成された数値 k とすると、あらかじめ決められた 生成元 G を k
7
に掛けることで楕円曲線上のもう1つの点を得ます。このもう1つの点は公開鍵 K
に対応するものです。ベースポイントは secp256k1 標準で決められており、
NEOでの全ての公開鍵に対して常に同じです。

NEOアドレスは一方向暗号学的ハッシュ化を使うことで公開鍵から生成されます。"ハッシュ化アルゴリズ
ム"または簡単に"ハッシュアルゴリズム"は、フィンガープリントまたは任意のサイズの"ハッシュ"を作り出す
一方向関数です。暗号学的ハッシュ関数はBitcoinの中で広範囲に活用されます。公開鍵から
NEOアドレスを作るときに使うアルゴリズムは、 Secure Hash Algorithm（SHA）と RACE Integrity
Primitives Evaluation Message Digest（RIPEMD）で、中でも SHA256 と RIPEMD160 が使われます。
公開鍵KのSHA256ハッシュを計算し、さらにこの結果のRIPEMD160ハッシュを計算することで、160bit(20b
yte)の数字を作り出します。

== Tips2
NEOアドレスは公開鍵は同じではありません 。
NEOアドレスは公開鍵から一方向関数を使って導出されるものです。

NEOアドレスは、 "Base58Check" と呼ばれる形にエンコードされた状態で通常使われます(Base58
とBase58Checkエンコード参照)。"Base58Check"では、58個の文字（Base58）とチェックサムを使いますが、
これは人間にとって読みやすくしたり、曖昧さを避けたり、転写時のエラーを防いだりするためです。

== Base58とBase58Checkエンコード
大きな数字をコンパクトに表すために、多くのコンピュータではいくつかの記号を使うことで10以上を基数
とするアルファベットと数字を混ぜた表現を使っています。たとえば、伝統的な10進数では0から9までの10個
11
の数字を使う一方、16進数ではAからFの文字を使うことで16個の数字を使います。16進数で表される数字は
10進数で表すよりも短くなります。 バイナリデータをemail
のようなテキストベースの通信で送るために、Base-64 では26個の小文字、26個の大文字、10個の数字、""
や "/" のような２種類の文字を使います。Base-64 は
emailにバイナリデータを添付するのによく使われます。Base58 は
Bitcoinで使うために開発されたテキストベースのエンコード形式で、他の暗号通貨でも使われています。こ
れはコンパクトな表現、可読性、エラー発見および防止のためです。Base58はBase64の部分集合でアルファ
ベットの大文字小文字、数字が使われます。しかし、あるフォントで表示したときに同じように見えて、よく
間違えてしまういくつかの文字は省かれています。Base58はBase64から0（数字の0）、O（大文字o）、l（小文字L）
、I（大文字i）、記号""や"/"を除いたもの、つまり、(0, O, l,
I)を除いたアルファベットの大文字小文字、数字の集合になっています。

書き間違いや転写間違いをさらに防ぐため、Base58Checkはチェックサムを加えたBase58エンコード形式に
なっていてNEOで頻繁に使われています。チェックサムは、エンコードされようとしているデータの最後
に追加される4byteです。このチェックサムはエンコードされたデータのハッシュから作られ、転写間違いや
タイピング間違いを検出したり防いだりするのに使われます。Base58Checkでエンコードされたデータが与
えられた場合、デコードソフトウェアはエンコードされようとしているデータのチェックサムを計算し、含ま
れているチェックサムと比較します。もし2つが一致しなかった場合、これはエラーが混入してしまったかBa
se58Checkデータが無効だということを示しています。これによって、たとえば、ウォレットが有効な送り先だ
と判断して受け付けてしまった打ち間違いBitcoinアドレスを無効と判断し、資金を失ってしまうということ
を防ぐことができます。

NEOアドレスを生成する完全な手順を見てみましょう。秘密鍵から始まって、公開鍵（楕円曲線上の点）を作
り、二重ハッシュ化アドレスを作り、最後にBase58Checkエンコードします。秘密鍵からのBase58Checkエ
ンコードされたNEOアドレスの作成にあるC#コードは、秘密鍵からBase58Checkエンコード済みNEO
アドレスまでの手順を完全な形で逐一示しています。

TODO:NEOのアドレス生成のコードの実行例を乗せると良さそう

== NEOのアドレスとは何か
NEOのアドレスは、`A`から始まる34桁の文字列の羅列になります。
//emlist{
	AXJAtEWGNW3EbgJZxoYDe9tL7CafDqdYKY
//}


== アドレスの生成

neo-cliで実行する
//cmd{
	vagrant@ubuntu-xenial:~/neo-cli/neo-cli/bin/release/netcoreapp2.0/linux-x64$ dotnet neo-cli.dll
	NEO-CLI Version: 2.7.6.1

	neo> create wallet test1.json
	password: ****
	password: ****
	address: AXJAtEWGNW3EbgJZxoYDe9tL7CafDqdYKY
	 pubkey: 0385fa3a2f18549f6c6b72b1c796f439787a54495a569c1df1e76cdb1ff5c99a1d

	 neo> list address
	 AXJAtEWGNW3EbgJZxoYDe9tL7CafDqdYKY	Standard
	 neo> create address
	 [1/1]
	 export addresses to address.txt
	 neo> list address
	 AXJAtEWGNW3EbgJZxoYDe9tL7CafDqdYKY	Standard
	 AT3R596p72wh6V4B38AHiqXgiy1CSSnjU8	Standard
//}



== コードでNEOのアドレス生成の流れを追ってみる
wallet.cs
//emlist{
public WalletAccount CreateAccount()
{
    byte[] privateKey = new byte[32];
    using (RandomNumberGenerator rng = RandomNumberGenerator.Create())
    {
        rng.GetBytes(privateKey);
    }
    WalletAccount account = CreateAccount(privateKey);
    Array.Clear(privateKey, 0, privateKey.Length);
    return account;
}

public WalletAccount CreateAccount(Contract contract, byte[] privateKey)
	{
			if (privateKey == null) return CreateAccount(contract);
			return CreateAccount(contract, new KeyPair(privateKey));
	}
//}
KeyPair.cs
//emlist{
 public KeyPair(byte[] privateKey)
  {
      if (privateKey.Length != 32 && privateKey.Length != 96 && privateKey.Length != 104)
          throw new ArgumentException();
      this.PrivateKey = new byte[32];
      Buffer.BlockCopy(privateKey, privateKey.Length - 32, PrivateKey, 0, 32);
      if (privateKey.Length == 32)
      {
          this.PublicKey = Cryptography.ECC.ECCurve.Secp256r1.G * privateKey;
      }
      else
      {
          this.PublicKey = Cryptography.ECC.ECPoint.FromBytes(privateKey, Cryptography.ECC.ECCurve.Secp256r1);
      }
  }
//}
Crypto.cs
//emlist{
public byte[] Hash160(byte[] message)
	 {
			 return message.Sha256().RIPEMD160();
	 }

public byte[] Hash256(byte[] message)
	 {
			 return message.Sha256().Sha256();
	 }
//}

WalletAccount.cs
//emlist{
public abstract class WalletAccount
	  {
	      public readonly UInt160 ScriptHash;
	      public string Label;
	      public bool IsDefault;
	      public bool Lock;
	      public Contract Contract;

	      public string Address => ScriptHash.ToAddress();
	      public abstract bool HasKey { get; }
	      public bool WatchOnly => Contract == null;

	      public abstract KeyPair GetKey();

	      protected WalletAccount(UInt160 scriptHash)
	      {
	          this.ScriptHash = scriptHash;
	      }
	  }
//}

Helper.cs
//emlist{
	public static string ToAddress(this UInt160 scriptHash)
    {
        byte[] data = new byte[21];
        data[0] = Settings.Default.AddressVersion;
        Buffer.BlockCopy(scriptHash.ToArray(), 0, data, 1, 20);
        return data.Base58CheckEncode();
    }

	public static string Base58CheckEncode(this byte[] data)
	 {
			 byte[] checksum = data.Sha256().Sha256();
			 byte[] buffer = new byte[data.Length + 4];
			 Buffer.BlockCopy(data, 0, buffer, 0, data.Length);
			 Buffer.BlockCopy(checksum, 0, buffer, data.Length, 4);
			 return Base58.Encode(buffer);
	 }
//}

TODO:pubkeyHashからアドレスが生成されるまでをもうちょい調べる


== Ethereumとのアドレスの比較
 EthereumではBitcoinと同じsecp256k1曲線を利用
 Ethereumでは公開鍵のハッシュ化のためのハッシュ関数にKeccak-256が利用されている
 イーサリアムアドレスの表示形式

 イーサリアムアドレスにチェックサムは導入されていないが、その代わりに、ICAPとENSという仕組みがあります。

  * ENS（Ethereum Name Service）
	アドレスにアルファベットをマッピングすることで可読性を確保する。

  * ICAP（Inter exchange Client Address Protocol）

 銀行間の国際送金規格IBANに準拠した形式でイーサリアムアドレスを表示する方法。

 XE（無国籍X＋Ethreum）＋チェックサム＋アドレスor Indirectアドレス

 誤り訂正のためにIndirectアドレスとしてCBC（Capital Based Checksum）アドレスが使われている。

 16進数表示でのローマ字を一定のルールに基づいて大文字に置き換えることで誤り訂正を導入する。CBCアドレスはコレを導入していなくても大文字小文字の違いを無視するので普通に読み込む。導入した場合、誤りを99.986%（約1/10000）の精度で検出できる。

 ルールは以下である。

 １６進数表記にしたアドレスとそのハッシュ値を並べ、アドレスのアルファベットでハッシュ値の同じ桁の値が８以上のものを大文字にする。


TODO:Ethereumのアドレス生成のメカニズムを簡単に書く


== その他の章との関連
NEP6→walletのstarndard
https://github.com/neo-project/proposals/blob/master/nep-6.mediawiki
