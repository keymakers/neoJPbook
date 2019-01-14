= はじめてのdApps開発
#@#担当者:@ookimaki
//lead{
この章では、実際にNEOを使ったdAppsの開発手法について説明します。
シンプルなコントラクトを実行できるための手順についてまとめています。
//}

== 概要
NEOを使ったdAppsの開発として、今回はこの手順で開発を行っていきます。
なお、「フロントエンドからのスマートコントラクトの呼び出し」では、
Javascriptでのフロントエンドの開発を行ったことがある方向けに、作成したスマートコントラクトとのやり取りを解説しています。

  * NEOのローカル環境の構築
  * スマートコントラクトの開発
  * スマートコントラクトのコンパイル
  * スマートコントラクトのDeploy
  * スマートコントラクトのInvoke
  * フロントエンドからのスマートコントラクトの呼び出し

まずは簡単なコントラクトを実行できることを目標にしてみましょう。
それでは、NEOのローカル環境の構築から始めていきます。

== NEOのローカル環境の構築と起動
ここでは環境構築を簡単にするためにneo-localを使用します。
neo-localのインストールについては、8章の「SDKや開発について」のneo-localの節に詳しくまとめてありますので、ここでは割愛します。

それでは、neo-localを起動し実行環境を準備しましょう。

//cmd{
# neo-localの起動
$ cd ./neo-local
$ make start

[neo-local] Fetching Docker containers...
~省略~
[neo-local] Starting Docker containers...
~省略~
[neo-local] Waiting for network........
[neo-local] Network running! 🎉
[neo-local] Attaching terminal to neo-python client
~省略~
neo> 

//}

複数のコンテナが立ち上がったのち、プロンプトが起動します。
ローカルにNEOの実行環境を構築できたら早速スマートコントラクトの開発を行ってみましょう。

== スマートコントラクトの開発
今回はできるだけ簡単にスマートコントラクトの開発を行うために、
NeoResearchコミュニティが開発したneocompiler<https://neocompiler.io>を使用します。

//image[neocompiler][neocompiler.io][scale=0.9]{
//}

Neocompilerではブラウザ上で次の操作を行うことができます。

  * スマートコントラクトの作成（C#, Phython, Go, Java）
  * 作成したスマートコントラクトのコンパイル
  * コンパイルしたスマートコントラクトのデプロイ
  * デプロイスマートコントラクトへのアクセス

シンプルなスマートコントラクトであれば、Neocompilerのみで開発を行うことができます。

それでは実際にスマートコントラクトの作成を始めていきましょう。

=== スマートコントラクトの作成
まずはNeocompilerにアクセスします。

 : Neocompiler
  https://neocompiler.io/#/ecolab

今回はExample（サンプルコード）の中から、C#の"HelloWorldNotification.cs"を使用して手順を説明します。

//image[neoc_example]["Select Example" から "HelloWorldNotification.cs"を選択する][scale=0.9]{
//}

"HelloWorldNotification.cs"のコントラクトの中身は次のとおりです。

//emlist{
  using Neo.SmartContract.Framework.Services.Neo;

  namespace Neo.SmartContract
  {
      public class HelloWorldNotification : Framework.SmartContract
      {
          public static void Main()
          {
              Runtime.Notify("Hello World");
          }
      }
  }
//}

これは、実行時に"Hello World"と表示するための簡単なコントラクトです。

それでは、この作成したコントラクトをコンパイルしてみましょう。

=== 作成したスマートコントラクトのコンパイル

画面の下の方に移動すると[Compile]と書かれたボタンがあるのでクリックします。
このとき、BaseNetworkに"NeoCompiler Eco"が選択されていることを確認してください。

//image[neoc_compiled][コンパイル終了後の画面][scale=0.9]{
//}

C#で書かれた言語をNEOが理解できるようにAVM形式に変換しています。
コンパイルが終了すると上記のようにAVMが出力されるのでしばらくお待ちください。

コンパイルが終了したら、コントラクトのデプロイを行ってみましょう。

=== コンパイルしたスマートコントラクトのデプロイ
スマートコントラクトをブロックチェーンに展開し、使用可能な状態にしましょう。

左側の[Deploy & Invoke]を選択し、BaseNetworkをLocalhostに設定します。
これによって、Neocompilerがneo-localで構築したローカルの環境に対して操作を行えるようになります。

//image[neoc_deployinvoke][Deploy & Invoke][scale=0.9]{
//}

画面の下の方にある"Deploy contract into the Blockchain"の"DEPLOY"をクリックします。

//image[neoc_deploy][Deploy Buttonをクリック][scale=0.9]{
//}

次のようなポップアップメッセージが表示され、Activityページに遷移します。

//image[neoc_popup][Deployが成功][scale=0.9]{
//}

ポップアップメッセージのOKを押した後、Activityページの"Histrical Relayed Tx's"にトランザクションが表示されます。

//image[neoc_deloyed][トランザクションの状態はここで確認可能][scale=0.9]{
//}

デプロイ時にはneo-localにもメッセージが表示されます。

//image[neoc_local][Deploy時のNEO環境のメッセージ][scale=0.9]{
//}

デプロイが終了すると、"Histrical Relayed Tx's"の"TX on NeoScan"にもトランザクションを確認することができます。

//image[neoc_api][NeoScanのメッセージ][scale=0.9]{
//}

これでスマートコントラクトのデプロイは完了です。
それでは、デプロイスマートコントラクトへのアクセスをしてみましょう。

=== デプロイスマートコントラクトへのアクセス

左側の[Deploy & Invoke]を選択し、"Interacting with a SmartContract"からInvokeをクリックします。

//image[neoc_invoke][Invoke Buttonをクリック][scale=0.9]{
//}

コントラクトが実行されると、NEO環境に次のようなメッセージが出力されていると思います。

//emlist{
[SmartContract.Runtime.Notify][9385] [d71ee2627458f77b92d98751c3b6798a85ac86b6]
 [tx 82df6bf2d20410c77c87e1f02c339be13184ace3d1669ae8aef912d39c426ea7]
 {'type': 'Array', 'value': [{'type': 'ByteArray', 'value': b'Hello World'}]}
//}

//image[neoc_runtime][neo環境上のデバッグログ][scale=0.9]{
//}

以上がスマートコントラクトの簡単な開発手順です。
それでは、次にデプロイしたコントラクトにアクセスするためのフロントエンドをJavascriptで作成してみましょう。

== フロントエンドからのスマートコントラクト呼び出し

ここではNEO用JavascriptSDKであるNeon-jsを使用します。
npmまたはCDNでインストールすることができます。

//cmd{
# npm
npm i @cityofzion/neon-js
# CDN
<script src="https://unpkg.com/@cityofzion/neon-js" />
//}

サンプルコードは次のとおりです。

//emlist[sc-access.js]{
  //Neon-jsの読み込み
  var Neon = require('@cityofzion/neon-js');

  //API providerを読み込んでAPIの作成
  //LocalhostのNeoScanのAPIを指定
  var apiProvider = new Neon.api.neoscan.instance('http://localhost:4000/
	api/main_net')

  //Private Key(WIF)の読み込でAccountのインスタンスを作成
  var acct = new Neon.wallet.Account(
      //WIF
      "KxDgvEKzgSBPPfuVfw67oPQBSjidEiqTHURKSDL1R7yGaGYAeYnr"
  );

  //Scriptの作成
  var script = Neon.default.create.script({
      //Contractデプロイ時に生成されるScriptHash
      scriptHash: "d71ee2627458f77b92d98751c3b6798a85ac86b6",
      //今回はMethodがないのでブランク
      operation: "",
      //今回はargumentsがないのでブランク
      args: []
  })

  //api, accountの用意
  var config = {
      api: apiProvider, //The network to perform the action, MainNet or TestNet
      account: acct, // This is the address which the assets come from.
      script: script,
      gas: 1
    };

  Neon.default.doInvoke(config)
    .then(config => {
      console.log(config.response);
    })
    .catch(config => {
      console.log(config);
    });
//}

neo-localを立ち上げたのち、上記のコードを実行すると、コンソール画面に"Hello world"と表示されるはずです。
これで、先ほど作成したNEOのコントラクトを呼び出すことができました。

以上が、はじめてのdApps開発となります。

Neon-jsにはNEOの開発を促進するさまざまな機能があるので、詳しい使い方は下記を参考にしてみてください。

 : neon-js
  @<href>{http://cityofzion.io/neon-js/docs/en/installation.html}
