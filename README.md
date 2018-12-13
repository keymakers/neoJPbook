# NEO技術書
本プロジェクトは、`NEO Keymakers Japan`を中心に行われる、NEOの日本人開発者向けの手引書作成プロジェクトです。NEO上で開発を行うにあたり、現状では日本語文献が圧倒的に少ないので、国内におけるNEOの普及はそれほど進んでいないのが実情です。そこで、NEO上での開発参入の敷居を下げるべく、ブロックチェーンに触れたことがある方がスムーズにNEOについて学習していくとともに、Dapps開発等に取り組む上で役に立つような文献を作成します。

## 内容

## フォルダ構成

|  章名 | 内容完了 |最終レビュー完了|
| ---- | ---- | ---- |
|  Introduction  | ✅ ||
|  Overview of NEO  |✅||
|  Keys and Addrerss  | ✅ ||
|  Wallets  | ✅ ||
|  Transaction  | ✅ ||
|  Network structure  |  ✅||
|  Concensus Algolism  | ✅||
|  SDK |✅ ||
|  Smart Contracts |✅ ||
|  How to start Dapps on NEO|✅ ||
|  NEP |✅||


## 環境構築
本プロジェクトでは、[TechBooster](https://techbooster.org/)の書籍制作ツールRe:VIEWを利用して、執筆・修正を行っていきます。したがって、下記の流れに沿ってRe:VIEWを使用できる設定を各自お願いいたします。環境構築にあたっては、[公式ドキュメント](https://github.com/TechBooster/ReVIEW-Template)も参考にしてください。

- Atomエディタのインストール
- Atom内のパッケージ`language-review`をインストール
- Atomの依存パッケージ`linter`などのインストール
- Re:VIEW をインストールする
```bash
$ sudo gem install review
```
以上で、環境構築は終了です。

## PDFを出力する
rbenvやnodebrewを利用してRubyやNode.jsの準備をしている前提です。 もしそうではない場合、適宜sudoを補うこと。 Node.jsは4.x系以上が必須です。

graphvizを使ったのでbrew install graphvizとかが必要かもしれません。

準備
```
$ gem install bundler
$ git submodule init
$ git submodule update
$ npm install
```
出力
```
$ npm run pdf
```

## お手伝い
本プロジェクトは、Githubにてオープンソースで行われているプロジェクトです。あらゆる方からのコメントや貢献、訂正を歓迎いたします。

詳細につきましては、NEO Keymakers Japan[Slack](https://join.slack.com/t/neokeymakersjapan/shared_invite/enQtMzg1ODE2MTg2ODAxLTE3M2Q0MzJmNDAxZDQ2ZTgwMTdkYzQwOTgwNTdlOWUzNDYwNzE0MWI3YjBhOGI5YmM2MDFhMmZlY2Q4OGY2NDQ)にてお問い合わせください。

### Pull requestによる貢献

|  Branch Name | 役割|
| ---- | ---- |
|  MASTER  |GitHubのトップ用（GitLab Flowのプリプロの位置付けにも活用）|
|   PUBLISH  |出版バージョンごとにマージ|
|  WRITING  |執筆者のプルリクエストを受けるブランチ（READMEの編集もここで）|
|  Chapter Branch  |執筆者それぞれの作業用ブランチ|

![flow](https://user-images.githubusercontent.com/35296935/47613002-905b8a00-dac9-11e8-9307-4e2459093b48.png)

それぞれの執筆者はGitHubをForkしてから作成を始めることを前提としています。それぞれ、WRITINGブランチからブランチを切って執筆作業をしていただければと思います。執筆作業完了後、プルリクエストをWRITINGブランチに対して投げてください。

1. Githubのアカウントを作成
2. `neoJPbook`リポジトリをフォーク
3. 新しいブランチを作成
4. 内容の変更・追加した点をコミット
5. 修正した`.re`ファイルごとにpull requestを提出
