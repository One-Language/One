<div align="center">

<p>
    <a href="https://onelang.org/">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="Il linguaggio di programmazione One">
    </a>
</p>

# Il linguaggio di programmazione One 💚 💙 🧡 🤍 💖 🖤

[Onelang.org](https://onelang.org) |
[Chiedi aiuto](https://github.com/One-Language/One/issues/new)

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
[![All Contributors](https://img.shields.io/badge/all_contributors-27-orange.svg?style=flat-square)](#contributors-)
<!-- ALL-CONTRIBUTORS-BADGE:END -->
<!-- prettier-ignore-end -->

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
[Italiano](README_IT.md)
&nbsp;
[русский](README_RU.md)
&nbsp;
[Türkçe](README_TR.md)
&nbsp;
[Українська](README_UK.md)

</div>

Benvenuto a <a href="https://onelang.org">One</a>!</br>
É un <b>linguaggio di programmazione</b> open source, auto-hostato, che rende semplice creare software efficiente e affidabile.
É sviluppato da <a href="https://github.com/BaseMax">Max</a>, <a href="https://github.com/jbampton">John</a> e altri contributori open-source.

### Il compilatore per il linguaggio One sarà rilasciato tra pochi mesi

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- TABLE OF CONTENTS -->
<h2 id="table-of-contents">Indice</h2>
<details open="open">
  <ol>
    <li><a href="#features-of-one">Funzionalità di <b>One</b></a></li>
    <li><a href="#roadmap">RoadMap</a></li>
    <li><a href="#code-examples">Esempi di codice</a></li>
    <li><a href="#getting-started">Per iniziare</a></li>
    <li><a href="#get-involved">Per partecipare</a></li>
    <li><a href="#license">Licenza</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ Funzionalità di One</h2>

- Semplicità
- Compilatore
- Possibilità di creare file in output (x86_64, i386)
- Linguaggio di programamzione di sistema
- Livello intermedio
- Programmazione network e API
- Supporto per la programamzione Web (in futuro)
  - Generazione automatica del codice corrispondente sia per CSS che per HTML. Così non dovrai imparare più di `One` linguaggio per sviluppare un sito web
  - Utilizzo delle variabili in CSS, in modo tale da ottenere i colori o le dimensioni da un database
  - Minimizzazione automatica dei risultati della pagina
- Performance e alta velocità
- Supporto inline per il codice Assembly (in futuro)
- Non richede librerie o tool specifici nel sistema dell'utente in modalità normale (in futuro)
- Non richede librerie di runtime esterne in modalità normale (in futuro)
- Non richede compilatori esterni per effettuare la compilazione (in futuro)

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ RoadMap</h2>

La sintaassi del linguaggio `One` è disponibile [qui](grammar.BNF).

- [x] Lexer/Parser (Mostly)
- [x] AST Tree
- [x] VM
- [ ] Generatore di codice (ispirato da LLVM-C)
- [ ] Sviluppare una libreria di runtime e aggiungere funzionalità
- [ ] Creare un web framework per il linguaggio
- [ ] Riscrivere il compilatore in linguaggio `One`

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="code-examples">➤ Esempi di codice</h2>
<!--Will have to explain how variable assignment, control flow, function declaration and call etc work in the language-->

```c
main {
   ret 0
}
```

**Equivalente in C:**

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

**Equivalente in C:**

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

**Equivalente in C:**

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

**Un altro esempio:**

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

**Un altro esempio:**

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

### Vecchio sviluppo CLI

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

### Vecchio sviluppo GUI: (Web, Software)

Questa architettura è disegnata solo per siti web e software nativo. In futuro, sarà disponibile anche per applicazioni mobili (native).<br>
Le strutture mobili non sono ancora complete e hanno bisogno di più attenzione.<br><br>Esempio per dimostrare il funzionamento del linguaggio:

```css
title "Name - Main"
description "Descriptions"
/*
il tag keyword non è usato nel software, solo sul web.
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

**Equivalente in CSS/HTML/JS base:**

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

<h2 id="getting-started">➤ Per iniziare</h2>

Fai riferimento a [questo link](https://github.com/ET-Lang/ET/wiki) per iniziare ad imparare il linguaggio.

<!--Installation Steps-->

<!--Prerequisites-->

#### Ambienti supportati

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
<h2 id="get-involved">➤ Per partecipare</h2>

Sono benvenute tutte le tipologie di contributo, inclusi bug reports, richieste di nuove funzionalità, miglioramento della documentazione etc.
Per fare una domanda o aprire una discussione, crea un'issue o unisciti al <a href ="https://discord.gg/sFCE2HcMCa">server Discord di <b>One</b></a>.

Se non sai come fare una Pull Request su GitHub per favore leggi questa [guida](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).

Se vuoi contribuire, per favore leggi le linee guida [qui](CONTRIBUTING.md).
<br>Puoi anche aiutare nello svilupo di `One` facendo una donazione su [:heart: Patreon](https://www.patreon.com/onelanguage).

Grazie a tutti i <a href ="https://github.com/One-Language/One/graphs/contributors">contributori</a>!!

Se vuoi contribuire allo sviluppo di questo progetto, puoi contattarci a: <maxbasecode@gmail.com>

<br>Creato da Max Base @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="license">➤ Licenza</h2>

`One` è rilasciato sotto la GNU General Public License v3.0. Per favore fai riferimento ai termini nel file <a href="https://github.com/One-Language/One/blob/master/LICENSE">LICENSE</a> incluso nel repository.

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

## Contributori ✨

Un grazie a tutte queste persone fantastiche ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

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
  </tr>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

Questo progetto segue le specifiche di [all-contributors](https://github.com/all-contributors/all-contributors). I contributi di ogni tipo sono i benvenuti! 🩱 🕐 1️⃣ 🔂
