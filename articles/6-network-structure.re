= NEOネットワーク
#@#担当者:CryptoAge
//lead{
NEOでは、ブロックを生成を行う上でコンセンサスノードと呼ばれる複数のノードによって合意形成を行います。
本章では、現在のコンセンサスノードの概要やこれからコンセンサスノードになるための手順について解説していきます。
//}

== オフチェーンガバナンス
オフチェーンガバナンスは通常NEOファウンデーションによって行われます。
現在のコンセンサスノードをマネジメントするだけではなく、NEOのプロモーションをしたりコアプロジェクトをサポートしたりしています。

== オンチェーンガバナンス
現在、メインネットではコンセンサスノードは7つあり、NEO Foundationが5つのコンセンサスノードを持ち、City of ZionとKPNが1つずつコンセンサスノードを持っています。
そのコンセンサスノードになる前のノードを候補ノード（candidate node)と呼び、現在4つの候補ノードがあります。

NEOには2つのトークンがあります。1つはNEO、もう1つはGASと表されるNeo Gasです。NEOの総量は100,000,000トークンであり、分割することはできません。

トークンはネットワークをマネジメントするためのトークンとして使われてており、NEOのプロトコルのアップデートやblock keepingの投票に用いられています。

NEOトークンは2つに分割されており、50%はクラウドセールにて販売され、残りの50%はNEOが保有しています。これはNEOが長期的なデベロップメントを行いエコシステムをマネジメントするために必要だからです。
50%の内訳は以下です。

 * 10% : NEOの開発者とNEOファウンデーションのメンバーに対するインセンティブ
 * 10% : NEOのエコシステム内で開発者に対するインセンティブ
 * 15% : 不遇の自体に対する備え
 * 15% : NEO上のプロジェクトに対する投資

@<href>{https://github.com/neo-ngd/reference/blob/master/How-To-Become-NEO-Consensus-Nodev1.4.md}

== コンセンサスノードへのなり方
オンチェーン、オフチェーンでのコンセンサスノードのなり方があります。

 * オンチェーンの場合
 ** 要件調査
 ** ノードになり投票
 ** 投票を集め、意思決定のサポート

 * オフチェーンの場合
 ** 要件調査
 ** NEOファウンデーションとのパートナーシップ
 ** ノードになり投票
 ** 投票を集め、意思決定のサポート

=== 要件調査
コンセンサスノードになる場合、次の要件を提出することが求められ、コンセンサスノードページと、オフィシャルページに情報が乗ることになります。

 * 組織情報
 ** ウェブサイトもしくはSNSアカウント
 ** 組織の名前と本拠地
 ** 少なくても2/3以上のチームメンバーの写真と詳細
 ** コンタクト（emailアドレスなど）
 * サーバータイプ
 * 次の課題に対する対応策
 ** ノードの安全性
 ** メンテナンス
 ** 長期安定性
 ** 単一障害性/リカバリー
 ** 予算
 * ハードウェアのスケーリング/アップデートに対するプラン
 ** ハードウェアの推奨スペック
 *** 4 Core CPU
 *** 8 GB RAM
 *** 10M Bandwidth
 *** 100G Hard Drive
 * NEOのコミュニティに対する貢献

== プレーヤー詳細
=== NEO Foundation
Public Key: 024c7b7fb6c310fccf1ba33b082519d82964ea93868d676662d4a59ad548df0e7d

NEOブロックチェーン運営主体。NPO法人でありSmart Economy（智能経済）を実現するために開発を行っています。
NEOファウンデーションはNEO Global DevelopmentとNEO Global Capitalにより設立されました。
City of ZionやNewEconoLab、NeoResearchなどに経済的な資金提供を行っています。

twitter: @<href>{https://twitter.com/neo_blockchain}

facebook: @<href>{https://www.facebook.com/NEOSmartEcon}

github: @<href>{https://github.com/neo-project}

=== CITY OF ZION
Public Key: 025bdf3f181f53e9696227843950deb72dcd374ded17c057159513c3d0abe20b64

Website: @<href>{http://cityofzion.io/}

E-mail: council@cityofzion.io

City of Zionはオープンソース開発、デザイン、翻訳などを行いNEOコアチームとエコシステムを開発しているグループです。

=== KPN
Public Key: 035e819642a8915a2572f972ddbdbe3042ae6437349295edce9bdc3b8884bbf9a3

Website: @<href>{https://www.kpn.com}

E-mail: DLT@KPN.com

KPNはオランダに拠点をもつ通信会社です。

=== Swisscom
Swissに拠点をもつ通信会社です。テストネットにノードをもっています。

== ブロック高
NEOブロックチェーンにおいて、ブロックの生成速度は15〜20秒に1つです。執筆時（2018年11月）で過去に生成されてきたブロックの数は2922556となっています。

== NEOテストネット
テストネットとは開発者・ユーザーが自由に開発しプログラムをテストすることができる環境です。テストネットで開発する際にもGASと呼ばれる手数料がかかりますが、これは実際のGASではなく価値はありません。テストネットのブロックは完全にメインネットと隔離されています。なので、実際に開発をする際には、まずテストネットでプログラムを検証してからメインネットにデプロイするという手順を取ります。このステップを踏む理由は、メインネットにデプロイされたプログラムはたとえ開発者でも変更することができないためです。

== テストネットの特徴
 1. 無料でやりとりをすることができる
 2. グローバルな環境で開発できる
 3. ブロックチェーンブラウザーにて簡単に過去の取引をみることができる
 4. スマートコントラクトをデプロイすることができ、誰でも参照することができる
 5. テストネットは商用では使われない

== NEOクライアントをダウンロードする
テストネットとメインネットのクライアントは同じものを使います。クライアントのconfigulationファイルを変更することによってメインネットとテストネットを入れ替えることができます。

 * リリース
 ** @<href>{https://neo.org/download, NEO-GUI}
 ** @<href>{https://github.com/neo-project/neo-cli/releases, NEO-CLI}
 * ソースコード
 ** @<href>{https://github.com/neo-project/neo-gui, NEO-GUI}
 ** @<href>{https://github.com/neo-project/neo-cli, NEO-CLI}

== テストGASとテストNEOの獲得方法

 1. リクエストフォーム（ @<href>{https://www.neo.org/Testnet/Create} )を埋めますその際に、EMAILとPUBLIC KEYを入力してください
 2. その後、1日ほどした後、コントラクトアドレスと2つ目のプライベートキーを受け取ります
 3. 自分のウォレットにマルチシグアドレスを作ります
 4. アドレスを特定し自分のウォレットからアセットを送信します

==== パブリックキーを確認する
アドレスとパブリックキーはことなります。パブリックキーはプライベートキーを表示している時に見ることが出いますが、プライベートキーをシェアするとアドレスの残高から通貨を引き出せるようになるので、他の人にシェアしないようにしましょう。
//image[neo_gas_0][パブリックキーの確認]{
//}

=== リクエストフォームに回答する
こちらのURL（@<href>{https://www.neo.org/Testnet/Create}）からEMAILアドレスとパブリックキーを指定します。数日ごEMAILが届きます。

=== マルチパーティーアドレスを作成する
アセットにアクセスするために、自身のNEO-GUIでウォレット内に"Multi-party signed address"を作成します。

NEO-GUI上でCreate Contract Addressを押しMulti-Signatureを選択します。
//image[neo_gas_1][NEO-GUIでの操作1]{
//}

パブリックキーのリストから、署名に必要なキーを選択します。

最低限必要な署名の数を設定します。

confirmを押します。

指定したEmailに紐付いたcontractアドレスが作成され、アカウントのページに表示されます。

//image[neo_gas_2][NEO-GUIでの操作2]{
//}

=== 他のアカウントのアセットを送信する

 1. NEO-GUI上でContract Addressを選択します
 2. NEO-GUIメニューからTransactionを押しTransferを選択します
 3. アセット、送りたい量、送信先のアドレスを指定します


== クライアントをすばやく同期する
クライアントは使用する実際に使用する前に完全に同期する必要があります。過去のブロックをすべてダウンロードする代わりに必要な部分だけをダウンロードすることで同期をすばやく行うことができます。

=== ステップ1
@<href>{http://sync.ngd.network/, Offline synchronized packageをダウンロードする}

//image[syncblocks_1][ブロック同期1]{
//}

=== ステップ2
オフラインパッケージをダウンロードするページで、ネットワークに応じてMainnetもしくはTestnetを選択し、パッケージをダウンロードします。

//image[syncblocks_2][ブロック同期2]{
//}

=== ステップ3
クライアントを起動してブロックのダウンロードしてステータスを確認します。

//image[gui_1][ブロック同期3]{
//}

* NEO-GUIでは、画面からダウンロードの状態を確認することができます。

== ネットワーク・プロトコル
NEOはP2P（Peer to Peer）ネットワーク構造を採用しています。この構造では、ノードがTCP/IPプロトコルを通じてお互いにやりとりをしあいます。このプロトコルではPeerノードとValidatingノードという2種類のノードがあります。Peerノードは取引やブロックを拡散し受け取り、交換します。一方でValidatingノードはブロックを作り出すことができます。

== NEOのノードでプライベートチェーンを構築する
プライベートチェーンの構築方法とGASとNEOの使用方法を見ていきましょう。

=== Virtual Machineをセッティングする
NEOのプライベートブロックチェーンでは、コンセンサスを行うために少なくても4つのノードが必要です。今回はデモンストレーションなので、Standard DS1 v2 1 core, 3.5 GB RAM サイズのWindows Virtual MachineをAzure上に構築します。
//image[privatechain_1][プライベートチェーンの構築]{
//}

クラウドのサーバーにvirtual machineを構築する場合、virtual machineの管理画面にログインしてnetwork security groupを作成してください。

"network interface" "network security group" "inbound security rules" "add" を port 10331-10334 に加えてください。

virtual machineの作成が完了したら、4つのvirtual machineのIP addressを保存してください。このアドレスは後使用します。

=== ウォレットを作成する
最初に4つのウォレットを作成します。それらには、@<code>{wallet1.db3,wallet2.db3,wallet3.db3,wallet4.db3} という名前をつけます。このステップはローカルのPC画面上もしくはロマンドラインで実行することができます。次のスクリーンショットでどのようにウォレットをコマンドライン上で作成するかが分かると思います。

//image[privatechain_3][walletの生成]{
//}

ウォレットを作成することができ、対応するパブリックキーをテキストファイルに保存します

その後、ウォレットを4つのVirtual Machineのノードにコピーします。

=== configurationファイルを修正する
ノードの設定ファイルであるprotocol.jsonを開きます。
Magicのvalueを修正します。Magicは通常、メッセージのネットワークを識別するために用いられています。Magicはuint型なので、値は[0 - 4294967295]のいずれかをとります。

StandbyValidatorsを修正し、さきほど保存した4つのパブリックキーの値を入力します。最後にSeedListを修正します。ここでは、以前保存したIP address入力しportは変更を加えないようにします。次のコードを参考にしてください。

//emlist[configulation]{
{
  "ProtocolConfiguration": {
    "Magic": 1704630,
    "AddressVersion": 23,
    "StandbyValidators": [
"02f27545181beb8f528d13bbb66d279db996ecb56ed9a324496d114acb48aa7a32",
      "02daa386d979ae6643869a365294055546023acb332ee1a74a5ae5d54774a97bac",
      "0306f12f7217569cdbe9dde9ff702d0040e0a4570873eee63291adaa658128e55c",
      "035781b4d55dc58187f61b5d9277afbaae425deacc5df57f9891f3a5c73ecb24df"
   ],
    "SeedList": [
      "13.75.112.62:10333",
      "137.116.173.200:10333",
      "168.63.206.73:10333",
      "137.116.171.134:10333"
   ],
    "SystemFee": {
      "EnrollmentTransaction": 0,
      "IssueTransaction": 0,
      "PublishTransaction": 0,
      "RegisterTransaction": 0
    }
  }
}
//}

SystemFeeは手数料を表しています。次の作業にかかる手数料は
 * book-keepersの登録 - 1000
 * アセットの分配 - 500
 * スマートコントラクト 500
 * アセットの登録 - 10000
となっています。

この設定はSeedList内で変更することができます。

その後、4つのバーチャルマシーンで次のコマンドを入力してノードを動かします。ウォレットを開き、コンセンサスプロセスを開始します。
CLI Command Referenceを参考にしてください。

ノードをスタートする：Dotnet neo-cli.dll

ウォレットを開く：Open wallet wallet1.db3

注意：すべてのノードでwallet1を開くわけではないので、ノードによって番号を変えてください。

コンセンサスをスタートする：Start consensus

上記のコマンドが正常に動作すれば、4つのノードは次のようなコンセンサスプロセスを表示します。

//image[privatechain_8][コンセンサスプロセス]{
//}

4つのノードは次に見れるように1つの環境が停止しても動き続ける。

//image[privatechain_9][コンセンサスの継続]{
//}

== 無料のNEOを手に入れる
Neo-GUIをインストールし、プライベートブロックチェーンにつなぐために、protocol.jsonを修正します。Walletを開き、左上の文字が0でなく、つぎのように表示されていた場合、クライアントはプライベートチェーンに接続されています。

//image[privatechain_12][NEO-GUIでプライベートチェーンに接続]{
//}

PCクライアントのwallet1.db3を開き、multi-party signatureアドレスを追加します。その後、protocol.jsonに4つのパブリックキーを入力します。マルチシグのミニマムの鍵数を選択（この場合は3つ）します。

Confirmをクリックしメニューバーのwalletをクリックします。そうすると、コントラクトアドレスに100000000NEOが入っていることを確認することができます。

//image[privatechain_14][NEO獲得]{
//}
