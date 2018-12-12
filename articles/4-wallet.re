= ウォレット
#@#担当者:
== この章でカバーすること
NEOを管理するにあたっていくつかの方法を紹介します。

=== ハードウェアウォレットで管理する方法

NEOなどの暗号資産を管理する方法は大きく分けて3種類あります。Ledger社などが提供しているハードウェアウォレットで管理する方法、bitFlyerやCoinbaseのような取引所のアカウントで管理する方法、GincoやCoinbase Walletなどが提供しているウォレットで管理する方法です。その中でもっとも安全性が高いのがハードウォレットで管理する方法です。これは、ハードウェアウォレットで管理することによりオフライン環境で資産が管理できるようになるので、プライベートキーを安全に守ることができます。

=== NEON Wallet

NEON Walletはデスクトップウォレットです。NEONウォレットではNEOとGASの送金、保有、受け取りを行うことができます。

現在のNEONウォレットでできることは次のとおりです。

 * ウォレットを作成する
 * プライベートキーの秘匿化
 * ウォレットアカウントのインポートとエクスポート
 * 残高の表示
 * GASとNEOの価格表示
 * NEO,GAS,NEP5トークンの送金
 * ネットワークの変更
 * 一斉送金
 * NEP9でのQRサポート
 * NEOトークンセールへの参加
 * など

//image[wallet][ブロック同期1]{
//}

インストール

NEONウォレットは
@<href>{https://github.com/CityOfZion/neon-wallet/releases, こちら}
からインストールすることができます。

NEONのインストールをする際に、Node v6.11.0と@<href>{https://github.com/CityOfZion/neon-wallet, yarn}が必要となります。

実際に開発を行うときには、プロジェクトのルートディレクトリーにて、

 * Setup
 ** yarn install
 *** nodeのディペンデンシーをインストールします。エラーが発生してしまった場合には、@<href>{https://github.com/node-hid/node-hid#compiling-from-source, こちら}を確認することでエラーの発生源を特定することができます。
 * ./node_modules/.bin/electron -v
 ** バージョンが1.8.4であることを確認します。起動するまでに10〜15秒ほどの時間がかかります。
 * Developing
 ** yarn dev
 * Running
 ** yarn assets
 ** yarn start
 * Testing
 ** yarn test もしくは、yarn run test-watchでテストを行います。

 NEONウォレットは開発アップデートが順次更新されていくので、githubのアカウントより確認ください。

=== NEO GUI
//image[NEO-GUI][ブロック同期1]{
//}
NEO GUIはNEO開発者向けのデスクトップウォレットです。これによってユーザーはグラフィカルユーザーインターフェーズとやり取りを行いながら開発をすることができます。

=== NEO Tracker
//image[NEO-Tracker][ブロック同期1]{
//}
NEO Trackerウォレットはウェブベースのウォレットです。Javascriptによって開発されており、オープンソースプロジェクトとなっています。NEOとGASの受信、送信、保存ができ、ユーザーフレンドリーなアプリケーションとなっています。

@<href>{https://neotracker.io/, NEO-Tracker, NEO-Tracker}

=== NEO ウォレット
//image[NEO-wallet][ブロック同期1]{
//}
NEOウォレットはNEOの開発者コミュニティによって開発されています。プライベートキーをローカル環境で管理できるので、安全性が比較的高くなっています。

=== NEO CLI
//image[NEO-CLI][ブロック同期1]{
//}
NEO CLIはNEOの開発者コミュニティーによって開発されています。こちらはコマンドライン上での操作となるため、上級者むけのウォレットです。現在、LinuxとWindowsのみの対応となっています。
