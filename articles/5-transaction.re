= トランザクション
#@#担当者:Azusa Taroura

トランザクションとは、ブロックチェーンの取り引きデータや、取り引きそのもののことを指します。
トランザクションはコンセンサスアルゴリズム（dBFT）を経て、ブロックチェーンに記録されます。

NEOのネットワークプロトコルはビットコインに似ていますが、ブロックやトランザクションのデータ構造は大きく異なります。


== ブロック

トランザクションやアセットなど、ネットワーク全体のデータはブロックチェーンに格納されます。
ブロックチェーンに格納されているブロックの構造を@<table>{blockdata1}に示します。

//tsize[10,20,10,60]
//table[blockdata1][ブロック]{
サイズ	名称	データ型	意味
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
x*x	Transactions	tx[]		トランザクションのリスト
//}

ブロックのハッシュ値を計算するとき、ブロック全体を計算するのではなく、
Version, PrevBlock, MerkleRoot, Timestamp, Height, Nonce, NextMinerの7つの値のみ計算されます。
MerkleRootには全てのトランザクションのハッシュ値が含まれており、トランザクションの変更はそのブロックのハッシュの値に影響します。


== トランザクションの内容

トランザクションの内容をみてみましょう。（@<table>{tx_table1}）
トランザクションの内容を大きく示すと、Type, Attributes, Input, Outputとなります。
その他にもプロトコルやライブラリの中で、Scripts, Witness, Exclusive Dataなどのデータをもつことがあります。

//tsize[30,60]
//table[tx_table1][トランザクションの内容]{
名前				意味
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
簡単にいうと、取り引きデータから残高を算出する方法になります。@<img>{utxo}はトランザクションの流れの一例を示しています。

//image[utxo][UTXO]{
... utxo ...
//}

=== トランザクションのタイプ（Type）

トランザクションのタイプには@<table>{tx_type_table1}のような種類があります。

//tsize[40,60]
//table[tx_type_table1][トランザクションのタイプ]{
名称						意味
-------------------------------------------------------------
MinerTransaction		コンセンサストランザクション、バイトチャージ割当を行う
IssueTransaction		アセット分配を行う
ClaimTransaction		GAS配布を行う
EnrollmentTransaction	バリデーター候補者として登録する
VotingTransaction		バリデーターの投票を行う
RegisterTransaction		アセットを登録する
ContractTransaction		最も一般的に使用されるコントラクトトランザクション
AgencyTransaction		トランザクション委託
PublishTransaction		スマートコントラクトトランザクション
InvocationTransaction	スマートコントラクトトランザクションの呼び出し
//}

いくつか代表的なトランザクションについて説明します。

MinerTransactionは、各ブロックのTransactionsのリストの最初に格納され、そのブロックの全ての手数料をバリデーターの報酬にします。
Nonce（uint32）をもち、Nonceの値はハッシュ値の衝突を避けるのに使用します。（@<table>{tx_type_table2}）

//table[tx_type_table2][MinerTransaction]{
サイズ	フィールド	データ型	意味
-------------------------------------------------------------
4		Nonce	uint32		ランダムな数値
//}

アセットの管理者は、IssueTransactionによってブロックチェーンに登録されているアセットを作成し、任意のアドレスへ送ることができます。
NEOから発行されているアセットの場合、トランザクションの手数料はかかりません。
IssueTransactionもNonceの値を持ちます。（@<table>{tx_type_table3}）

//table[tx_type_table3][IssueTransaction]{
サイズ	フィールド	データ型	意味
-------------------------------------------------------------
4		Nonce	uint32		ランダムな数値
//}

ClaimTransactionは分配するためのGASをInputとして持ちます。（@<table>{tx_type_table4}）

//table[tx_type_table4][ClaimTransaction]{
サイズ	フィールド	データ型	意味
-------------------------------------------------------------
34*x	Claims	tx_in[]		分配するGAS
//}

EnrollmentTransactionは、登録フォームを表し、トランザクションの提供者をバリデーター候補者として登録するために使用されます。
EnrollmentTransaction型のトランザクションを作成し、PublicKeyのアドレスにデポジットを送付することで登録が行われます。
そのため、EnrollmentTransactionは@<table>{tx_type_table5}にあるように、バリデーター候補者のPublicKeyを持ちます。
バリデーター候補者の登録をキャンセルする場合は、登録しているPublicKeyを0にしてください。

//table[tx_type_table5][EnrollmentTransaction]{
サイズ	フィールド	データ型	意味
-------------------------------------------------------------
33	PublicKey	ec_point	バリデーターのPublicKey
//}

VotingTransactionは、登録フォームのハッシュ値のリストを持ち、
EnrollmentTransactionで登録されたバリデーター候補者へ投票するために使用されます。（@<table>{tx_type_table6}）
投票することのできる候補者は、1人以上、1024人以下です。
このトランザクションのNEOの値が投票の重みとなります。

//table[tx_type_table6][VotingTransaction]{
サイズ	フィールド	データ型	意味
-------------------------------------------------------------
32*x	Enrollments	uint256[]	登録フォームのハッシュ値のリスト
//}

NEOブロックチェーンに新しいアセットを登録する場合は、RegisterTransactionを使用します。
RegisterTransactionの構造を@<table>{tx_type_table7}に示します。

//tsize[10,15,15,70]
//table[tx_type_table7][RegisterTransaction]{
サイズ	フィールド	データ型	意味
-------------------------------------------------------------
1	AssetType	uint8		アセットの型
x	Name		varstr		アセット名
8	Amount		int64		アセットの金額（正の値をとる場合は制限モード、-10^-8の場合は無制限モード）
33	Issuer		ec_point	発行者のPublicKey
20	Admin		uint160		発行者のコントラクトのハッシュ値
//}

AssetTypeには@<table>{tx_type_table7_1}の値が格納されます。
それぞれのアセットには固有の制限があり、NEOおよびAntCoinはシステムの組み込みアセットのためGenesisブロック（高さが0のブロック）でのみ作成することができます。
equityのようなアセットを作成するときは、アセットの合計額を制限し、送信者と受信者の両方がトランザクションに署名しなくてはなりません。
Currencyのアセット作成時には、アセットの合計額は制限することができません。

//table[tx_type_table7_1][AssetType]{
値		名前			意味
-------------------------------------------------------------
0x00	SystemShare		NEO
0x01	SystemCoin		NEO GAS
0x10	Share			equity/シェア
0x20	Currency		通貨
0x40	Token			カスタムアセットのトークン
//}

ContractTransactionは、アセットを転送するためのトランザクションです。
NEOやGASなどのアセットを転送することを目的としており、ブロックチェーンでもっとも一般的な取引です。

AgencyTransactionにおいて、ValueAssetIdは通貨のアセット（Currency）でなければならず、AssetIdと同じ値を使用することはできません。
購入リストと販売リストは、それぞれ少なくとも1つの注文を格納する必要があります。
トランザクションには全く未取引である注文は含めることはできませんが、部分的に取引が実行されている注文であれば可能です。
部分的に取引が実行されている注文では、最低価格をつける必要があります。
買い注文では顧客が指定した価格より低い値段でトランザクションを実行することができ、反対に売り注文では顧客が指定した価格より高い価格とすることができます。

AgencyTransactionの構造を@<table>{tx_type_table8}に示します。

//tsize[10,20,20,70]
//table[tx_type_table8][AgencyTransaction]{
サイズ	フィールド		データ型	意味
-------------------------------------------------------------
32	AssetId			uint256		アセットID
32	ValueAssetId	uint256		アセットIDの値
20	Agent			uint160		エージェントのコントラクトアドレス
x*x	Orders			order[]		注文のリスト
1	-				uint8		固定値(1)
36	SplitOrder		split_order	部分的に実行されている注文のリスト
//}

トランザクションと共に注文が転送される場合、すでにアセット、Currency、
エージェントなどの情報が含まれているため、@<table>{tx_type_table8_1}のように注文を圧縮できます。

//table[tx_type_table8_1][Order]{
サイズ	フィールド		データ型	意味
-------------------------------------------------------------
8		Amount		int64		注文の量
8		Price		int64		注文の金額
20		Client		uint160		顧客のコントラクトアドレス
34*x	Inputs		tx_in[]		トランザクションの入力
x*x		Scripts		script[]	この注文を検証するために使用されるスクリプトのリスト
//}

部分的に実行されている注文について、@<table>{tx_type_table8_2}のようなデータ構造をとります。

//table[tx_type_table8_2][SplitOrder]{
サイズ	フィールド		データ型	意味
-------------------------------------------------------------
8		Amount		int64		注文の量
8		Price		int64		注文の金額
20		Client		uint160		顧客のコントラクトアドレス
//}

すべての種類の注文について、金額がプラスの場合は買い、金額がマイナスの場合は販売を意味します。

=== トランザクションの属性（Attributes）

トランザクションの属性は、トランザクションが使用される目的に合わせたデータを格納しているUsageと、
目的外のデータ用に確保されたDataの２つの領域に分類されます。（@<table>{tx_attributes_table1}）

//table[tx_attributes_table1][トランザクションの属性]{
名称			意味
-------------------------------------------------------------
Usage			トランザクションの目的に関連したデータ
Data			トランザクションの目的外のデータ
//}

Usageでは、@<table>{tx_usage_table1}のようなデータが格納されます。

//table[tx_usage_table1][トランザクションの用途]{
値			名称				意味
-------------------------------------------------------------
0x00			ContractHash		コントラクトのハッシュ値
0x02-0x03		ECDH02-ECDH03		ECDH鍵交換のための公開鍵
0x20			Script				トランザクションの追加承認用
0x30			Vote				投票
0x80			CertUrl				トランザクションの承認URL
0x81			DescriptionUrl		トランザクションの説明URL
0x90			Description			簡単な説明
0xa1-0xaf		Hash1-Hash15		ハッシュデータの操作に使用可能
0xf0-0xff		Remark-Remark15		トランザクション備考
//}


=== トランザクションの入力

トランザクションの入力は、以前に存在していた別のトランザクションの出力から来なければなりません。
1つ前のトランザクションの出力を確認するために、Inputでは次の2つのデータを持ちます。

1. 参照される1つ前のトランザクションのハッシュ（PrevHash）
2. 1つ前のトランザクションの出力リストにある、この入力のインデックス（PrevIndex）


=== トランザクションの出力

トランザクションの出力には、3つのフィールドがあります。

1. アセットのタイプ
2. 宛先のアドレス
3. 転送量


== NEO scan

ブロックチェーン上の情報を取り出すために、ブロックチェーンのデータを同期させると膨大な時間がかかります。
NEO scanを利用すると、Web上で瞬時にトランザクションの確認を行うことができます。

NEO SCAN APIではWeb APIを提供しており、プログラムに組み込んでNEOのトランザクションを参照させることが可能です。
NEO SCAN APIの仕様については下記ページを参照してください

https://neoscan.io/docs/index.html


== トランザクションの手数料

現在、NEOではトランザクションに手数料はありません。（ブロック毎に21トランザクションに限ります。）
しかし、ユーザはトランザクションの手数料を支払い、優先度を上げることが可能です。
