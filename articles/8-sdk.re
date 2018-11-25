= SDKや開発について
#@#担当者:@genm

この章では、NEOでの開発を促進するためのSDKや開発ツールの操作方法について解説します。


== neo-local

neo-localとは、自身のPCやサーバ上で瞬時にNEOブロックチェーンを展開できる、NEO dApp向けのブロックチェーン構築ツールです。
本ツールを使用することによって、NEOでの開発をすぐに始めることができます。
対応OSはMacOS、Linux、Windowsです。
本ツールは、EthereumのGanacheに相当します。

neo-localを使用すると、複数のDockerイメージが展開されます。

neo-localは、次のサービスによって構成されます。

 * neo-local-faucet（開発用フォーセット）
 * neo-privatenet（ローカル実行用のプライベートネット）
 * neo-python（開発用CLI）
 * neo-scan-api（ブロック参照ツールのAPI）
 * neo-scan-sync（ブロック参照ツールのブロックチェーンとの同期）
 * postgres（neoscan用のデータベース）

=== インストール

本項では、neo-localをインストールする方法を解説します。
それぞれのプラットフォームにおいて、neo-scanを稼働させるには
Docker、Docker Compose、Gitが必要なので事前にインストールをしてください。

gitコマンドを使用して、neo-localのリポジトリをクローンします。
//cmd{
git clone https://github.com/CityOfZion/neo-local.git
//}

=== 起動
本項では　、neo-localを起動する方法を解説します。

==== Linux, MacOS
neo-localをクローンしたディレクトリに移動します。
//cmd{
cd ./neo-local
//}
neo-scanを起動します。

//cmd{
make start
//}

neo-scanを停止させる場合は次のコマンドを実行します。
//cmd{
make stop
//}

==== Windows
neo-localをクローンしたディレクトリに移動します。
//cmd{
cd ./neo-local
//}

neo-scanを起動して、neo-pythonにアクセスします。
//cmd{
docker-compose up -d --build --remove-orphans

docker exec -it neo-python np-prompt -p -v
//}

neo-scanを停止させる場合は次のコマンドを実行します。
//cmd{
docker-compose down
//}


== neo-local-faucet

ブロックチェーンの操作や、スマートコントラクトをデプロイする際には、手数料としてNEOGasが必要になります。
NEOには、開発の際の手数料を補充する手段として、ファーセット（蛇口）が用意されています。
neo-localに含まれているので、単体でインストールする必要はありません。
#@# TODO

== neonjs
neon-jsとは、ウォレット機能、トランザクションの操作機能、その他便利機能を搭載したNEOブロックチェーンのためのJavascript SDKです。
City Of Zionによってオープンソースで開発されており、NeonWalletというNEO用ウォレットアプリで実際に使われています。

neon-jsは、ノードとして機能しないライトウォレットです。前章までで使用したneo-pythonには、フルノードとして多くの機能が搭載されています。
@<img>{lightwallet}にフルノードとライトウォレットの違いを示します。

//image[lightwallet][ライトウォレットとフルノードの違い][scale=0.8]{

//}

ライトウォレットとフルノードには、決定的な違いとしてブロックチェーンとの同期を行うか否かという点があります。
フルノードは、ブロックチェーンとの同期のためにブロックチェーンのすべてのデータを内部に取り込み、自身がノードとしてブロックチェーンのやり取りを行います。
これに対し、ライトウォレットでは同期をせずブロックチェーンとのやり取りをフルノードに委任します。よって、ライトウォレットでは内部にブロックチェーンのデータをもつことなく、さまざまな処理を行うことが可能となっています。
ライトウォレットは、機能がシンプルで必要とする容量が少ないことから、スマートフォンやブラウザのアプリケーションで展開しやすいという特徴があります。

== neo-python
neo-pythonとは、City Of Zionによって開発されたNEOブロックチェーンのためのPython SDKです。
neo-pythonでは、主に次の機能を備えています。
neo-localに含まれているので、単体でインストールする必要はありません。


 * PythonベースのP2Pノード機能
 * インタラクティブな CLI
 * スマートコントラクトのビルド、デプロイ、実行
 * Pythonバーチャルマシンのブロックチェーン上でスマートコントラクトを実行
 * 基本的なウォレット機能
 * NEP2、NEP5に対応したウォレット機能
 * RPCクライアント機能
 * RPCサーバ機能
 * Notfication Server機能
 * Runtime.Log や Runtime.Notify によるイベントモニタリング機能

=== プロンプト操作

==== wallet関連の操作
//emlist{
	#ウォレットを開く
	open wallet {wallet_path}

	#ウォレットを作成する
	create wallet

	#ウォレット情報を表示する
	wallet

	#ウォレットを閉じる
	wallet close

	#ウォレットを再構築する
	wallet rebuild

	#指定したブロックの高さからウォレットを再構築する
	wallet rebuild {number}

	#コントラクトによるトークンの送信
	wallet tkn_send {token symbol} {address_from} {address to} {amount}

	#ウォレットによるトークンの送信
	wallet tkn_send_from {token symbol} {address_from} {address to} {amount}

	#ウォレットからトークンを削除する
	wallet delete_token {token_contract_hash}

	#GASの配当を請求する
	wallet claim

	#wifキーからアカウントをインポートする
	import wif {wif}

	#nep2暗号化済みキーからアカウントをインポートする
	import nep2 {nep2_encrypted_key}

	#wifを出力する
	export wif {address}

	#nep2暗号化済みキーを出力する
	export nep2 {address}
//}

==== トランザクションに関するコマンド

//emlist{
	#JSON形式で書かれたトランザクションに署名する
	sign {transaction in JSON format}
//}

==== スマートコントラクトに関するコマンド

//emlist{
	#スマートコントラクトのイベントログを表示するように設定する
	config sc-events {on/off}

	#ブロックチェーンに影響しないテスト用のInvokeを行う
	testinvoke {contract hash}

	#オプション:
	--attach-neo={amount}
	--attach-gas={amount}
	--from-addr={addr}
	--no-parse-addr (parse address strings to script hash bytearray)

	#ストレージへの書き込み結果の表示設定(標準はonになっている)
	debugstorage {on/off/reset}
//}

==== その他のコマンド

//emlist{
	#現在のノード情報を表示
	open wallet

	#プロンプトを終了する
	quit	または exit

	#コマンドリストの表示をする
	help

	#指定したアカウントの情報を表示する
	account {address}
//}


== Neoscan
neoscanは、WebアプリケーションとAPIサーバによって構成されたソフトウェアです。
NEOブロックチェーンとの同期をとり、ブロックチェーン上で行われたトランザクションや、デプロイしたスマートコントラクトの情報を即座に参照することができます。

@<href>{https://neoscan.io/}にアクセスすることで、NEOのMainnetに接続しているneoscanを利用することができます。

現在のneo-scanは、次の複数のサービスにより構成されています。

 * neo-scan-api（ブロック参照ツールのAPI）
 * neo-scan-sync（ブロック参照ツールのブロックチェーンとの同期）
 * postgres（データベース）



== その他のツール
これまでに解説したツールの他にも、NEO dApp開発に役に立つツールや情報は存在します。
Awesome NEO( @<href>{https://github.com/CityOfZion/awesome-neo} )というGithubのリポジトリでは、
NEOの関連ツールへのリンクがまとめられており、多くのNEO技術者の助けとなるでしょう。
