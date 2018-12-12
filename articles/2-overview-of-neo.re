= NEOの仕組みと概要
#@#担当者:@EG-easy
//lead{
この章では、NEOの概要および歴史について解説していくとともに、NEOがもつ基本的な特徴について触れていきます。
//}

== OnchainとNEOについて
NEOは、スマートコントラクトを実行するプラットフォームの構築を目指すオープンソースプロジェクトです。
まずは、NEOと上海で創業されたブロックチェーン技術の研究開発会社であるOnchainとの関係性について見ていきましょう。
Onchain@<fn>{onchain}は、2014年に設立され、そのときの創業者は次の3人になります。

  * Da Hongfei Zhang@<fn>{Da}
  * Jun Li@<fn>{Jun}
  * Wentao Yang@<fn>{Wentao}

//footnote[onchain][http://www.onchain.com/]
//footnote[Da][https://twitter.com/dahongfei]
//footnote[Jun][https://www.linkedin.com/in/jun-li-58950069/]
//footnote[Wentao][https://www.linkedin.com/in/wentaoyang/]

Onchainは@<b>{ブロックチェーン技術の研究開発会社}であり、民間企業や政府と組み既存の業務課題を
ブロックチェーン技術を用いて解決できないかを模索するPoC（Proof of Concept）などを行うビジネスをしています。
パートナー企業や組織にはMicrosoft ChinaやLinux FoundationのHyperLedger、中国政府、そして日本の豊橋市などがいます。
Onchainはこれまで、Antshares, NEO, DNA（Distributed Network Architecture}）@<fn>{dna}, ONTology@<fn>{ont} とプロジェクトの立ち上げを行ってきています。

//footnote[dna][https://github.com/DNAProject/]
//footnote[ont][https://github.com/ontio/ontology]

Onchainの前身であるAntsharesの開発チームは2014年頃からブロックチェーン技術の研究開発をスタートしました。
このとき開発していたブロックチェーンはAntsharesと呼ばれました。

//indepimage[antshares][Antsharesのロゴ][scale=0.5]

一方で、研究開発を進めていくうちに、さまざまな民間企業から注目を集め、B2Bに特化したエンタープライズ向けに焦点を当てたブロックチェーン技術
の開発を行う会社（Onchain）を設立しました。

Onchain設立後、開発が続けられたAntsharesは2017年8月にICOを実施します。

//table[ico][ICOの概要]{
期間　資金調達額（BTC）
----------
2017年8月8日～9月7日　6119.53 BTC
//}

また、その後リブランディングを行い、プロジェクト名をNEOに変えました。

NEOに携わるエンジニアの一部はOnchainに在籍しているものの、NEOは完全なオープンソースのパブリックブロックチェーンであり、コミュニティが所有しているものであると考えられています。
つまり、NEOとOnchainは資本的な所有関係などがないサポート関係であり、@<b>{NEOは完全にコミュニティによって運営されています}。

== NEOのトークン設計について
ネットワークに流通するネイティブトークンが2つ存在します。

NEO

 * ネットワークを維持するためのガバナンストークン
 * Validator選出のための投票機能（governance）
 * NEO保有者に自動的にGasを分配
 * ICOに配布
 * 総発行量は、1億NEOで、5000万NEOがICOで販売され、残りの5000万NEOはFoundationが管理

Gas

 * ブロック生成時に発生
 * Network維持のための手数料（スマートコントラクトのdeploy/invoke）
 * Network内のペイメントトークン

現在（2018/12）、メインネットでのNEOやGasの送金手数料は無料になっています。
􏰢􏰱􏰒􏰈􏰋􏰖􏰟􏰜
