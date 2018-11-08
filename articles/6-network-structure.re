= NEOネットワーク
#@#担当者:CryptoAge
= コンセンサスノード
コンセンサスノードには2種類あり、候補ノード（candidate node)とコンセンサスノード（consensus node)があります。これは前章のコンセンサスアルゴリズムであるdBFTに準拠しているためです。

== オフチェーンガバナンス
オフチェーンガバナンスは通常NEOファウンデーションによって行われます。現在のコンセンサスノードをマネジメントするだけではなく、NEOのプロモーションをしたりコアプロジェクトをサポートしたりしています。

== オンチェーンガバナンス
現在、メインネットではコンセンサスノードは7つあり、NEO Foundationが6つのコンセンサスノードを持ち、City of Zionが1つのコンセンサスノードを持っています。テストネットでは、NEO Foundationが2つ、NEO Global Developmentが1つ、CityOfZionが2つ、KPNは1つ、Swisscomが1つを持っています。

NEOには2つのトークンがあります。1つはNEO、もう1つはGASと表されるNeo Gasです。NEOの総量は100,000,000トークンであり、分割することはできません。

トークンはネットワークをマネジメントするためのトークンとして使われてており、NEOのプロトコルのアップデートやblock keepingの投票に用いられています。

NEOトークンは2つに分割されており、50%はクラウドセールにて販売され、残りの50%はNEOが保有しています。これはNEOが長期的なデベロップメントを行いエコシステムをマネジメントするために必要だからです。
50%の内訳は以下です。

* 10% : NEOの開発者とNEOファウンデーションのメンバーに対するインセンティブ
* 10% : NEOのエコシステム内で開発者に対するインセンティブ
* 15% : 不遇の自体に対する備え
* 15% : NEO上のプロジェクトに対する投資

https://github.com/neo-ngd/reference/blob/master/How%20To%20Become%20A%20Consensus%20Nodev1.2.md

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

NEOブロックチェーン運営主体。NPO法人でありSmart Economy（智能经济）を実現するために開発を行っています。NEOファウンデーションはNEO Global DevelopmentとNEO Global Capitalにより設立された。City of ZionやNewEconoLab、NeoResearchなどに経済的な資金提供を行っています。

twitter: https://twitter.com/neo_blockchain
facebook: https://www.facebook.com/NEOSmartEcon
github: https://github.com/neo-project

=== CITY OF ZION
Public Key: 025bdf3f181f53e9696227843950deb72dcd374ded17c057159513c3d0abe20b64
Website: http://cityofzion.io/
E-mail: council@cityofzion.io

City of Zionはオープンソース開発、デザイン、翻訳などを行いNEOコアチームとエコシステムを開発しているグループです。

=== KPN
Public Key: 035e819642a8915a2572f972ddbdbe3042ae6437349295edce9bdc3b8884bbf9a3
Website: https://www.kpn.com
E-mail: DLT@KPN.com

KPNはオランダに拠点をもつ通信会社です。

=== Swisscom
Swissに拠点をもつ通信会社です。テストネットにノードをもっています。

= ブロック高
NEOブロックチェーンにおいて、ブロックの生成速度は15〜20秒に1つです。執筆時（2018年11月）で過去に生成されてきたブロックの数は2922556となっています。

= NEOテストネット
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

=== テストGASとテストNEOの獲得方法

1. リクエストフォーム（ https://www.neo.org/Testnet/Create )を埋めます。その際に、EMAILとPUBLIC KEYを入力してください
2. その後、1日ほどした後、コントラクトアドレスと2つ目のプライベートキーを受け取ります
3. 自分のウォレットにマルチシグアドレスを作ります
4. アドレスを特定し自分のウォレットからアセットを送信します

==== パブリックキーを確認する
アドレスとパブリックキーはことなります。パブリックキーはプライベートキーを表示している時に見ることが出いますが、プライベートキーをシェアするとアドレスの残高から通貨を引き出せるようになるので、他の人にシェアしないようにしましょう。
//image[neo_gas_0][ブロック同期1]{
}

=== リクエストフォームに回答する
こちらのURL（https://www.neo.org/Testnet/Create）からEMAILアドレスとパブリックキーを指定します。数日ごEMAILが届きます。

=== マルチパーティーアドレスを作成する
アセットにアクセスするために、自身のNEO-GUIでウォレット内に"Multi-party signed address"を作成します。

NEO-GUI上でCreate Contract Addressを押しMulti-Signatureを選択します。
//image[neo_gas_1][ブロック同期1]{
}

パブリックキーのリストから、署名に必要なキーを選択します。

最低限必要な署名の数を設定します。

confirmを押します。

指定したEmailに紐付いたcontractアドレスが作成され、アカウントのページに表示されます。

//image[neo_gas_2][ブロック同期1]{
}

=== 他のアカウントのアセットを送信する

1. NEO-GUI上でContract Addressを選択します
2. NEO-GUIメニューからTransactionを押しTransferを選択します
3. アセット、送りたい量、送信先のアドレスを指定します


== クライアントをすばやく同期する
クライアントは使用する実際に使用する前に完全に同期する必要がある。過去のブロックをすべてダウンロードする代わりに必要な部分だけをダウンロードすることで同期をすばやく行うことができる。

=== ステップ1
@<href>{http://sync.ngd.network/, Offline synchronized packageをダウンロードする}

//image[syncblocks_1][ブロック同期1]{
}

=== ステップ2
オフラインパッケージをダウンロードするページで、ネットワークに応じてMainnetもしくはTestnetを選択し、パッケージをダウンロードする。

//image[syncblocks_2][ブロック同期2]{
}

http://docs.neo.org/en-us/network/syncblocks.html

= ネットワーク・プロトコル
NEOはP2P（Peer to Peer）ネットワーク構造を採用しています。この構造では、ノードがTCP/IPプロトコルを通じてお互いにやりとりをしあいます。このプロトコルではPeerノードとValidatingノードという2種類のノードがあります。Peerノードは取引やブロックを拡散し受け取り、交換します。一方でValidatingノードはブロックを作り出すことができます。

http://docs.neo.org/en-us/network/network-protocol.html
