<div align="center">

<p>
    <a href="https://onelang.org/" alt="The One Programming Language">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="The One Programming Language">
    </a>
</p>

# Ang Isang Programang Lengguwahe 💚 💙 🧡 🤍 💖 🖤

[Onelang.org](https://onelang.org) |
[Tulong](https://github.com/One-Language/One/issues/new)

</div>
<div align="center">

<!--
[![Build Status][WorkflowBadge]][WorkflowUrl]
-->

[![Patreon][patreonbadge]][patreonurl]
[![Discord][discordbadge]][discordurl]
[![Twitter][twitterurl]][twitterbadge]

[English](README.md)
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
[русский](README_RU.md)
&nbsp;
[Türkçe](README_TR.md)
&nbsp;
[Українська](README_UK.md)

</div>

Maligayang pagdating sa <a href="https://onelang.org">One</a>!</br>
Ito ay isang open source, self-hosted, bootstrapping <b>programang lengguwahe</b> upang madaling makabuo ng maaasahan at mahusay na software.
Ito ay dinebelop ng <a href="https://github.com/BaseMax">Max</a>, <a href="https://github.com/jbampton">John</a> at ng iba pang may akda

### Ang mga may akda ng Isang Lengguwahe ay mailalabas sa loob ng ilang buwan

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- TALAAN NG NILALAMAN -->
<h2 id="table-of-contents">Talaan ng Nilalaman</h2>
<details open="open">
  <ol>
    <li><a href="#features-of-one">Katangian ng <b>One</b></a></li>
    <li><a href="#roadmap">Daan ng Mapa</a></li>
    <li><a href="#code-examples">Halimbawa ng Code</a></li>
    <li><a href="#getting-started">Panimula</a></li>
    <li><a href="#get-involved">Pakikisalamuha</a></li>
    <li><a href="#license">Lisensya</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ Katangian ng One</h2>

- Simple
- Tagatala
- Kakayahang makagawa ng output file (x86_64, i386)
- Sistema ng Programang Lengguwahe
- Kalagitnaang lebel
- Pagprograma ng network at API
- Suporta sa Programang Web (sa hinaharap)
  - Awtomatikong pagbuo ng naaayon na code para sa CSS at HTML. Para hindi ka na mag-aral ng higit sa "One" lengguwahe upang makabuo ng website.
  - Gumagamit ng variables sa CSS, upang makakuha ng kulay at sukat galing sa database
  - Awtomatik na pagliit ng resultang pahina
- Pagsasagawa at mabilis
- Suporta sa inline Assembly code (sa hinaharap)
- Hindi nangangailangan ng tiyak na aklatan at kagamitan sa sistema ng gumagamit sa normal mode (sa hinaharap)
- Hindi nangangailangan ng panlabas na runtime aklatan sa normal mode (sa hinaharap)
- Hindi nangangailangan ng panlabas na tagatalang aklatan sa normal mode (sa hinaharap)

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ RoadMap</h2>

Magagamit ang `One` grammar [dito](grammar.BNF).

- [x] Lexer/Parser (Karamihan)
- [x] Arbol AST
- [x] VM
- [ ] Gumagawa ng Code (inspirasyon ng LLVM-C)
- [ ] Bumuo ng isang runtime aklata at magdagdag ng katangian
- [ ] Mag-disenyo ng arkitektura sa web para sa lengguwahe
- [ ] Isulat muli ang tagatala sa `One` lengguwahe

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="code-examples">➤ Halimbawa ng Code</h2>
<!--Will have to explain how variable assignment, control flow, function declaration and call etc work in the language-->

```c
main {
   ret 0
}
```

**Convertir a C:**

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

**Convertir a C:**

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

**Convertir a C:**

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

**Isa pang halimbawa:**

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

**Isa pang halimbawa:**

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

### Nakaraang pag-unlad ng CLI

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

### Nakaraang pag-unlad ng GUI: (Web, Software)

Ang arkitekturang ito ay dinisenyo para sa katutubong software at mga website lamang. Sa hinaharap, magagamit din ito para sa mga mobile application. (katutubo).<br>
Ang mga estraktura na ito ay hindi pa nakukumpleto at nangangailangan pa rin ng pansin at dedikasyon.<br><br>Ang sumusunod ay isang halimbawa kung paano gumagana ang lengguwahe:

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

**I-convert ang base CSS/HTML/JS:**

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

<h2 id="getting-started">➤Mga Unang Hakbang</h2>

Maaari mong suriin ang [link na ito](https://github.com/ET-Lang/ET/wiki) upang simulang matuto ng wika.

<!--Mga hakbang para sa pag-install-->

<!--Mga Pangangailangan-->

#### Mga sinusuportahang kapaligiran

- [x] GNU / Linux <!--which Linux?-->
- [x] Windows
- [ ] macOS (Hindi kumpleto)
- [ ] BSD

<!--Sumulat ng higit pa tungkol sa tagatala-->
<!--Mga Hakbang-->
<!--Isang Bituin mule sa Pinagmulan-->
<!--Kamusta Mundo sa Isa-->
<!--Mga tip upang mas maunawaan ang wika-->
<!--Pangalan ng mga extension: `.one`-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!--Get Involved-->
<h2 id="get-involved">➤ Pakikiugnay</h2>

Tumatanggap kami ng anumang uri ng mga kontribusyon, kabilang ang ulat ng mga bug, paghiling ng tampok, pagpapahusay ng dokumentasyon, atbp.
Upang magtanong o magsimula ng isang Pag-uusap, gumawa ng isang isyu o sumali sa <a href ="https://discord.gg/sFCE2HcMCa"><b>One</b> Servidor de Discord</a>.

Kung hindi ka pamilyar sa proseduring upang gumawa ng isang kahilingan sa paghila sa GitHub maaari mong suriin ang na ito [gabay](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).

Kung nagpasya kang mag-ambag, mangyaring suriin ang mga alituntunin [dito](CONTRIBUTING.md).
<br>Maaari mo ring tulungan ang pagbuo ng `One` sa pamamagitan ng mga donasyon sa [:heart: Patreon](https://www.patreon.com/onelanguage).

Salamat sa lahat ng <a href ="https://github.com/One-Language/One/graphs/contributors">mga nag-ambag</a>!!

Kung nais mong magbigay ng kontribusyon sa pag-unlad ng proyektong ito, maaari kang sumulat sa amin sa: <maxbasecode@gmail.com>

<br>Created By Max Base @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="license">➤ Lisensya</h2>

Ang `One` ay inilabas sa ilalim ng GNU General Public License v3.0. Para sa pabor na suriin ang mga tuntunin sa file na <a href="https://github.com/One-Language/One/blob/master/LICENSE">LICENCIA</a> incluido en el repositorio.

<!--[![Gitter](https://badges.gitter.im/ET_lang/community.svg)](https://gitter.im/ET_lang/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)-->
<!--[Official Community for a chat and discuss.](https://spectrum.chat/et?tab=chat)-->

[discordbadge]: https://img.shields.io/discord/834373930692116531?label=Discord&logo=discord&logoColor=white
[patreonbadge]: https://img.shields.io/endpoint.svg?url=https%3A%2F%2Fshieldsio-patreon.vercel.app%2Fapi%3Fusername%3Donelanguage%26type%3Dpledges
[sponsorbadge]: https://camo.githubusercontent.com/da8bc40db5ed31e4b12660245535b5db67aa03ce/68747470733a2f2f696d672e736869656c64732e696f2f7374617469632f76313f6c6162656c3d53706f6e736f72266d6573736167653d254532253944254134266c6f676f3d476974487562
[twitterbadge]: https://twitter.com/onelangteam
[discordurl]: https://discord.gg/sFCE2HcMCa
[patreonurl]: https://patreon.com/onelanguage
[twitterurl]: https://img.shields.io/twitter/follow/onelangteam.svg?style=flatl&label=Follow&logo=twitter&logoColor=white&color=1da1f2
