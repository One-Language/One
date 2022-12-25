<div dir="rtl">
<div align="center">

<p>
    <a href="https://onelang.org/">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="The One Programming Language">
    </a>
</p>

# زبان برنامه نویسی وان💚 💙 🧡 🤍 💖 🖤

[Onelang.ir](https://onelang.ir) |
[کمک خواست](https://github.com/One-Language/One/issues/new)

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
[한국어](README_KR.md)
&nbsp;
[русский](README_RU.md)
&nbsp;
[Türkçe](README_TR.md)
&nbsp;
[Українська](README_UK.md)

</div>

به <a href="https://onelang.org">وان</a> خوش آمدید!</br>

این یک <b>زبان برنامه نویسی سیستمی</b>، خود میزبان و منبع باز هست که طراحی نرم افزار های توسعه پذیر و سریع رو راحت می کند.

این زبان توسط <a href="https://github.com/BaseMax">مکس</a> و <a href="https://github.com/jbampton">جوهن</a> و دیگرتوسعه دهندگان پروژه طراحی می شود.

### کامپایلر برای زبان وان در ماه هایی پیش رو آماده می شود.

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- TABLE OF CONTENTS -->
<h2 id="table-of-contents">فهرست</h2>
<details open="open">
  <ol>
    <li><a href="#features-of-one">ویژگی های <b>زبان وان</b></a></li>
    <li><a href="#roadmap">نقشه و مسیر پروژه</a></li>
    <li><a href="#code-examples">نمونه کد ها</a></li>
    <li><a href="#getting-started">طریقه شروع</a></li>
    <li><a href="#get-involved">مشارکت کردن</a></li>
    <li><a href="#license">مجوز و لایسنس</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ ویژگی های زبان وان</h2>

- سادگی
- کامپایلری
- امکان ایجاد فایل خروجی قابل اجرا برای معماری های مختلف (x86_64, i386)
- زبان برنامه نویسی سیستمی
- سطح متوسط و نحو نزدیک به انسان
- شبکه و طراحی وبسرویس
- سازگار برای طراحی وب (در آینده ای نزدیک)
  - بصورت خودکار کد های زبان های دیگر را برای شما تولید می کند و برای طراحی وب سایت شما نیاز به یادگیری زبان دیگری ندارید و تنها زبان وان است که استفاده می کنید.
  - استفاده از متغییر در استایل CSS, بنابراین حتی می توانید مشخصات ظاهری و رنگ ها را از دیتابیس نیز دریافت کنید.
  - امکان خودکار کوتاه کردن نتیجه های وب سایت (minify)
- عملکرد و سرعت بالا
- پشتیبانی از دستورات خطی اسمبلی در لابه لای برنامه (در آینده)
- عدم نیاز به ابزارها و کتابخانه های مخصوص بر روی سیستم کاربر در حالت معمول (در آینده)
- به کتابخانه زمان اجرای جانبی دیگری نیاز ندارد (در آینده)
- به کامپایلر خارجی دیگری برای کامپایل احتیاج ندارد (در آینده)

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ نقشه و مسیر پروژه</h2>

نحو و گرامر زبان `وان` نیز در [اینجا](../grammar.BNF) در دسترس است.

</div>

- [x] Lexer/Parser (Mostly)
- [x] AST Tree
- [x] VM
- [ ] Code Generator (get inspired from LLVM-C)
- [ ] Develop a runtime library and add features
- [ ] Design web framework for the language
- [ ] Rewrite compiler in the `One` language

<div dir="rtl">

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="code-examples">➤ نمونه کد ها</h2>
<!--Will have to explain how variable assignment, control flow, function declaration and call etc work in the language-->

</div>

```c
main {
   ret 0
}
```

<div dir="rtl">

**تبدیل به زبان سی C:**

</div>

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

<div dir="rtl">

**تبدیل به زبان سی C:**

</div>

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

<div dir="rtl">

**تبدیل به زبان سی C:**

</div>

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

<div dir="rtl">

**چک نویس دیگر:**

</div>

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

<div dir="rtl">

**نمونه دیگر:**

</div>

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

<div dir="rtl">

### رابط طراحی کنسولی قبلی

</div>

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

<div dir="rtl">

### توسعه نرم افزار گرافیکی و سایت

این معماری برای وبسایت ها و نرم افزار های محلی در حال طراحی است. در آینده، برای اپ های موبایل هم در دسترس خواهد بود. معماری موبایل هنوز تکمیل نشده و نیازمند فکر و توجه بیشتر است.<br><br>مثال برای نشان دادن کارکرد زبان:

</div>

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

<div dir="rtl">

**تبدیل خودکار به CSS/HTML/JS:**

</div>

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

<div dir="rtl">

<h2 id="getting-started">➤ شروع کنید</h2>

</div>

<div dir="rtl">

می توانید برای یادگیری بیشتر نحو این زبان به [این صفحه](https://github.com/ET-Lang/ET/wiki) راهنما مراجعه کنید.

<!--Installation Steps-->

<!--Prerequisites-->

#### پلتفرم و محیط های پشتیبانی شده

</div>

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

<div dir="rtl">

<!--Get Involved-->
<h2 id="get-involved">➤ مشارکت کردن</h2>

</div>

<div dir="rtl">
ما از انواع مشارکت ها، از جمله گزارش اشکال، درخواست ویژگی، بهبود اسناد و غیره استقبال می کنیم.

برای پرسیدن سوال یا باز کردن بحث، یک موضوع بسازید یا به <a href ="https://discord.gg/sFCE2HcMCa"><b>وان</b> سرور دیسکورد</a> بپیوندید.

اگر شما با نحوه ساختن درخواست pull در گیت هاب آشنا نیستید لطفا این [راهنما](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests) را بخوانید.

اگر تصمیم به مشارکت گرفتید، لطفا ابتدا رهنمودها را از [اینجا](../CONTRIBUTING.md) بخوانید.

شما همچنین میتوانید با کمک های مالی به توسعه `وان` کمک کنید [:heart: Patreon](https://www.patreon.com/onelanguage).

تشکر از تمامی <a href ="https://github.com/One-Language/One/graphs/contributors">مشارکت کننده ها</a>!!

اگر شما تمایل به مشارکت در توسعه این پروژه دارید، میتوانید به ما ایمیل بزنید: <maxbasecode@gmail.com>

<br> ساخته شده توسط Max Base @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

</div>

<div dir="rtl">

<h2 id="license">➤ مجوز و لایسنس</h2>

</div>

<div dir="rtl">

`وان` تحت لایسنس GNU General Public License v3.0 انتشار یافته. لطفا به شرایط در فایل <a href="https://github.com/One-Language/One/blob/master/LICENSE">لایسنس</a> موجود در مخزن مراجعه کنید.

</div>

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
