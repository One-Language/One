<div align="center">

<p>
    <a href="https://onelang.org/">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="The One Programming Language">
    </a>
</p>

# One 프로그래밍 언어 💚 💙 🧡 🤍 💖 🖤

[Onelang.org](https://onelang.org) |
[Help wanted](https://github.com/One-Language/One/issues/new)

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
[한국어](README_KR.md)
&nbsp;
[русский](README_RU.md)
&nbsp;
[Türkçe](README_TR.md)
&nbsp;
[Українська](README_UK.md)

</div>

<a href="https://onelang.org">One</a>에 오신 것을 환영합니다!</br>
오픈 소스, 자체 호스팅, 부트스트랩 <b>시스템 프로그래밍 언어</b>로
안정적이고 효율적인 소프트웨어를 구축합니다.
<a href="https://github.com/BaseMax">Max</a>, <a href="https://github.com/jbampton">John</a> 및 기타 오픈 소스 기여자.

### Compiler for the One Language는 몇 달 안에 출시될 예정입니다.

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- 목차 -->
<h2 id="table-of-contents">목차</h2>
<details open="open">
   <ol>
     <li><a href="#features-of-one"><b>One</b></a>의 기능</li>
     <li><a href="#roadmap">로드맵</a></li>
     <li><a href="#code-examples">코드 예</a></li>
     <li><a href="#getting-started">시작하기</a></li>
     <li><a href="#get-involved">참여하기</a></li>
     <li><a href="#license">라이선스</a></li>
   </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ One의 기능</h2>

- 단순성
- 컴파일러
- 출력 파일 생성 기능(x86_64, i386)
- 시스템 프로그래밍 언어
- 중급
- 네트워크 및 API 프로그래밍
- 웹 프로그래밍 지원(향후)
   - CSS와 HTML 모두에 해당하는 코드의 자동 생성. 따라서 웹사이트를 개발하기 위해 '하나의' 언어 이상을 배울 필요가 없습니다.
   - CSS에서 변수를 사용하여 데이터베이스에서 색상이나 크기를 얻을 수 있습니다.
   - 페이지 결과 자동 축소
- 성능 및 고속
- 인라인 어셈블리 코드 지원(향후)
- 일반 모드에서 사용자 시스템에 특정 라이브러리 및 도구가 필요하지 않음(향후)
- 일반 모드에서 외부 런타임 라이브러리가 필요하지 않음(향후)
- 컴파일을 위해 외부 컴파일러가 필요하지 않음(향후)

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ 로드맵</h2>

'One' 언어의 문법은 [여기](../grammar.BNF)에서 볼 수 있습니다.

- [x] 렉서/파서(대부분)
- [x] AST 트리
- [x] VM
- [ ] 코드 생성기(LLVM-C에서 영감을 얻음)
- [ ] 런타임 라이브러리 개발 및 기능 추가
- [ ] 언어에 대한 웹 프레임워크 설계
- [ ] `One` 언어로 컴파일러 재작성

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="code-examples">➤ 코드 </h2>
<!--Will have to explain how variable assignment, control flow, function declaration and call etc work in the language-->

```c
main {
   ret 0
}
```

**C로 변환:**

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

**C로 변환:**

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

**C로 변환:**

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

**또 다른 초안:**

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

**또 다른 초안:**

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

### 이전 CLI 개발

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

###  GUI 개발: (웹, 소프트웨어)

이 아키텍처는 웹 사이트 및 기본 소프트웨어용으로만 설계되었습니다. 앞으로 모바일 앱(네이티브)에서도 사용할 수 있습니다.<br>
모바일 구조는 아직 완성되지 않았으며 더 많은 주의와 생각이 필요합니다.<br><br>언어 작동을 보여주는 예:

```css
title "Name - Main"
description "Descriptions"
/*
Keyword tag not used in the software, only on the web.
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

**CSS/HTML/JS 기반으로 변환:**

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

<h2 id="getting-started">➤ 시작하기</h2>

언어 학습을 시작하려면 [이 링크](https://github.com/ET-Lang/ET/wiki)를 참조하세요.

<!--Installation Steps-->

<!--Prerequisites-->

#### 지원되는 환경

- [x] GNU / Linux <!--which Linux?-->
- [x] Windows
- [ ] macOS (Not complete)
- [ ] BSD

<!--Write more about the compiler-->
<!--Steps-->
<!--Building One from Source-->
<!--Hello World in One-->
<!--Tips to understand the language better-->
<!--Filename extensions: `.one`-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!--Get Involved-->
<h2 id="get-involved">➤ 참여하기</h2>

버그 보고서, 기능 요청, 문서 개선 등을 포함한 모든 종류의 기여를 환영합니다.
질문을 하거나 토론을 열려면 문제를 만들거나 <a href ="https://discord.gg/sFCE2HcMCa"><b>One</b> Discord Server</a>에 가입하세요.

GitHub에서 pull 요청하는 방법에 익숙하지 않다면 이 [가이드](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).

기여하기로 결정하셨다면 먼저 [여기](../CONTRIBUTING.md) 가이드라인을 읽어주세요.
<br>[:heart: Patreon](https://www.patreon.com/onelanguage)에서 기부를 통해 'One' 개발에 도움을 줄 수도 있습니다.

모든 <a href ="https://github.com/One-Language/One/graphs/contributors">기고자</a>에게 감사드립니다!!

이 프로젝트의 개발에 기여하고 싶다면 <maxbasecode@gmail.com>으로 메일을 보내주십시오.

<br>Created By Max Base @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="license">➤ 라이선스</h2>

`One`은 GNU General Public License v3.0에 따라 출시되었습니다. 저장소에 포함된 <a href="https://github.com/One-Language/One/blob/master/LICENSE">라이센스</a> 파일의 용어를 참조하십시오.

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
