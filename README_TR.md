<div align="center">

<p>
    <a href="https://onelang.org/" alt="The One Programming Language">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="The One Programming Language">
    </a>
</p>

# One Programlama Dili 💚 💙 🧡 🤍 💖 🖤

[Onelang.org](https://onelang.org) |
[Yardımınıza ihtiyacımız var](https://github.com/One-Language/One/issues/new)

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
[Türkçe](README_TR.md)

</div>

<a href="https://onelang.org">One</a>'a hoşgeldiniz!</br>
One açık kaynak kodlu, kendini barındıran ve fonlayan ve bu özellikleri sayesinde güvenilebilir ve verimli yazılımlar yaratmayı kolaylaştıran bir <b>sistem programlama dilidir.</b>
<a href="https://github.com/BaseMax">Max</a>, <a href="https://github.com/jbampton">John</a> ve diğer katılımcılar tarafından geliştirilmektedir.

### One dilinin Compiler'ı birkaç ay içerisinde yayınlanacaktır

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- TABLE OF CONTENTS -->
<h2 id="table-of-contents">İçindekiler</h2>
<details open="open">
  <ol>
    <li><a href="#features-of-one"><b>One</b></a> dilinin özellikleri</li>
    <li><a href="#roadmap">Yol Haritası</a></li>
    <li><a href="#code-examples">Kod Örnekleri</a></li>
    <li><a href="#getting-started">İlk kullanım kılavuzu</a></li>
    <li><a href="#get-involved">Dahil olun</a></li>
    <li><a href="#license">Lisans</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ One Dilinin Özellikleri</h2>

- Basit.
- Compiler.
- Çıktı dosyası oluşturabilir. (x86_64, i386)
- Sistem Programlama Dilidir.
- Orta Düzey.
- Network ve API programlama yapılabilir.
- Web programlama desteği sunar. (gelecek)
  - Hem CSS hem de HTML'e karşılık gelen kodlar otomatik olarak üretilir. Yani, bir websitesi geliştirmek için `One` dışında herhangi bir dil öğrenmenize gerek yok.
  - CSS'de variables kullanır, böylece veritabanından renkleri ve boyutları çekebilir.
  - Sayfa sonuçlarını otomatik olarak küçültür.
- Yüksek hızlı performans vaad eder.
- İnline Assembly code destekler. (gelecek)
- Normal modda, kullanıcının sisteminde belirli kütüphane ve araçlar olmasına ihtiyaç duymaz. (gelecek)
- Normal modda, external runtime kütüphanelerine ihtiyaç duymaz. (gelecek)
- Compile etmek için harici compiler'lara ihtiyaç duymaz. (gelecek)

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ Yol Haritası</h2>

`One` dilinin kurallarını [burada](grammar.BNF) bulabilirsiniz.

- [x] Lexer/Parser (Mostly)
- [x] AST Tree
- [x] VM
- [ ] Code Generator (LLVM-C'den esinlenildi.)
- [ ] Bir runtime kütüphanesi geliştmek ve yeni özellikler eklemek
- [ ] Dil için bir web framework geliştirmek
- [ ] Compiler'ı `One` dili içerisinde yeniden yazmak

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="code-examples">➤ Kod Örnekleri</h2>
<!--Will have to explain how variable assignment, control flow, function declaration and call etc work in the language-->

```c
main {
   ret 0
}
```

**C'ye çevirelim:**

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

**C'ye çevirelim:**

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

**C'ye çevirelim:**

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

**Başka bir taslak:**

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

**Başka bir taslak:**

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

### Eski CLI Geliştirmesi

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

### Eski GUI Geliştirmesi: (Web, Yazılım)

Bu mimari sadece websiteler ve native yazılımlar için tasarlanmıştır. Gelecekte, mobil uygulamalar için de kullanılabilir olacaktır.(native).<br>
Mobil yapılar henüz tamamlanmadı ve daha fazla düşünceye ve ilgilenilmeye ihtiyaçları var.<br><br>Dilin çalışma şeklini göstermek için bir örnek:

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

**CSS/HTML/JS temelli kodlara çevirelim:**

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

<h2 id="getting-started">➤ İlk Kullanım Kılavuzu</h2>

Dili öğrenmeye başlamak için [bu linke](https://github.com/ET-Lang/ET/wiki) göz atabilirsiniz.

<!--Installation Steps-->

<!--Prerequisites-->

#### Desteklenen Ortamlar

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
<h2 id="get-involved">➤ Bize katılın</h2>

Bug raporlamaları, özellik istekleri, dokümentasyon geliştirmeleri vb. dahil olmak üzere her türlü katkıyı nezaketle karşılıyoruz.
Soru sormak ya da bir tartışma başlatmak için bir issue oluşturun ya da <a href ="https://discord.gg/sFCE2HcMCa"><b>One</b> Discord Server</a>'ına katılın.

Eğer GitHub'da nasıl pull request oluşturacağınızı bilmiyorsanız şu [rehberi](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests) inceleyebilirsiniz.

Eğer katkıda bulunmak istiyorsanız, lütfen ilk olarak [burada](CONTRIBUTING.md) yer alan esasları okuyunuz.
<br>Ayrıca [:heart: Patreon](https://www.patreon.com/onelanguage) üzerinden bize maddi destek sağlayarak da bu projeye katkıda bulunabilirsiniz..

<a href ="https://github.com/One-Language/One/graphs/contributors">Katkı sağlayan</a> herkese teşekkürler!

Eğer projenin geliştirilmesinde katkıda bulunmak isterseniz, bize mail atabilirsiniz: <maxbasecode@gmail.com>

<br> Max Base tarafından oluşturuldu! @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="license">➤ Lisans</h2>

`One` GNU General Public License v3.0 lisansı altında yayınlanmıştır. Lütfen <a href="https://github.com/One-Language/One/blob/master/LICENSE">LICENSE</a> dosyası içerisinde yer alan detaylara göre hareket ediniz.

<!--[![Gitter](https://badges.gitter.im/ET_lang/community.svg)](https://gitter.im/ET_lang/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)-->
<!--[Official Community for a chat and discuss.](https://spectrum.chat/et?tab=chat)-->

[discordbadge]: https://img.shields.io/discord/834373930692116531?label=Discord&logo=discord&logoColor=white
[patreonbadge]: https://img.shields.io/endpoint.svg?url=https%3A%2F%2Fshieldsio-patreon.vercel.app%2Fapi%3Fusername%3Donelanguage%26type%3Dpledges
[sponsorbadge]: https://camo.githubusercontent.com/da8bc40db5ed31e4b12660245535b5db67aa03ce/68747470733a2f2f696d672e736869656c64732e696f2f7374617469632f76313f6c6162656c3d53706f6e736f72266d6573736167653d254532253944254134266c6f676f3d476974487562
[twitterbadge]: https://twitter.com/onelangteam
[discordurl]: https://discord.gg/sFCE2HcMCa
[patreonurl]: https://patreon.com/onelanguage
[twitterurl]: https://img.shields.io/twitter/follow/onelangteam.svg?style=flatl&label=Follow&logo=twitter&logoColor=white&color=1da1f2
