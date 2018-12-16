= はじめてのDapps
#@#担当者:@ookimaki
//lead{
この章では、実際にNEOを使ったDappsの開発手法について説明します。
シンプルなコントラクトを実行できるための手順についてまとめまています。
//}

== 概要
NEOを使ったDappsの開発には下記が必要です

  * NEOのローカル環境の構築
  * スマートコントラクトの開発
  * フロントエンドからのスマートコントラクトのアクセス

まずは簡単なコントラクトを実行できることを目標にしてみましょう。
それでは、NEOのローカル環境の構築から始めていきます。

== NEOのローカル環境の構築
ここではNeo-localを使用します。
Neo-localを使ったNEOのローカル環境の構築については、8章の「SDKや開発について」で詳しくまとめてありますので、ここでは割愛します。

ローカルにNEOの実行環境を構築できたら早速スマートコントラクトの開発を行ってみましょう。

== スマートコントラクトの開発
今回はできるだけ簡単にスマートコントラクトの開発を行うために、neocompiler<https://neocompiler.io>を使用します。

//image[neocompiler][neocompiler.io][scale=0.9]{
//}

Neocompilerではブラウザ上で

  * スマートコントラクトの作成（C#, Phython, Co, Java）
  * 作成したスマートコントラクトのコンパイル
  * コンパイルしたスマートコントラクトのデプロイ
  * デプロイスマートコントラクトへのアクセス

までを行うことができます。シンプルなスマートコントラクトならNeocompileのみで開発を行うことができます。
それでスマートコントラクトの作成を始めます。

=== スマートコントラクトの作成
まずはNeocompilerにアクセスします。
https://neocompiler.io/#/ecolab

今回はExampleの中から、"HelloWorldNotification.cs"を使用して手順を説明します。

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

コントラクト実行時に"Hello World"と表示するための簡単なコントラクトです。

それでは、この作成したコントラクトをコンパイルしてみましょう。

=== 作成したスマートコントラクトのコンパイル

画面の下の方に移動すると"Compile"とかかれたボタンがあるのでクリックします。

//image[neoc_compiled][コンパイル終了後の画面][scale=0.9]{
//}

C#で書かれた言語をNEOが理解できるようにAVM形式に変換しています。コンパイルが終了すると上記のようにAVMが出力されるのでしばらくお待ちください。

コンパイルが終了したら、コントラクトのデプロイを行ってみましょう。

=== コンパイルしたスマートコントラクトのデプロイ

左側のNetwork Essencialsを選択し、BaseNetworkをLocalhostに設定します。
ここではNeo-loccalを使用してローカルにNEOの環境を構築して置く必要があります。

//image[neoc_networkessencial][NetworkEssencials][scale=0.9]{
//}

画面の下の方にある"Deploy contract into the Blockchain"の"DEPLOY JS"をクリックします。

//image[neoc_deploy][Deploy Buttonをクリック][scale=0.9]{
//}

"Histrical Relayed Tx's"にトランザクションが表示されます。

//image[neoc_deloyed][トランザクションの状態はここで確認可能][scale=0.9]{
//}

デプロイ時にはNEO-localにもメッセージが表示されます。

//image[neoc_local][Deploy時のNEO環境のメッセージ][scale=0.9]{
//}

デプロイが終了すると、"Histrical Relayed Tx's"の"TX on NeoScan"にもトランザクションを確認することができます。

//image[neoc_api][NeoScanのメッセージ][scale=0.9]{
//}

これでスマートコントラクトのデプロイは完了です。
それでは、デプロイスマートコントラクトへのアクセスしてみましょう。

=== デプロイスマートコントラクトへのアクセス

"Interacting with a SmartContract"からInvoke JSをクリックします。

//image[neoc_invoke][Deploy Buttonをクリック][scale=0.9]{
//}

コントラクトが実行されると、NEO環境に次のようなメッセージが出力されていると思います。

//emlist{
[SmartContract.Runtime.Notify][9385] [d71ee2627458f77b92d98751c3b6798a85ac86b6]
 [tx 82df6bf2d20410c77c87e1f02c339be13184ace3d1669ae8aef912d39c426ea7]
 {'type': 'Array', 'value': [{'type': 'ByteArray', 'value': b'Hello World'}]}
//}

//image[neoc_runtime][Deploy Buttonをクリック][scale=0.9]{
//}

以上でスマートコントラクトの開発は終了です。
それでは、次にデプロイしたコントラクトにアクセスするためのフロントエンドをJavascriptで作成してみましょう。

== フロントエンドからのスマートコントラクトのアクセス

ここではNeon-js使用します。サンプルコードは次のとおりです。

//emlist{
  //Neon-jsの読み込み
  var Neon = require('@cityofzion/neon-js');

  //API providerの読み込んでAPIの作成
  //LocalhostのNeoScanのAPIを指定
  var apiProvider = new Neon.api.neoscan.instance('http://localhost:4000/
	api/main_net')

  //Private Keyの読み込でAccount
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

  //api, account
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

上記のコードを実行すると、NEOのコントラクトにアクセスすることができます。

Neon-jsの詳しい使い方は下記を参考にしてみてください。

@<href>{http://cityofzion.io/neon-js/docs/en/installation.html}
