<div align="center">

<p>
    <a href="https://onelang.org/">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="The One Programming Language">
    </a>
</p>

# The One Programming Language 💚 💙 🧡 🤍 💖 🖤

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

<!-- prettier-ignore-start -->
<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
[![All Contributors](https://img.shields.io/badge/all_contributors-31-orange.svg?style=flat-square)](#contributors-)
<!-- ALL-CONTRIBUTORS-BADGE:END -->
<!-- prettier-ignore-end -->

[English](README.md)
&nbsp;
[عربي](langs/README_AR.md)
&nbsp;
[Español](langs/README_ES.md)
&nbsp;
[فارسی](langs/README_FA.md)
&nbsp;
[Filipino](langs/README_FIL.md)
&nbsp;
[Français](langs/README_FR.md)
&nbsp;
[Italiano](langs/README_IT.md)
&nbsp;
[日本語](langs/README_JA.md)
&nbsp;
[русский](langs/README_RU.md)
&nbsp;
[Türkçe](langs/README_TR.md)
&nbsp;
[Українська](langs/README_UK.md)

</div>

<a href="https://onelang.org">One</a>에 오신 것을 환영합니다!</br>
오픈 소스, 자체 호스팅, 부트스트랩 <b>시스템 프로그래밍 언어</b>로
안정적이고 효율적인 소프트웨어를 구축합니다.
<a href="https://github.com/BaseMax">Max</a>, <a href="https://github.com/jbampton">John</a> 및 기타 오픈 소스 기여자.

### Compiler for the One Language will be released in a few months

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- TABLE OF CONTENTS -->
<h2 id="table-of-contents">Table of Contents</h2>
<details open="open">
  <ol>
    <li><a href="#features-of-one">Features of <b>One</b></a></li>
    <li><a href="#roadmap">RoadMap</a></li>
    <li><a href="#code-examples">Code Examples</a></li>
    <li><a href="#getting-started">Getting Started</a></li>
    <li><a href="#get-involved">Get Involved</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ Features of One</h2>

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

<h2 id="roadmap">➤ RoadMap</h2>

'One' 언어의 문법은 [여기](grammar.BNF)에서 볼 수 있습니다.

- [x] 렉서/파서(대부분)
- [x] AST 트리
- [x] VM
- [ ] 코드 생성기(LLVM-C에서 영감을 얻음)
- [ ] 런타임 라이브러리 개발 및 기능 추가
- [ ] 언어에 대한 웹 프레임워크 설계
- [ ] `One` 언어로 컴파일러 재작성

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="code-examples">➤ Code Examples</h2>
<!--Will have to explain how variable assignment, control flow, function declaration and call etc work in the language-->

```c
main {
   ret 0
}
```

**Convert to C:**

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

**Convert to C:**

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

**Convert to C:**

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

**Another draft:**

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

**Another draft:**

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

### Old CLI Development

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

### Old GUI Development: (Web, Software)

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

**Convert to CSS/HTML/JS base:**

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

<h2 id="getting-started">➤ Getting Started</h2>

언어 학습을 시작하려면 [이 링크](https://github.com/ET-Lang/ET/wiki)를 참조하세요.

<!--Installation Steps-->

<!--Prerequisites-->

#### Supported Environments

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
<h2 id="get-involved">➤ Get Involved</h2>

버그 보고서, 기능 요청, 문서 개선 등을 포함한 모든 종류의 기여를 환영합니다.
질문을 하거나 토론을 열려면 문제를 만들거나 <a href ="https://discord.gg/sFCE2HcMCa"><b>One</b> Discord Server</a>에 가입하세요.

GitHub에서 pull 요청하는 방법에 익숙하지 않다면 이 [가이드](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to- pull-requests/about-pull-requests).

기여하기로 결정하셨다면 먼저 [여기](CONTRIBUTING.md) 가이드라인을 읽어주세요.
<br>[:heart: Patreon](https://www.patreon.com/onelanguage)에서 기부를 통해 'One' 개발에 도움을 줄 수도 있습니다.

모든 <a href ="https://github.com/One-Language/One/graphs/contributors">기고자</a>에게 감사드립니다!!

이 프로젝트의 개발에 기여하고 싶다면 <maxbasecode@gmail.com>으로 메일을 보내주십시오.

<br>Created By Max Base @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="license">➤ License</h2>

`One`은 GNU General Public License v3.0에 따라 출시되었습니다. 저장소에 포함된 <a href="https://github.com/One-Language/One/blob/master/LICENSE">라이센스</a> 파일의 용어를 참조하십시오.

<!--[![Gitter](https://badges.gitter.im/ET_lang/community.svg)](https://gitter.im/ET_lang/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)-->
<!--[Official Community for a chat and discuss.](https://spectrum.chat/et?tab=chat)-->

[discordbadge]: https://img.shields.io/discord/834373930692116531?label=Discord&logo=discord&logoColor=white
[facebookbadge]: https://img.shields.io/badge/Facebook-Up-brightgreen
[instagrambadge]: https://img.shields.io/badge/Instagram-Up-brightgreen
[licensebadge]: https://img.shields.io/github/license/One-Language/One
[patreonbadge]: https://img.shields.io/endpoint.svg?url=https%3A%2F%2Fshieldsio-patreon.vercel.app%2Fapi%3Fusername%3Donelanguage%26type%3Dpledges
[sponsorbadge]: https://camo.githubusercontent.com/da8bc40db5ed31e4b12660245535b5db67aa03ce/68747470733a2f2f696d672e736869656c64732e696f2f7374617469632f76313f6c6162656c3d53706f6e736f72266d6573736167653d254532253944254134266c6f676f3d476974487562
[twitterbadge]: https://twitter.com/onelangteam
[discordurl]: https://discord.gg/sFCE2HcMCa
[facebookurl]: https://www.facebook.com/onelangteam
[instagramurl]: https://www.instagram.com/one.lang
[licenseurl]: https://github.com/One-Language/One/blob/master/LICENSE
[patreonurl]: https://patreon.com/onelanguage
[twitterurl]: https://img.shields.io/twitter/follow/onelangteam.svg?style=flatl&label=Follow&logo=twitter&logoColor=white&color=1da1f2

## Contributors ✨

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://maxbase.org/"><img src="https://avatars.githubusercontent.com/u/2658040?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Max Base</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=BaseMax" title="Code">💻</a> <a href="https://github.com/One-Language/One/issues?q=author%3ABaseMax" title="Bug reports">🐛</a> <a href="#business-BaseMax" title="Business development">💼</a> <a href="#content-BaseMax" title="Content">🖋</a> <a href="https://github.com/One-Language/One/commits?author=BaseMax" title="Documentation">📖</a> <a href="#example-BaseMax" title="Examples">💡</a> <a href="#ideas-BaseMax" title="Ideas, Planning, & Feedback">🤔</a> <a href="#infra-BaseMax" title="Infrastructure (Hosting, Build-Tools, etc)">🚇</a> <a href="#maintenance-BaseMax" title="Maintenance">🚧</a> <a href="#mentoring-BaseMax" title="Mentoring">🧑‍🏫</a> <a href="#projectManagement-BaseMax" title="Project Management">📆</a> <a href="#question-BaseMax" title="Answering Questions">💬</a> <a href="https://github.com/One-Language/One/pulls?q=is%3Apr+reviewed-by%3ABaseMax" title="Reviewed Pull Requests">👀</a> <a href="https://github.com/One-Language/One/commits?author=BaseMax" title="Tests">⚠️</a></td>
    <td align="center"><a href="https://github.com/jbampton"><img src="https://avatars.githubusercontent.com/u/418747?v=4?s=100" width="100px;" alt=""/><br /><sub><b>John Bampton</b></sub></a><br /><a href="#projectManagement-jbampton" title="Project Management">📆</a> <a href="#business-jbampton" title="Business development">💼</a> <a href="https://github.com/One-Language/One/commits?author=jbampton" title="Code">💻</a> <a href="https://github.com/One-Language/One/commits?author=jbampton" title="Documentation">📖</a> <a href="#eventOrganizing-jbampton" title="Event Organizing">📋</a> <a href="#financial-jbampton" title="Financial">💵</a> <a href="#fundingFinding-jbampton" title="Funding Finding">🔍</a> <a href="#ideas-jbampton" title="Ideas, Planning, & Feedback">🤔</a> <a href="#infra-jbampton" title="Infrastructure (Hosting, Build-Tools, etc)">🚇</a> <a href="#maintenance-jbampton" title="Maintenance">🚧</a> <a href="#mentoring-jbampton" title="Mentoring">🧑‍🏫</a> <a href="https://github.com/One-Language/One/pulls?q=is%3Apr+reviewed-by%3Ajbampton" title="Reviewed Pull Requests">👀</a> <a href="https://github.com/One-Language/One/commits?author=jbampton" title="Tests">⚠️</a> <a href="#tutorial-jbampton" title="Tutorials">✅</a> <a href="#talk-jbampton" title="Talks">📢</a></td>
    <td align="center"><a href="https://github.com/basalumutgazi"><img src="https://avatars.githubusercontent.com/u/81925269?v=4?s=100" width="100px;" alt=""/><br /><sub><b>basalumutgazi</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=basalumutgazi" title="Documentation">📖</a> <a href="#translation-basalumutgazi" title="Translation">🌍</a> <a href="#projectManagement-basalumutgazi" title="Project Management">📆</a> <a href="#mentoring-basalumutgazi" title="Mentoring">🧑‍🏫</a></td>
    <td align="center"><a href="https://github.com/n4i9kita"><img src="https://avatars.githubusercontent.com/u/60391776?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Nikita Sharma</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=n4i9kita" title="Documentation">📖</a></td>
    <td align="center"><a href="http://aaronmeese.com"><img src="https://avatars.githubusercontent.com/u/17814535?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Aaron Meese</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=ajmeese7" title="Documentation">📖</a></td>
    <td align="center"><a href="https://github.com/tHe-AK"><img src="https://avatars.githubusercontent.com/u/19654243?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Akshay Kapoor</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=tHe-AK" title="Documentation">📖</a></td>
    <td align="center"><a href="https://allcontributors.org"><img src="https://avatars.githubusercontent.com/u/46410174?v=4?s=100" width="100px;" alt=""/><br /><sub><b>All Contributors</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=all-contributors" title="Documentation">📖</a></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/features/security"><img src="https://avatars.githubusercontent.com/u/27347476?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Dependabot</b></sub></a><br /><a href="#maintenance-dependabot" title="Maintenance">🚧</a> <a href="#security-dependabot" title="Security">🛡️</a></td>
    <td align="center"><a href="https://kotbiabderrahmane.web.app/"><img src="https://avatars.githubusercontent.com/u/37270435?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Kotbi Abderrahmane</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=abdorah" title="Code">💻</a> <a href="https://github.com/One-Language/One/commits?author=abdorah" title="Documentation">📖</a></td>
    <td align="center"><a href="https://github.com/jassab"><img src="https://avatars.githubusercontent.com/u/41446786?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Jas</b></sub></a><br /><a href="#design-jassab" title="Design">🎨</a></td>
    <td align="center"><a href="https://www.upwork.com/freelancers/~013dd1f9db3380689d"><img src="https://avatars.githubusercontent.com/u/81928799?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Mujahid Al-Majali</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=Majalian" title="Documentation">📖</a> <a href="#projectManagement-Majalian" title="Project Management">📆</a></td>
    <td align="center"><a href="https://github.com/Anderson-Garcia"><img src="https://avatars.githubusercontent.com/u/68165804?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Anderson García</b></sub></a><br /><a href="#translation-Anderson-Garcia" title="Translation">🌍</a></td>
    <td align="center"><a href="https://rayhanadev.vercel.app/"><img src="https://avatars.githubusercontent.com/u/72509475?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Ray Arayilakath</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=RayhanADev" title="Documentation">📖</a></td>
    <td align="center"><a href="https://bandism.net/"><img src="https://avatars.githubusercontent.com/u/22633385?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Ikko Ashimine</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=eltociear" title="Documentation">📖</a></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/murataka"><img src="https://avatars.githubusercontent.com/u/5358438?v=4?s=100" width="100px;" alt=""/><br /><sub><b>murat aka</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=murataka" title="Code">💻</a></td>
    <td align="center"><a href="http://amir-shiati.github.io/"><img src="https://avatars.githubusercontent.com/u/47950086?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Amir</b></sub></a><br /><a href="#translation-amir-shiati" title="Translation">🌍</a></td>
    <td align="center"><a href="https://github.com/Ubersetzerin"><img src="https://avatars.githubusercontent.com/u/82717753?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Ubersetzerin</b></sub></a><br /><a href="#translation-Ubersetzerin" title="Translation">🌍</a></td>
    <td align="center"><a href="https://github.com/mafedeocampo"><img src="https://avatars.githubusercontent.com/u/85558716?v=4?s=100" width="100px;" alt=""/><br /><sub><b>mafedeocampo</b></sub></a><br /><a href="#translation-mafedeocampo" title="Translation">🌍</a></td>
    <td align="center"><a href="https://github.com/mohitsaxenaknoldus"><img src="https://avatars.githubusercontent.com/u/76725454?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Mohit Saxena</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=mohitsaxenaknoldus" title="Documentation">📖</a> <a href="https://github.com/One-Language/One/commits?author=mohitsaxenaknoldus" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/pedramcvx1"><img src="https://avatars.githubusercontent.com/u/87372623?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Pedram Lotfi</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=pedramcvx1" title="Documentation">📖</a></td>
    <td align="center"><a href="https://jdrprod.github.io/"><img src="https://avatars.githubusercontent.com/u/16467095?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Arthur Correnson</b></sub></a><br /><a href="#translation-jdrprod" title="Translation">🌍</a></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/mikey-b"><img src="https://avatars.githubusercontent.com/u/1836123?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Michael Brown</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=mikey-b" title="Code">💻</a></td>
    <td align="center"><a href="https://xahmed.com/"><img src="https://avatars.githubusercontent.com/u/79005095?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Ahmed.</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=xahmd" title="Documentation">📖</a></td>
    <td align="center"><a href="https://github.com/parsa011"><img src="https://avatars.githubusercontent.com/u/43126637?v=4?s=100" width="100px;" alt=""/><br /><sub><b>parsa mahmoudy</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=parsa011" title="Documentation">📖</a></td>
    <td align="center"><a href="https://restyled.io"><img src="https://avatars.githubusercontent.com/u/65077583?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Restyled Commits</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=restyled-commits" title="Code">💻</a></td>
    <td align="center"><a href="https://github.com/Kkkkkk58"><img src="https://avatars.githubusercontent.com/u/55288330?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Karim Khasan</b></sub></a><br /><a href="#translation-Kkkkkk58" title="Translation">🌍</a></td>
    <td align="center"><a href="https://github.com/ihasidul"><img src="https://avatars.githubusercontent.com/u/32800356?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Hasidul Islam</b></sub></a><br /><a href="https://github.com/One-Language/One/pulls?q=is%3Apr+reviewed-by%3Aihasidul" title="Reviewed Pull Requests">👀</a></td>
    <td align="center"><a href="http://danyb0.me"><img src="https://avatars.githubusercontent.com/u/66164380?v=4?s=100" width="100px;" alt=""/><br /><sub><b>DanyB0</b></sub></a><br /><a href="#translation-DanyB0" title="Translation">🌍</a></td>
  </tr>
  <tr>
    <td align="center"><a href="https://github.com/alesar1"><img src="https://avatars.githubusercontent.com/u/54070865?v=4?s=100" width="100px;" alt=""/><br /><sub><b>alesar1</b></sub></a><br /><a href="#translation-alesar1" title="Translation">🌍</a></td>
    <td align="center"><a href="https://github.com/Gokul2003g"><img src="https://avatars.githubusercontent.com/u/75162131?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Gokul</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=Gokul2003g" title="Documentation">📖</a></td>
    <td align="center"><a href="https://github.com/sokratisvas"><img src="https://avatars.githubusercontent.com/u/77175483?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Sokratis Vasiliou</b></sub></a><br /><a href="https://github.com/One-Language/One/commits?author=sokratisvas" title="Documentation">📖</a></td>
  </tr>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome! 🩱 🕐 1️⃣ 🔂
