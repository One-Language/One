<div align="center">

<p>
    <a href="https://onelang.org/">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="The One Programming Language">
    </a>
</p>

# One 言語 💚 💙 🧡 🤍 💖 🖤

[Onelang.org](https://onelang.org) |
[ヘルプ募集](https://github.com/One-Language/One/issues/new)

</div>
<div align="center">

<!--
[![Build Status][WorkflowBadge]][WorkflowUrl]
-->

[![Patreon][patreonbadge]][patreonurl]
[![Discord][discordbadge]][discordurl]
[![Facebook][facebookbadge]][facebookurl]
[![Instagram][instagrambadge]][instagramurl]
[![Twitter][twitterurl]][twitterbadge]
[![License][licensebadge]][licenseurl]

[English](../README.md)
&nbsp;
[عربي](README_AR.md)
&nbsp;
[Español](README_ES.md)
&nbsp;
[فارسی](README_FA.md)
&nbsp;
[Filipino](README_FIL.md)
&nbsp;
[Français](README_FR.md)
&nbsp;
[Italiano](README_IT.md)
&nbsp;
[日本語](README_JA.md)
&nbsp;
[русский](README_RU.md)
&nbsp;
[Türkçe](README_TR.md)
&nbsp;
[Українська](README_UK.md)

</div>

<a href="https://onelang.org">One</a>へようこそ!</br>
これは、オープン ソースの自己ホスト型ブートストラップ<b>システム プログラミング言語</b>であり、
信頼性が高く効率的なソフトウェアを構築します。
これは、<a href="https://github.com/BaseMax">Max</a>や<a href="https://github.com/jbampton">John</a>およびその他のオープンソースのコントリビュータによって開発されています。

### One 言語用のコンパイラは数か月以内にリリースされます

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- TABLE OF CONTENTS -->
<h2 id="table-of-contents">目次</h2>
<details open="open">
  <ol>
    <li><a href="#features-of-one"><b>One</b>の特徴</a></li>
    <li><a href="#roadmap">ロードマップ</a></li>
    <li><a href="#code-examples">コード例</a></li>
    <li><a href="#getting-started">入門</a></li>
    <li><a href="#get-involved">参加する</a></li>
    <li><a href="#license">ライセンス</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ Oneの特徴</h2>

- シンプルさ
- コンパイラ
- 出力ファイルを作成する機能(x86_64、i386)
- システムプログラミング言語
- 中間レベル
- ネットワークおよび API プログラミング
- Web プログラミングに対応（将来予定）
  - CSS と HTML の両方に対応したコードを自動生成します。そのため、ウェブサイトを開発するために複数の`One`言語を学ぶ必要がない
  - CSS で変数を使用するので、データベースから色やサイズを取得することができる
  - ページの結果を自動的に最小化する
- パフォーマンスと高速
- インラインアセンブリコードをサポート（将来予定）
- 通常モードではユーザーシステムに特定のライブラリとツールを必要としない（将来予定）
- 通常モードで外部ランタイムライブラリを必要としない（将来予定）
- コンパイルを行うために外部コンパイラを必要としない（将来予定）

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ ロードマップ</h2>

`One`言語の文法は[こちら](../grammar.BNF)。

- [x] レキサー／パーサー(ほとんど)
- [x] AST ツリー
- [x] VM
- [ ] コードジェネレータ(LLVM-C からヒントを得た)
- [ ] ランタイムライブラリの開発と機能追加
- [ ] この言語のためのウェブフレームワークをデザインする
- [ ] `One`言語でコンパイラを書き直す

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="code-examples">➤ コード例</h2>
<!--Will have to explain how variable assignment, control flow, function declaration and call etc work in the language-->

```c
main {
   ret 0
}
```

**C 言語への変換:**

```c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
   global_argc = argc;
   global_argv = argv;
   return (int) 0;
}
```

---

```c
i32 main {
   ret 10
}
```

**C 言語への変換:**

```c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
   global_argc = argc;
   global_argv = argv;
   return (int) 10;
}
```

---

```c
main {
   string in = "Hello, World!"
   __ in
   return in.length
}
```

**C 言語への変換:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
   global_argc = argc;
   global_argv = argv;
   char *in = "Hello, World!";
   printf("%s\n", in);
   return (int) strlen(in);
}
```

<hr>

**別のドラフト:**

```c
import web
home {
    _ "Hi, Welcome"
}
error {
    headers.add('HTTP-Type: 404')
    headers.add('Content-Type: text/html;charset=utf-8')
    _ "<h1>404></h1>"
}
main {
    if system.args.length === 2 {
        port = system.args[1]
    } else  {
        port=8080;
    }
    web.route.add("/", home)
    web.route.add("*", error)
    web.listen(port)
    return 0
}
```

---

**別のドラフト:**

```c
error {
    headers.add('HTTP-Type: 404')
    headers.add('Content-Type: text/html;charset=utf-8')
    _ `<!doctype html><html><head>title>Error 404</title><meta charset="utf-8"></head><body><h1>404></h1></body></html>`
}

vs

error {
    headers.add('HTTP-Type: 404')
    headers.add('Content-Type: text/html;charset=utf-8')
    page {
        title: 'Error 404'
        label {
            type: 'h1'
            _ "Not found!"
        }
    }
}
```

---

### 古い CLI の開発

```
main:
   // __ "Hello, World!"
   _ "Hello,"
   io.write(' ')
   io.write("World")
   __ '!'
end
```

```
@start
customName:
   _ "Hello, World!\n"
end
```

```
@start
void app:
   __ "Hello, World!"
end
```

```
@start
int customName:
   _ "Hello, World!\n"
   return 0
end
```

<hr>

### 古い GUI 開発: (Web, GUI 開発)

このアーキテクチャは、Web サイトとネイティブソフトウェアのみを対象として設計されています。将来的には、モバイルアプリ（ネイティブ）でも利用できるようになる予定です。<br>
モバイル構造はまだ完全ではないので、もっと注意深く考える必要があります。<br><br>言語の動作を示す例:

```css
title "Name - Main"
description "Descriptions"
/*
キーワードタグはソフトウェア内では使用せず、Web上でのみ使用します。
*/
keyword "keywords"
style {
  * {
    margin 0
    padding 0
  }
  header {
    width "100%"
    height "auto"
  }
  list {
    color "red"
  }
  list item {
    display "inline"
    padding "10px"
    background "yellow"
  }
}
header {
  list {
    item {
      _ "Home"
    }
    item {
      _ "About"
    }
    item {
      _ "Contact Us"
    }
  }
}
```

**CSS/HTML/JS ベースへの変換:**

```html
<html>
  <head>
    <title>Name - Main</title>
    <meta name="description" content="Descriptions" />
    <meta name="keyword" content="keywords" />
    <style>
      * {
        margin: 0;
        padding: 0;
      }
      header {
        width 100%;
        height: auto;
      }
      ul {
        color: red;
      }
      ul li {
        display: inline;
        padding: 10px;
        background: yellow;
      }
    </style>
  </head>
  <body>
    <header>
      <ul>
        <li>Home</li>
        <li>About</li>
        <li>Contact Us</li>
      </ul>
    </header>
  </body>
</html>
```

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="getting-started">➤ 入門</h2>

[このリンク](https://github.com/ET-Lang/ET/wiki)を参照して、語学学習を始めてください。

<!--Installation Steps-->

<!--Prerequisites-->

#### 対応環境

- [x] GNU / Linux <!--which Linux?-->
- [x] Windows
- [ ] macOS (未完成)
- [ ] BSD

<!--Write more about the compiler-->
<!--Steps-->
<!--Building One from Source-->
<!--Hello World in One-->
<!--Tips to understand the language better-->
<!--Filename extensions: `.one`-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!--Get Involved-->
<h2 id="get-involved">➤ 参加する</h2>

バグレポート、機能リクエスト、ドキュメントの改善など、あらゆる種類のコントリビュートを歓迎します。
質問やディスカッションを行うには、issue を作成するか、<a href ="https://discord.gg/sFCE2HcMCa"><b>One</b> Discord Server</a>に参加してください。

GitHub でのプルリクエストのやり方がよくわからないという方は、こちらの[ガイド](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests)をご覧ください。

投稿を決意された方は、まず[こちら](../CONTRIBUTING.md)のガイドラインをお読みください。
<br>また、[:heart: Patreon](https://www.patreon.com/onelanguage)でいくらかの寄付をすることで、`One`の開発に協力することができます。

<a href ="https://github.com/One-Language/One/graphs/contributors">コントリビュータ</a>の皆様、ありがとうございました!!

このプロジェクトの開発にコントリビュートしたい方は、次のアドレスにメールを送ってください： <maxbasecode@gmail.com>

<br>作成者：Max Base @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="license">➤ ライセンス</h2>

`One`は GNU General Public License v3.0 の下でリリースされています。リポジトリに含まれる<a href="https://github.com/One-Language/One/blob/master/LICENSE">LICENSE</a>ファイルに記載されている条件を参照してください。

<!--[![Gitter](https://badges.gitter.im/ET_lang/community.svg)](https://gitter.im/ET_lang/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)-->
<!--[Official Community for a chat and discuss.](https://spectrum.chat/et?tab=chat)-->

[discordbadge]: https://img.shields.io/discord/834373930692116531?label=Discord&logo=discord&logoColor=white
[facebookbadge]: https://img.shields.io/badge/Facebook-Up-brightgreen
[instagrambadge]: https://img.shields.io/badge/Instagram-Up-brightgreen
[licensebadge]: https://img.shields.io/github/license/One-Language/One
[patreonbadge]: https://img.shields.io/endpoint.svg?url=https%3A%2F%2Fshieldsio-patreon.vercel.app%2Fapi%3Fusername%3Donelanguage%26type%3Dpledges
[twitterbadge]: https://twitter.com/onelangteam
[discordurl]: https://discord.gg/sFCE2HcMCa
[facebookurl]: https://www.facebook.com/onelangteam
[instagramurl]: https://www.instagram.com/one.lang
[licenseurl]: https://github.com/One-Language/One/blob/master/LICENSE
[patreonurl]: https://patreon.com/onelanguage
[twitterurl]: https://img.shields.io/twitter/follow/onelangteam.svg?style=flatl&label=Follow&logo=twitter&logoColor=white&color=1da1f2
