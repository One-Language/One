<div align="center">

<p>
    <a href="https://onelang.org/">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="The One Programming Language">
    </a>
</p>

# Мова програмування The One 💚 💙 🧡 🤍 💖 🖤

[Onelang.org](https://onelang.org) |
[Потрібна допомога](https://github.com/One-Language/One/issues/new)

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

Ласкаво просимо до <a href="https://onelang.org">One</a>!</br>
Це відкрита, самодостатня, самоналаштовувана <b>системна мова програмування</b> яка дає можливість легко створити надійне і ефективне програмне забезпечення.
Вона розробляється <a href="https://github.com/BaseMax">Max</a>, <a href="https://github.com/jbampton">John</a> і іншими людьми, що роблять внесок через відкритий доступ.

### Компілятор для One Language буде представлений через декілька місяців

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- ЗМІСТ -->
<h2 id="table-of-contents">Зміст</h2>
<details open="open">
  <ol>
    <li><a href="#features-of-one">Особливості <b>One</b></a></li>
    <li><a href="#roadmap">Дорожня карта</a></li>
    <li><a href="#code-examples">Зразки коду</a></li>
    <li><a href="#getting-started">Почнемо</a></li>
    <li><a href="#get-involved">Долучайтесь</a></li>
    <li><a href="#license">Ліцензія</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ Особливості One</h2>

- Простота
- Компілятор
- Можливість створення вихідного файлу (x86_64, i386)
- Системна мова програмування
- Середній рівень
- Мережеве і API програмування
- Підтримує веб-програмування (в майбутньому)
  - Автоматична генерація відповідного коду і для CSS і HTML. Отже, вам не потрібно буде вивчати інші мови, крім `One`, щоб створити вебсайт
  - Використовує змінні в CSS, щоб ми змогли отримати кольори чи розміри з бази данних
  - Автоматична мінімізація результатів пошуку сторінки
- Продуктивність і висока швидкість
- Підтримує код вбудованого асемблера (в майбутньому)
- В звичайному режимі не потребує спеціальних бібліотек і інструментів на системі користувача (в майбутньому )
- В звичайному режимі не потребує зовнішніх бібліотек часу виконання (в майбутньому )
- Не потребує зовнішніх компіляторів для виконання компіляції (в майбутньому)

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ RoadMap</h2>

Граматика мови `One` доступна [тут](https://github.com/One-Language/One/blob/main/grammar.BNF).

- [x] Lexer/Parser (здебільшого)
- [x] Дерево AST
- [x] VM
- [ ] Генератор коду (на основі LLVM-C)
- [ ] Розробіть бібліотеку часу виконання і додайте характеристики
- [ ] Створіть веб-фреймворк для мови
- [ ] Перепишіть компілятор мовою `One`

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="code-examples">➤ Зразки коду</h2>
<!--Will have to explain how variable assignment, control flow, function declaration and call etc work in the language-->

```c
main {
   ret 0
}
```

**Конвертувати в C:**

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

**Конвертувати в C:**

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

**Конвертувати в C:**

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

**Інший варіант:**

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

**Інший варіант:**

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

### Розробка старого CLI

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

### Розробка старого GUI : (Web, Software)

Ця архітектура розробляється лише для веб-сайтів і власного програмного забезпечення. В майбутньому вона також буде доступною для мобільних додатків (власних).<br>
Мобільні структури ще не завершені і потребують більше уваги і осмислення.<br><br>Приклад для демонстрації роботи мови:

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

**Конвертувати в базу CSS/HTML/JS:**

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

<h2 id="getting-started">➤ Почнемо</h2>

Перейдіть за [цим посиланням](https://github.com/ET-Lang/ET/wiki), щоб почати вивчення мови.

<!--Кроки встановлення-->

<!--Передумови-->

#### Середовища, що підтримуються

- [x] GNU / Linux <!--which Linux?-->
- [x] Windows
- [ ] macOS (Не повністю)
- [ ] BSD

<!--напишіть більше про компілятор-->
<!--Кроки-->
<!--Building One from Source-->
<!--Hello World в One-->
<!--Поради, щоб зрозуміти One краще-->
<!--Розширення найменувань файлів: `.one`-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!--Get Involved-->
<h2 id="get-involved">➤ Долучайтесь</h2>

Ми вітаємо будь-які види внесків, включаючи повідомлення про баги, запити щодо особливостей, покращення документації і т.д.
Щоб задати питання чи відкрити дискусію, створіть тему обговорення або ж долучіться до <a href ="https://discord.gg/sFCE2HcMCa"><b>One</b> Discord сервер</a>.

Якщо ви не знайомі з тим, як створити Pull-запит у GitHub, прочитайте, будь-ласка, це - [довідник](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).

Якщо ви вирішили зробити свій внесок, прочитайте, будь-ласка, спочатку настанови [тут](https://github.com/One-Language/One/blob/main/CONTRIBUTING.md).
<br>Також ви можете допомогти в розробці `One`, надсилаючи пожертвування на [:heart: Patreon](https://www.patreon.com/onelanguage).

Дякуємо усім <a href ="https://github.com/One-Language/One/graphs/contributors">людям, що роблять свої внески</a>!!

Якщо ви бажаєте зробити власний внесок у розвиток цього проекту, ви можете написати нам на: <maxbasecode@gmail.com>

<br>Created By Max Base @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="license">➤ Ліцензія</h2>

`One` випущено згідно з Загальною публічною ліцензією GNU v3.0. Будь-ласка, перейдіть до умов в <a href="https://github.com/One-Language/One/blob/master/LICENSE">ЛІЦЕНЗІЯ</a> файлі, вкладеному в репозиторій.

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
