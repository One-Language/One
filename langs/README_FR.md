<div align="center">

<p>
    <a href="https://onelang.org/">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="Langage de Programmation One">
    </a>
</p>

# Langage de Programmation One 💚 💙 🧡 🤍 💖 🖤

[Onelang.org](https://onelang.org) |
[Demande d'aide](https://github.com/One-Language/One/issues/new)

</div>
<div align="center">

<!--
[![Build Status][WorkflowBadge]][WorkflowUrl]
-->

[![Patreon][patreonbadge]][patreonurl]
[![Discord][discordbadge]][discordurl]
[![Twitter][twitterurl]][twitterbadge]
[![Instagram][instagrambadge]][instagramurl]
[![License][licensebadge]][licenseurl]
[![Facebook][facebookbadge]][facebookurl]

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

Bienvenue à <a href="https://onelang.org">One</a>!</br>
Il s'agit d'un langage de <b>programmation système</b>, d'amorçage, à source libre, et auto-hébergé, qui facilite la création de logiciels fiables et efficaces. Il est développé par <a href="https://github.com/BaseMax">Max</a>, <a href="https://github.com/jbampton">John</a>, et d'autres contributeurs en open-source.

### Le compilateur pour le langage One sera publié dans quelques mois

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- TABLE OF CONTENTS -->
<h2 id="table-of-contents">Table des matières</h2>
<details open="open">
  <ol>
    <li><a href="#fonctionnalités-de-one">Fonctionnalités de <b>One</b></a></li>
    <li><a href="#carte">Carte</a></li>
    <li><a href="#exemples-de-code">Exemples de code</a></li>
    <li><a href="#pour-commencer">Pour commencer</a></li>
    <li><a href="#pour-s-impliquer">Pour s'impliquer</a></li>
    <li><a href="#licence">Licence</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="fonctionnalités-de-one">➤ Fonctionnalités de One</h2>

- Simplicité
- Compilé
- Possibilité de créer un fichier de sortie (x86_64, i386)
- Langage de programmation système
- Niveau intermédiaire
- Programmation réseau et API
- Prise en charge de la programmation Web (prochainement)
  - Génération automatique du code correspondant pour CSS et HTML. Vous n'aurez donc pas besoin d'apprendre plus que le langage `One` pour développer un site web
  - Variables CSS pour l'utilisatino de couleurs ou de tailles prédéfinies
  - Minification automatique des résultats de la page
- Performances et vitesse élevée
- Prise en charge des fragments de code assembleur (prochainement)
- Ne nécessite pas de bibliothèques et d'outils spécifiques sur le système utilisateur en mode normal (prochainement)
- Ne nécessite pas de bibliothèques d'exécution externes en mode normal (prochainement)
- Ne nécessite pas de compilateurs externes pour effectuer la compilation (prochainement)

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="carte">➤ Feuille de route</h2>

La grammaire du langage `One` est disponible [ici](https://github.com/One-Language/One/blob/main/grammar.BNF).

- [x] Lexer/Parser (principalement)
- [x] Arbre AST
- [x] MV
- [ ] Générateur de code (inspirez-vous de LLVM-C)
- [ ] Développer une bibliothèque d'exécution et ajouter des fonctionnalités
- [ ] Concevoir un framework web pour le langage
- [ ] Réécrire le compilateur par le langage `One`

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="exemples-de-code">➤ Exemples de code</h2>
<!--Will have to explain how variable assignment, control flow, function declaration and call etc work in the language-->

```c
main {
   ret 0
}
```

### Équivalant en C :

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

### Équivalent en C :

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

### Équivalent en C :

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

### Brouillon

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

### Brouillon

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

### Développement de l'ancienne CLI

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

### Développement de l'ancienne interface graphique : (Web, logiciel)

Cette architecture est conçue uniquement pour les sites Web et les logiciels natifs. Prochainement, il sera également disponible pour les applications mobiles (natives).<br>
Les structures mobiles ne sont pas encore terminées et nécessitent plus d'attention et de réflexion.<br><br>Exemple pour démontrer le fonctionnement de la langue :

```css
title "Name - Main"
description "Descriptions"
/*
Balise de mot-clé non utilisée dans le logiciel, uniquement sur le web.
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

### Équivalant en CSS/HTML/JS :

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

<h2 id="pour-commencer">➤ Pour commencer</h2>

Référez-vous à [ce lien](https://github.com/ET-Lang/ET/wiki) pour commencer à apprendre la langue.

<!--Installation Steps-->

<!--Prerequisites-->

#### Environnements pris en charge

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
<h2 id="pour-s-impliquer">➤ Pour s'impliquer</h2>

Nous accueillons toutes sortes de contributions, y compris les rapports de bogues, les demandes de fonctionnalités, les améliorations de la documentation, etc. Pour poser une question ou ouvrir une discussion, créer un problème ou rejoindre le <a href ="https://discord.gg/sFCE2HcMCa">Serveur Discord<b>One</b></a>.

Si vous ne savez pas comment faire une pull request sur GitHub, veuillez lire ce [guide](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).

Si vous avez décidé de contribuer, veuillez d'abord lire les directives[here](https://github.com/One-Language/One/blob/main/CONTRIBUTING.md).
<br>Vous pouvez également aider au développement de `One` en faisant des dons sur [:heart: Patreon](https://www.patreon.com/onelanguage).

Merci à tous les <a href ="https://github.com/One-Language/One/graphs/contributors">contributeurs</a>!!

Si vous souhaitez contribuer au développement de ce projet, vous pouvez nous envoyer un mail à : <maxbasecode@gmail.com>

<br>Créé par Max Base @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="licence">➤ Licence</h2>

`One` est publié sous la licence publique générale GNU v3.0. Veuillez vous référer aux termes du fichier <a href="https://github.com/One-Language/One/blob/master/LICENSE">LICENCE</a> inclus dans le repository.

<!--[![Gitter](https://badges.gitter.im/ET_lang/community.svg)](https://gitter.im/ET_lang/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)-->
<!--[Official Community for a chat and discuss.](https://spectrum.chat/et?tab=chat)-->

[discordbadge]: https://img.shields.io/discord/834373930692116531?label=Discord&logo=discord&logoColor=white
[patreonbadge]: https://img.shields.io/endpoint.svg?url=https%3A%2F%2Fshieldsio-patreon.vercel.app%2Fapi%3Fusername%3Donelanguage%26type%3Dpledges
[sponsorbadge]: https://camo.githubusercontent.com/da8bc40db5ed31e4b12660245535b5db67aa03ce/68747470733a2f2f696d672e736869656c64732e696f2f7374617469632f76313f6c6162656c3d53706f6e736f72266d6573736167653d254532253944254134266c6f676f3d476974487562
[twitterbadge]: https://twitter.com/onelangteam
[instagrambadge]: https://img.shields.io/badge/Instagram-Up-brightgreen
[licensebadge]: https://img.shields.io/github/license/One-Language/One
[facebookbadge]: https://img.shields.io/badge/Facebook-Up-brightgreen
[discordurl]: https://discord.gg/sFCE2HcMCa
[patreonurl]: https://patreon.com/onelanguage
[twitterurl]: https://img.shields.io/twitter/follow/onelangteam.svg?style=flatl&label=Follow&logo=twitter&logoColor=white&color=1da1f2
[instagramurl]: https://www.instagram.com/one.lang
[licenseurl]: https://github.com/One-Language/One/blob/master/LICENSE
[facebookurl]: https://www.facebook.com/onelangteam
