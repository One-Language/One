<div align="center">

<p>
    <a href="https://onelang.org/">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="The One Programming Language">
    </a>
</p>

# Язык программирования One 💚 💙 🧡 🤍 💖 🖤

[Onelang.org](https://onelang.org) |
[Нужна помощь](https://github.com/One-Language/One/issues/new)

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
[한국어](README_KR.md)
&nbsp;
[русский](README_RU.md)
&nbsp;
[Türkçe](README_TR.md)
&nbsp;
[Українська](README_UK.md)

</div>

Добро пожаловать в <a href="https://onelang.org">One</a>!</br>
Это самодостаточный, самонастраиваемый <b>язык системного программирования</b> с открытым исходным кодом, который предоставляет возможность легко создать надёжное и эффективное программное обеспечение.
Он разрабатывается <a href="https://github.com/BaseMax">Max</a>, <a href="https://github.com/jbampton">John</a> и другими людьми, которые вносят свой вклад.

### Компилятор для One Language будет представлен через несколько месяцев

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- СОДЕРЖАНИЕ -->
<h2 id="table-of-contents">Содержание</h2>
<details open="open">
  <ol>
    <li><a href="#features-of-one">Особенности <b>One</b></a></li>
    <li><a href="#roadmap">Дорожная карта</a></li>
    <li><a href="#code-examples">Примеры кода</a></li>
    <li><a href="#getting-started">Начало работы</a></li>
    <li><a href="#get-involved">Присоединяйтесь</a></li>
    <li><a href="#license">Лицензия</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ Особенности One</h2>

- Простота
- Компилятор
- Возможность создания выходного файла (x86_64, i386)
- Язык системного программирования
- Средний уровень
- Сетевое и API программирование
- Поддерживает веб-программирования (в будущем)
  - Автоматическая генерация соответствующего кода как для CSS, так и для HTML. Таким образом, вам не придётся изучать другие языки кроме `One`, чтобы создать веб-сайт
  - Использует CSS-переменные, благодаря чему у нас есть возможность получить цвета или размеры из базы данных
  - Автоматическая минимизация полученной страницы
- Производительность и высокая скорость
- Поддерживает код ассемблерной вставки (в будущем)
- В нормальном режиме не нуждается в специальных библиотеках и инструментах в системе пользователя (в будущем)
- В нормальном режиме не нуждается во внешних библиотеках среды выполнения (в будущем)
- Не нуждается во внешних компиляторах для компиляции (в будущем)

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ RoadMap</h2>

Грамматика языка `One` доступна [здесь](../grammar.BNF).

- [x] Lexer/Parser (по большей части)
- [x] Дерево AST
- [x] VM
- [ ] Генератор кода (на основе LLVM-C)
- [ ] Создание библиотеки среды выполнения и добавление возможностей
- [ ] Создание веб-фреймворка для языка
- [ ] Переписывание компилятора на язык `One`

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="code-examples">➤ Примеры кода</h2>
<!--Will have to explain how variable assignment, control flow, function declaration and call etc work in the language-->

```c
main {
   ret 0
}
```

**Этот же код на языке C:**

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

**Этот же код на языке C:**

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

**Этот же код на языке C:**

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

---

**Ещё пример:**

```c
import web
home {
    _ "Hi, Welcome"
}
error {
    headers.add('HTTP/1.0 404 Not Found')
    headers.add('content-type: text/html;charset=utf-8')
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

**И ещё пример:**

```c
error {
    headers.add('HTTP/1.0 404 Not Found')
    headers.add('content-type: text/html;charset=utf-8')
    _ `<!doctype html><html><head><title>Error 404</title><meta charset="utf-8"></head><body><h1>404></h1></body></html>`
}

vs

error {
    headers.add('HTTP/1.0 404 Not Found')
    headers.add('content-type: text/html;charset=utf-8')
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

### Разработка старого CLI

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

---

### Разработка старого GUI : (Web, Software)

Эта архитектура разрабатывается только для веб-сайтов и нативного программного обеспечения. В будущем она также будет доступна для мобильных приложений (нативных).<br>
Мобильные структуры ещё не завершены и нуждаются в большем внимании и осмыслении.<br><br>Пример для демонстрации работы языка:

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

**Этот же код в CSS/HTML/JS:**

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

<h2 id="getting-started">➤ Начало работы</h2>

Перейдите по [этой ссылке](https://github.com/ET-Lang/ET/wiki), чтобы начать изучение языка.

<!--Шаги установки-->

<!--Предварительные условия-->

#### Поддерживаемые среды

- [x] GNU / Linux <!--which Linux?-->
- [x] Windows
- [ ] macOS (не полностью)
- [ ] BSD

<!--Напишите больше о компиляторе-->
<!--Шаги-->
<!--Установка One из источника-->
<!--Hello World в One-->
<!--Советы для лучшего понимания One-->
<!--Расширения названий файлов: `.one`-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!--Get Involved-->
<h2 id="get-involved">➤ Присоединяйтесь</h2>

Мы приветствуем все виды сотрудничества, включая сообщения о багах, запросы о нововведениях, улучшение документации и т.д.
Чтобы задать вопрос или начать обсуждение, создайте Issue или присоединитесь к <a href ="https://discord.gg/sFCE2HcMCa">Discord серверy <b>One</b></a>.

Если вы не знаете, как создать Pull-request в GitHub, прочитайте, пожалуйста, это [руководство](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).

Если вы решили внести свой вклад, прочитайте, пожалуйста, сначала руководство [здесь](../CONTRIBUTING.md).
<br>Также у вас есть возможность помочь в разработке `One`, делая пожертвования на [:heart: Patreon](https://www.patreon.com/onelanguage).

Спасибо всем <a href ="https://github.com/One-Language/One/graphs/contributors">людям, помогающим проекту</a>!!

Если вы хотите посодействовать в разработке этого проекта, вы можете написать нам на: <maxbasecode@gmail.com>

<br>Created By Max Base @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="license">➤ Лицензия</h2>

`One` выпущен в соответствии с GNU General Public License v3.0. Перейдите, пожалуйста, к условиям в файле <a href="https://github.com/One-Language/One/blob/master/LICENSE">LICENSE</a>, включенном в репозиторий.

<!--[![Gitter](https://badges.gitter.im/ET_lang/community.svg)](https://gitter.im/ET_lang/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)-->
<!--[Official Community for a chat and discuss.](https://spectrum.chat/et?tab=chat)-->

[discordbadge]: https://img.shields.io/discord/834373930692116531?label=Discord&logo=discord&logoColor=white
[patreonbadge]: https://img.shields.io/endpoint.svg?url=https%3A%2F%2Fshieldsio-patreon.vercel.app%2Fapi%3Fusername%3Donelanguage%26type%3Dpledges
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
