= トランザクション
#@#担当者:Azusa Taroura

トランザクションとは、コインやトークン、アセットなどの取り引きを指します。
NEOのネットワークプロトコルはビットコインに似ていますが、ブロックやトランザクションのデータ構造は大きく異なります。


== ブロック

トランザクションやアセットなど、ネットワーク全体のデータはブロックチェーンに格納されます。
ブロックはトランザクションをまとめて格納でき、トランザクションがブロックに格納される際、ブロックの検証用スクリプトによって検証が行われます。
検証のあと、ブロックはコンセンサスアルゴリズム（dBFT）を経てブロックチェーンに格納されます。

ブロックの構造を@<table>{blockdata1}に示します。

//tsize[10,20,10,60]
//table[blockdata1][ブロック]{
サイズ	名称	データ型	説明
-------------------------------------------------------------
4	Version		uint32		ブロックのバージョンを示します。現在は0が使用されています。
32	PrevBlock	uint256		前のブロックのハッシュ値を示します。
32	MerkleRoot	uint256		トランザクションリストのルートのハッシュ値
4	Timestamp	uint32		タイムスタンプ。Timestampは、前のブロックよりも後の値が入る必要があります。一般に、前後のブロックでタイムスタンプの差は約15秒程度となります。
4	Height		uint32		ブロックの高さ。Heightは、前のブロックのHeightに1を加えた値が入ります。
8	Nonce		uint64		ランダムな数値
20	NextMiner	uint160		次の採掘者(マイナー)のコントラクトアドレス
1	-		uint8		固定値(1)
x	Script		script		ブロックの検証用のスクリプト
x*x	Transactions	tx[]		トランザクションのリスト。リストの最初には必ず後述のMinerTransactionが入ります。
//}

ブロックは前のブロックのハッシュ値を持っており、ブロックチェーン上でブロック同士の「チェーン」が形成されます。
ブロックのハッシュ値を計算するとき、ブロック全体を計算するのではなく、
Version, PrevBlock, MerkleRoot, Timestamp, Height, Nonce, NextMinerの7つの値のみ計算されます。
MerkleRootには全てのトランザクションのハッシュ値が含まれており、トランザクションの変更はそのブロックのハッシュの値に影響します。

== トランザクションの内容

トランザクションの内容をみてみましょう。（@<table>{tx_table1}）
トランザクションの内容を大きく示すと、Type, Attributes, Input, Outputとなります。
その他にもプロトコルやライブラリの中で、Scripts, Witness, Exclusive Dataなどのデータをもつことがあります。

//tsize[30,60]
//table[tx_table1][トランザクションの内容]{
名前				説明
-------------------------------------------------------------
Type				トランザクションのタイプ
Attributes			トランザクションの属性
Input				トランザクションの入力
Output				トランザクションの出力
(Scripts)			NEOのネットワークプロトコルにおいて、トランザクションの検証に使用されるスクリプト。Neon-jsにおいてはWitnessに当たります。
(Exclusive Data)	Neon-jsにおいて、各トランザクションのTypeごとに持つユニークな値。
//}

NEOではコインの管理方法として、ビットコインなどでも使用されているUTXO（Unspent Transaction Output）という仕組みを利用しています。
UTXOとは、ブロックチェーン上でまだ使用されていないトランザクションのアウトプットであり、残高を示します。
簡単にいうと、取り引きデータから残高を算出する方法になります。 @<img>{utxo} はトランザクションの流れの一例を示しています。
過去のトランザクションのアウトプットが、次のトランザクションのインプットとなります。

//image[utxo][UTXO]{
... utxo ...
//}

=== トランザクションのタイプ（Type）

トランザクションのタイプには@<table>{tx_type_table1}のような種類があります。

//tsize[40,60]
//table[tx_type_table1][トランザクションのタイプ]{
名称						説明
-------------------------------------------------------------
MinerTransaction		コンセンサストランザクション、バイトチャージ割当を行う
IssueTransaction		アセット分配を行います。
ClaimTransaction		GAS配布を行います。
EnrollmentTransaction	バリデーター候補者として登録します。
VotingTransaction		バリデーターの投票を行います。
RegisterTransaction		アセットを登録します。version2以降はAsset.CreateAsset関数に置き換わっています。
ContractTransaction		最も一般的に使用されるコントラクトトランザクションです。
AgencyTransaction		トランザクションの委託を行います。
PublishTransaction		スマートコントラクトトランザクション。version2以降はContract.Create関数に置き換わっています。
InvocationTransaction	スマートコントラクトトランザクションの呼び出しを行います。
//}

いくつか代表的なトランザクションについて説明します。

MinerTransactionは、各ブロックのTransactionsのリストの最初に格納され、そのブロックの全ての手数料をブロックの検証を行うバリデーターの報酬にします。
Nonce（uint32）をもち、Nonceの値はハッシュ値の衝突を避けるのに使用します。（@<table>{tx_type_table2}）

//table[tx_type_table2][MinerTransaction]{
サイズ	フィールド	データ型	説明
-------------------------------------------------------------
4		Nonce	uint32		ランダムな数値
//}

次に、IssueTransactionについてです。
アセットの管理者は、IssueTransactionによってアセットを作成し、NEOのブロックチェーンに登録して任意のアドレスへ送ることができます。
発行されているアセットがNEOの場合、トランザクションの手数料はかかりません。
IssueTransactionもNonceの値を持ちます。（@<table>{tx_type_table3}）

//table[tx_type_table3][IssueTransaction]{
サイズ	フィールド	データ型	説明
-------------------------------------------------------------
4		Nonce	uint32		ランダムな数値
//}

ClaimTransactionは分配するためのGASをInputとして持ちます。（@<table>{tx_type_table4}）

//table[tx_type_table4][ClaimTransaction]{
サイズ	フィールド	データ型	説明
-------------------------------------------------------------
34*x	Claims	tx_in[]		分配するGAS
//}

#@# 現在EnrollmentTransaction/VotingTransaction/AgencyTransactionは"obstacle"であるということで、記述を削除
#@# -----------------------------------------------------------------
#@# EnrollmentTransactionは、登録フォームを表し、トランザクションの提供者をバリデーター候補者として登録するために使用されます。
#@# EnrollmentTransaction型のトランザクションを作成し、PublicKeyのアドレスにデポジットを送付することで登録が行われます。
#@# そのため、EnrollmentTransactionは@<table>{tx_type_table5}にあるように、バリデーター候補者のPublicKeyを持ちます。
#@# バリデーター候補者の登録をキャンセルする場合は、登録しているPublicKeyの残高を0にしてください。
#@#
#@# //table[tx_type_table5][EnrollmentTransaction]{
#@# サイズ	フィールド	データ型	説明
#@# -------------------------------------------------------------
#@# 33	PublicKey	ec_point	バリデーターのPublicKey
#@# //}
#@#
#@# VotingTransactionは、登録フォームのハッシュ値のリストを持ち、
#@# EnrollmentTransactionで登録されたバリデーター候補者へ投票するために使用されます。（@<table>{tx_type_table6}）
#@# 投票することのできる候補者は、1人以上、1024人以下です。
#@# このトランザクションのNEOの値が投票の重みとなります。
#@#
#@# //table[tx_type_table6][VotingTransaction]{
#@# サイズ	フィールド	データ型	説明
#@# -------------------------------------------------------------
#@# 32*x	Enrollments	uint256[]	登録フォームのハッシュ値のリスト
#@# //}

NEOブロックチェーンに新しいアセットを登録する場合は、RegisterTransaction（@<table>{tx_type_table7}）を使用します。
RegisterTransactionは、NEOのversion2以降はAsset.CreateAsset関数（@<list>{tx_type_table7_new}, @<table>{tx_type_table7_new}）に置き換わっています。
RegisterTransactionの構造をに示します。

//tsize[10,15,15,70]
//table[tx_type_table7][RegisterTransaction]{
サイズ	フィールド	データ型	説明
-------------------------------------------------------------
1	AssetType	uint8		アセットタイプ
x	Name		varstr		アセットの名前
8	Amount		int64		アセットの金額（正の値をとる場合は制限モード、-10^-8の場合は無制限モード）
33	Issuer		ec_point	発行者のPublicKey
20	Admin		uint160		発行者のコントラクトのハッシュ値
//}

//list[tx_type_table7_new][Asset.CreateAsset]{
public static extern Neo.SmartContract.Framework.Services.Neo.Asset
	Create(byte asset_type,
		   string name,
		   long amount,
		   byte precision,
		   byte[] owner,
		   byte[] admin,
		   byte[] issuer)
//}

//table[tx_type_table7_new][Asset.CreateAsset]{
名称			データ型	説明
-------------------------------------------------------------
asset_type		byte	アセットタイプ
name			string	アセットの名前
amount			long	アセットの合計。入力値は、100,000,000を掛けた値。
precision		byte	アセットが取ることができる小数点以下の桁数。
owner			byte[]	長さが33のバイト配列の、所有者のパブリックキー
admin			byte[]	長さが20のバイト配列の、管理者のコントラクトアドレス
issuer			byte[]	長さが20のバイト配列の、発行者のコントラクトアドレス
戻り値			Asset	新たに登録されたアセット
//}

AssetTypeには@<table>{tx_type_table7_1}の値が格納されます。
それぞれのアセットには固有の制限があり、NEOおよびAntCoinはシステムの組み込みアセットのためGenesisブロック（高さが0のブロック）でのみ作成することができます。
equityのようなアセットを作成するときは、アセットの合計額を制限し、送信者と受信者の両方がトランザクションに署名しなくてはなりません。
Currencyのアセット作成時には、アセットの合計額は制限することができません。

//table[tx_type_table7_1][AssetType]{
値		名前			説明
-------------------------------------------------------------
0x40	CreditFlag		クレジットフラグ
0x80	DutyFlag		Dutyフラグ。このフラグがONの場合、検証が行われます。
0x00	SystemShare		NEO
0x01	SystemCoin		NEO GAS
0x08	Currency		通貨
0x60	Token			カスタムアセットのトークン。CreditFlag | 0x20で計算されます
0x90	Share			equity/シェア。DutyFlag | 0x10で計算されます
0x98	Invoice			インボイス。DutyFlag | 0x18で計算されます
//}

#@# DutyFlag
#@# https://github.com/neo-project/neo/blob/fd5e3c6d7e9e0e9ff87b0994d71d2cbc0db9e27d/neo/Network/P2P/Payloads/Transaction.cs#L184

ContractTransactionは、NEOやGASなどのアセットを送るためのもっとも一般的なトランザクションです。
InputsとOutputsのトランザクションフィールドは、このトランザクションにおいて重要です。
（たとえば、NEOをどれだけ、どのアドレスに対して送信するかが設定されます。）

#@# AgencyTransactionにおいて、ValueAssetIdは通貨のアセット（Currency）でなければならず、AssetIdと同じ値を使用することはできません。
#@# 購入リストと販売リストは、それぞれ少なくとも1つの注文を格納する必要があります。
#@# トランザクションにはまったく未取引である注文は含めることはできませんが、部分的に取引が実行されている注文であれば可能です。
#@# 部分的に取引が実行されている注文では、最低価格をつける必要があります。
#@# 買い注文では顧客が指定した価格より低い値段でトランザクションを実行することができ、反対に売り注文では顧客が指定した価格より高い価格とすることができます。
#@#
#@# AgencyTransactionの構造を@<table>{tx_type_table8}に示します。
#@#
#@# //tsize[10,20,20,70]
#@# //table[tx_type_table8][AgencyTransaction]{
#@# サイズ	フィールド		データ型	説明
#@# -------------------------------------------------------------
#@# 32	AssetId			uint256		アセットID
#@# 32	ValueAssetId	uint256		アセットIDの値
#@# 20	Agent			uint160		エージェントのコントラクトアドレス
#@# x*x	Orders			order[]		注文のリスト
#@# 1	-				uint8		固定値(1)
#@# 36	SplitOrder		split_order	部分的に実行されている注文のリスト
#@# //}
#@#
#@# トランザクションと共に注文が転送される場合、すでにアセット、Currency、
#@# エージェントなどの情報が含まれているため、@<table>{tx_type_table8_1}のように注文を圧縮できます。
#@#
#@# //table[tx_type_table8_1][Order]{
#@# サイズ	フィールド		データ型	説明
#@# -------------------------------------------------------------
#@# 8		Amount		int64		注文の量
#@# 8		Price		int64		注文の金額
#@# 20		Client		uint160		顧客のコントラクトアドレス
#@# 34*x	Inputs		tx_in[]		トランザクションの入力
#@# x*x		Scripts		script[]	この注文を検証するために使用されるスクリプトのリスト
#@# //}
#@#
#@# 部分的に実行されている注文について、@<table>{tx_type_table8_2}のようなデータ構造をとります。
#@#
#@# //table[tx_type_table8_2][SplitOrder]{
#@# サイズ	フィールド		データ型	説明
#@# -------------------------------------------------------------
#@# 8		Amount		int64		注文の量
#@# 8		Price		int64		注文の金額
#@# 20		Client		uint160		顧客のコントラクトアドレス
#@# //}
#@#
#@# すべての種類の注文について、金額がプラスの場合は買い、金額がマイナスの場合は販売を意味します。

PublishTransactionは、version2以降においてContract.Create関数（@<list>{tx_type_table9}, @<table>{tx_type_table9}）に置き換わっています。

//list[tx_type_table9][Contract.Create]{
public static extern Neo.SmartContract.Framework.Services.Neo.Contract
	CreateContract(byte[] script,
				   byte[] parameter_list,
				   byte return_type,
				   bool need_storage,
				   string name,
				   string version,
				   string author,
				   string email,
				   string description)
//}

//table[tx_type_table9][Contract.Create]{
名称			データ型	説明
-------------------------------------------------------------
script			byte[]		コントラクトのバイトコード
parameter_list	byte[]		パラメータリスト
return_type		byte		戻り値の型
need_storage	bool		コントラクトが永続化ストアを必要とするかどうか
name			string		コントラクトの名前
version			string		バージョン
author			string		署名者の名前
email			string		署名者のeメールアドレス
description		string		コントラクトの説明
戻り値			Contract	新たに作成されたコントラクト
//}

InvocationTransaction@<table>{tx_type_table10}に示します。

//table[tx_type_table10][InvocationTransaction]{
サイズ	フィールド	データ型	説明
-------------------------------------------------------------
x		Script	uint8[]		スマートコントラクトのスクリプトにより呼び出されます
8		Gas		int64		スマートコントラクトを実行するのに必要なコストです
//}



=== トランザクションの属性（Attributes）

トランザクションの属性は、トランザクションが使用される目的に合わせたデータを格納しているUsageと、
目的外のデータ用に確保されたDataの２つの領域に分類されます。（@<table>{tx_attributes_table1}）

//table[tx_attributes_table1][トランザクションの属性]{
サイズ	名称	データの型	説明
-------------------------------------------------------------
1		Usage	uint8			トランザクションの目的に関連したデータ
0|1		length	uint8			データ長（Usageの値によっては省略されます）
length	Data	uint8[length]	トランザクションの目的外のデータ
//}

Usageでは、@<table>{tx_usage_table1}のようなデータが格納されます。

//table[tx_usage_table1][トランザクションの用途]{
値			名称				説明
-------------------------------------------------------------
0x00			ContractHash		コントラクトのハッシュ値
0x02-0x03		ECDH02-ECDH03		ECDH鍵交換のための公開鍵
0x20			Script				トランザクションの追加のバリデーション
0x30			Vote				投票に使用します
0x80			CertUrl				証明書のURLアドレス
0x81			DescriptionUrl		トランザクションの説明URL
0x90			Description			簡単な説明
0xa1-0xaf		Hash1-Hash15		カスタムハッシュ値を保管するのに使用
0xf0-0xff		Remark-Remark15		注意事項
//}

ContractHash、ECDH02-ECDH03、Hash1-Hash15において、データ長は32固定でありlengthフィールドは省略されます。
CertUrl、DescriptionUrl、Description、Remark-Remark15において、データ長を255以下の長さで明確に定義する必要があり、省略することはできません。


=== トランザクションの入力

トランザクションの入力は、以前に存在していた別のトランザクションの出力から来なければなりません。
1つ前のトランザクションの出力を確認するために、Inputでは次の2つのデータを持ちます。

1. 参照される1つ前のトランザクションのハッシュ（PrevHash）
2. 1つ前のトランザクションの出力リストにある、この入力のインデックス（PrevIndex）


=== トランザクションの出力

トランザクションの出力には、@<table>{tx_output}に示す3つのフィールドがあります。
各トランザクションは最大65536のOutputをもつことができます。

//table[tx_output][トランザクションの出力]{
サイズ	フィールド		データ型	説明
-------------------------------------------------------------
32		AssetId		uint256		アセットID
8		Value		int64		アセットの値
20		ScriptHash	uint160		宛先のアドレス
//}

==[column] NEO3.0ではTransactionの種類を簡素化する方向へ
今まで見てきたように、NEO 2.xでは、次のようにさまざまな種類のトランザクションがあります。

 * MinerTransaction
 * IssueTransaction
 * ClaimTransaction
 * EnrollmentTransaction
 * RegisterTransaction
 * ContractTransaction
 * StateTransaction
 * PublishTransaction
 * InvocationTransaction

しかしながら、それらのほとんどは時代遅れであり、多くのタイプのトランザクションはスマートコントラクトで簡単に実装することができます。
保持する必要がある唯一のものはInvocationTransactionです。

参考:@<href>{https://github.com/neo-project/neo/issues/327}

== NEO scan

ブロックチェーン上の情報を取り出すために、ブロックチェーンのデータを同期させると膨大な時間がかかります。
NEO scanを利用すると、Web上で瞬時にトランザクションの確認を行うことができます。

NEO SCAN APIではWeb APIを提供しており、プログラムに組み込んでNEOのトランザクションを参照させることが可能です。
NEO SCAN APIの仕様については下記ページを参照してください

@<href>{https://neoscan.io/docs/index.html}


== 悪意のあるトランザクションに対する取り組み
#@# https://medium.com/neo-smart-economy/annocements-about-attack-transactions-in-neo-9fd7409fb3c6

NEOではネットワークのトランザクション数が大幅に増加しており、その中にはNEOのネットワークに対する攻撃も含まれます。
しかしながら、NEOは高いパフォーマンスをもち、1秒あたりに多くのトランザクションを処理することが可能です。

NEOではMaxTransactionsPerBlockというパラメーターが、ネットワークからトランザクションが溢れるのを防ぐために追加されました。
また、MaxFreeTransactionsPerBlockというパラメーターがあり、これによって１つのブロックで手数料なしで送信できるトランザクションの数を制限しています。
MaxFreeTransactionsPerBlockを超えてしまったトランザクションは、ノードのメモリプールに残り、順番を待ちます。
MaxTransactionsPerBlockは500、MaxFreeTransactionsPerBlockは20に設定されています。

MaxFreeTransactionsPerBlockが20で、各ブロックのトランザクションの先頭は必ずMinerTransactionとなるため、
ブロックごとのトランザクションの合計は21になります。
ブロックの中の21のトランザクションのうち、いずれかのトランザクションが手数料を払って送信された場合、
そのノードは他のノードより高い優先度で処理されます。

トランザクションの手数料の額は、どのぐらい優先度をあげて早く取引を完了したいかによって変わりますが、一般には1 satoshi gas程度です。
トランザクションの手数料を払うかどうかの決定には、ノードのメモリプールの状態を確認してもよいでしょう。
ノードのメモリプールの状態は、NEO-CLIのgetrawmempool関数によって取得することができます。

@<href>{http://docs.neo.org/en-us/node/cli/2.7.6/api/getrawmempool.html}

NEOチームでは、ユーザーが取引所からNEOを引き出す際に、取引所が手数料を追加することを推奨しています。
また、ウォレットに手数料を設定する機能をつけることを推奨しており、これによってユーザーは簡単に手数料を使用した取引が行うことが可能です。
