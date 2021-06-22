<div dir="rtl">

<div align="center">

<p>
    <a href="https://onelang.org/" alt="The One لغة برمجة">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="The One Programming Language">
    </a>
</p>

# The One لغة برمجة 💚 💙 🧡 🤍 💖 🖤

[Onelang.org](https://onelang.org) |
[للمساعدة](https://github.com/One-Language/One/issues/new)

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
[Türkçe](README_TR.md)
&nbsp;
[فارسی](README_FA.md)

</div>

اهلا وسهلا بك في <a href="https://onelang.org">One</a>!</br>
إنها لغة برمجة نظام مفتوحة المصدر ، مستضافة ذاتيًا ، مما يجعل من السهل إنشاء برامج موثوقة وفعالة.
يتم تطويره من قبل <a href="https://github.com/BaseMax">ماكس</a>, <a href="https://github.com/jbampton">جون</a> ومساهمين آخرين من المصادر المفتوحة.

### سيصدر المترجم للغة الواحدة "ONE" في غضون أشهر قليلة

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- جدول المحتويات -->
<h2 id="table-of-contents">جدول المحتويات</h2>
<details open="open">
  <ol>
    <li><a href="#features-of-one">ميزات <b>One</b></a></li>
    <li><a href="#roadmap">خريطة الطريق</a></li>
    <li><a href="#code-examples">أمثلة التعليمات البرمجية</a></li>
    <li><a href="#getting-started">البدء</a></li>
    <li><a href="#get-involved">شارك</a></li>
    <li><a href="#license">الرخصة</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ مميزات لغة البرمجة One</h2>

- البساطة
- مترجم
- القدرة على إنشاء ملف الإخراج (x86_64, i386)
- لغة برمجة النظام
- المستوى المتوسط
- برمجة الشبكات و API
- يدعم برمجة الويب (في المستقبل)
  - الإنشاء التلقائي للرمز المقابل لكل من CSS و HTML. لذلك لن تضطر إلى تعلم أكثر من لغة واحدة لتطوير موقع ويب
  - يستخدم المتغيرات في CSS ، حتى نتمكن من الحصول على الألوان أو الأحجام من قاعدة البيانات
  - تصغير نتائج الصفحة تلقائيًا
- أداء وسرعة عالية
- يدعم رمز التجميع المضمن (في المستقبل)
- لا يتطلب مكتبات وأدوات محددة على نظام المستخدم في الوضع العادي (في المستقبل)
- لا يتطلب مكتبات وقت تشغيل خارجية في الوضع العادي (في المستقبل)
- لا يتطلب من المترجمين الخارجيين القيام بالتجميع (في المستقبل)

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ خارطة الطريق</h2>

قواعد اللغة الواحدة متوفرة . [هنا](grammar.BNF).

- [x] المعجم / المحلل اللغوي (في الغالب)
- [x] شجرة AST
- [x] VM
- [ ] مولد الشفرة (استلهم من LLVM-C)
- [ ] قم بتطوير مكتبة وقت التشغيل وإضافة ميزات
- [ ] تصميم إطار عمل للغة
- [ ] أعد كتابة المترجم بلغة ONE

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="code-examples">➤ أمثلة التعليمات البرمجية</h2>
<!--Will have to explain how variable assignment, control flow, function declaration and call etc work in the language-->

</div>

```c
main {
   ret 0
}
```

<div dir="rtl">

**التحويل الى C:**

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

**التحويل الى C:**

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

**التحويل الى C:**

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

<hr/>

<div dir="rtl">

**مسودة أخرى:**

</div>

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

<div dir="rtl">

**مسودة أخرى:**

</div>

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

<div dir="rtl">

### تطوير CLI القديم

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

<hr/>

<div dir="rtl">

### تطوير واجهة المستخدم الرسومية القديمة: (الويب ، البرامج)

تم تصميم هذه البنية فقط لمواقع الويب والبرامج الأصلية. في المستقبل ، سيكون متاحًا أيضًا لتطبيقات الأجهزة المحمولة (الأصلية). (native).<br/>
الهياكل المتنقلة لم تكتمل بعد وتتطلب المزيد من التفكير والاهتمام. <br/><br/>مثال لإثبات عمل اللغة:

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

**التحويل إلى قاعدة CSS / HTML / JS:**

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

<h2 id="getting-started">➤ البدء</h2>

الرجوع الى [هذا الرابط](https://github.com/ET-Lang/ET/wiki) لبدء تعلم اللغة.

<!--Installation Steps-->

<!--Prerequisites-->

#### البيئات المدعومة

</div>

- [x] GNU / Linux <!--which Linux?-->
- [x] Windows
- [ ] macOS (Not complete)
- [ ] BSD

<div dir="rtl">

<!--Write more about the compiler-->
<!--Steps-->
<!--Building One from Source-->
<!--Hello World in One-->
<!--Tips to understand the language better-->
<!--Filename extensions: `.one`-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!--Get Involved-->
<h2 id="get-involved">➤ شارك</h2>

نرحب بجميع أنواع المساهمات ، بما في ذلك تقارير الأخطاء وطلبات الميزات وتحسينات الوثائق وما إلى ذلك.
لطرح سؤال أو فتح مناقشة أو إنشاء مشكلة أو الانضمام إلى . <a href ="https://discord.gg/sFCE2HcMCa"><b>One</b> Discord Server</a>.

إذا لم تكن على دراية بكيفية تقديم طلب سحب على GitHub ، فيرجى قراءة هذا . [الدليل](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).

إذا كنت قد قررت المساهمة ، يرجى قراءة الإرشادات هنا أولاً. [هنا](CONTRIBUTING.md).
<br/>يمكنك أيضًا المساعدة في تطوير `One` من خلال تقديم بعض التبرعات على [:heart: Patreon](https://www.patreon.com/onelanguage).

شكرا لجميع <a href ="https://github.com/One-Language/One/graphs/contributors">المساهمين</a>!!

إذا كنت ترغب في المساهمة في تطوير هذا المشروع, يمكنك مراسلتنا على: <maxbasecode@gmail.com>

<br/>تم إنشاؤه بواسطة Max Base @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="license">➤ الرخصة</h2>

`One` تم إصدارها بموجب رخصة جنو العمومية العامة v3.0. يرجى الرجوع إلى المصطلحات الموجودة في ملف الترخيص المتضمن في المستودع.

<!--[![Gitter](https://badges.gitter.im/ET_lang/community.svg)](https://gitter.im/ET_lang/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)-->
<!--[Official Community for a chat and discuss.](https://spectrum.chat/et?tab=chat)-->

[discordbadge]: https://img.shields.io/discord/834373930692116531?label=Discord&logo=discord&logoColor=white
[patreonbadge]: https://img.shields.io/endpoint.svg?url=https%3A%2F%2Fshieldsio-patreon.vercel.app%2Fapi%3Fusername%3Donelanguage%26type%3Dpledges
[sponsorbadge]: https://camo.githubusercontent.com/da8bc40db5ed31e4b12660245535b5db67aa03ce/68747470733a2f2f696d672e736869656c64732e696f2f7374617469632f76313f6c6162656c3d53706f6e736f72266d6573736167653d254532253944254134266c6f676f3d476974487562
[twitterbadge]: https://twitter.com/onelangteam
[discordurl]: https://discord.gg/sFCE2HcMCa
[patreonurl]: https://patreon.com/onelanguage
[twitterurl]: https://img.shields.io/twitter/follow/onelangteam.svg?style=flatl&label=Follow&logo=twitter&logoColor=white&color=1da1f2

</div>
