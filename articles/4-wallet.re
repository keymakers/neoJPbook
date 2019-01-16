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

NEONウォレットは、次のURLよりダウンロードすることができます。@<br>{}

@<href>{https://github.com/CityOfZion/neon-wallet/releases}@<br>{}

NEONを手動でインストールをする際に、Node v6.11.0とyarnが必要となります。

実際に開発を行うときには、プロジェクトのルートディレクトリーにて、

 * Setup
 ** yarn install
 *** nodeのディペンデンシーをインストールします。エラーが発生してしまった場合には、次のリンクを確認することでエラーの発生源を特定することができます。

 @<href>{https://github.com/node-hid/node-hid#compiling-from-source}

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

 @<href>{https://github.com/CityOfZion/neon-wallet}

=== NEO GUI
//image[NEO-GUI][NEO-GUI]{
//}
NEO GUIはNEO開発者向けのデスクトップウォレットです。これによってユーザーはグラフィカルユーザーインターフェーズとやり取りを行いながら開発をすることができます。
現在サポートされているOSは、windowsのみです。NEO-GUIのインストールは次のリンクより可能です。

@<href>{https://github.com/neo-project/neo-gui/releases}

=== NEO Tracker
//image[NEO-Tracker][NEO-Tracker]{
//}
NEO Trackerウォレットはブラウザベースのウォレットです。Javascriptによって開発されており、オープンソースプロジェクトとなっています。NEOとGASの受信、送信、保存ができ、ユーザーフレンドリーなアプリケーションとなっています。
NEO Trackerウォレットの使用は次のリンクより可能です。

@<href>{https://neotracker.io/}

=== NEO ウォレット
//image[NEO-wallet][NEOウォレット]{
//}
NEOウォレットはNEOの開発者コミュニティによって開発されているブラウザwalletです。プライベートキーをローカル環境で管理できるので、安全性が比較的高くなっています。
NEOウォレットの使用は次のリンクより可能です。

@<href>{https://neowallet.cn/}

=== NEO CLI
//image[NEO-CLI][NEO CLI]{
//}
NEO CLIはNEOの開発者コミュニティーによって開発されています。こちらはコマンドライン上での操作となるため、上級者むけのウォレットです。
NEO CLIのインストールは次のリンクより可能です。

@<href>{https://github.com/neo-project/neo-cli/releases}
