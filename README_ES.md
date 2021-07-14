<div align="center">

<p>
    <a href="https://onelang.org/" alt="The One Programming Language">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="The One Programming Language">
    </a>
</p>

# El lenguaje de programacion ONE 💚 💙 🧡 🤍 💖 🖤

[Onelang.org](https://onelang.org) |
[Colaboraciones](https://github.com/One-Language/One/issues/new)

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
[русский](README_RU.md)
&nbsp;
[Türkçe](README_TR.md)
&nbsp;
[Українська](README_UK.md)


</div>

Bienvenidos a <a href="https://onelang.org">One</a>!</br>
Es un <b>lenguaje de programación</b> de código abierto, autohospedado y de arranque que facilita construir software confiable y eficiente.
Está siendo desarrollado por <a href="https://github.com/BaseMax">Max</a>, <a href="https://github.com/jbampton">John</a> Y otros contribuyentes de código abierto.

### El compilador para el lenguaje One estará disponible en los próximos meses

<!--
    WRITE PROJECT MOTIVATION HERE
-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- TABLA DE CONTENIDOS -->
<h2 id="table-of-contents">Tabla de Contenidos</h2>
<details open="open">
  <ol>
    <li><a href="#features-of-one">Características de <b>One</b></a></li>
    <li><a href="#roadmap">Hoja de Ruta</a></li>
    <li><a href="#code-examples">Ejemplos del código</a></li>
    <li><a href="#getting-started">Primeros Pasos</a></li>
    <li><a href="#get-involved">Involucrarse</a></li>
    <li><a href="#license">Licencia</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ Características de One</h2>

- Simplicidad
- Compilador
- Capacidad de crear archivo de salida (x86_64, i386)
- Lenguaje de programación de sistema
- Nivel intermedio
- Programacion Network y API
- Soporta programación Web (próximamente)
  - Generación automática del código correspondiente para CSS y HTML. Así que no tendrás que aprender sino el lenguaje `One` para desarrollar un sitio web
  - Emplea variables en CSS, de manera que podemos obtener los colores o tamaños de la base de datos
  - Auto minifica los resultados de la página
- Desempeño y alta velocidad
- Soporta inline Assembly code (próximamente)
- No requiere librerías y herramientas específicas en el sistema del usuario en modo normal (próximamente)
- No requiere bibliotecas de ejecución externas en modo normal (próximamente)
- No requiere compiladores externos para llevar a cabo la compilación (próximamente)

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ RoadMap</h2>

La gramática del lenguaje `One` está disponible [aquí](grammar.BNF).

- [x] Lexer/Parser (Mayormente)
- [x] Arbol AST
- [x] VM
- [ ] Generador de código (inspirado en LLVM-C)
- [ ] Desarrollar una biblioteca en tiempo de ejecución y agregar funciones
- [ ] Diseñar arquitectura (framework) web para el lenguaje
- [ ] Reescribir el compilador en el lenguaje `One`

<!--Include to a section about steps of installation-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="code-examples">➤ Ejemplos del código</h2>
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

**Otro ejemplo:**

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

**Otro ejemplo:**

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

### Desarrollo anterior de la CLI

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

### Desarrollo anterior de la GUI: (Web, Software)

Esta arquitectura está diseñada solo para sitios web y software nativo. En el futuro, también estará disponible para aplicaciones móviles. (native).<br>
Las estructuras móviles aún no están completas y aún requieren de atención y dedicación.<br><br>El siguiente es un ejemplo de como funciona el lenguaje:

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

**Convertir a base CSS/HTML/JS:**

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

<h2 id="getting-started">➤ Primeros Pasos</h2>

Puedes revisar [este link](https://github.com/ET-Lang/ET/wiki) para comenzar a aprender el lenguaje.

<!--Pasos para la instalación-->

<!--Prerequisitos-->

#### Ambientes soportados

- [x] GNU / Linux <!--which Linux?-->
- [x] Windows
- [ ] macOS (Incompleto)
- [ ] BSD

<!--Escribir más sobre el compilador-->
<!--Pasos-->
<!--Building One from Source-->
<!--Hello World en One-->
<!--Tips para entender mejor el lenguaje-->
<!--Nombre de las extensiones: `.one`-->

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!--Get Involved-->
<h2 id="get-involved">➤ Involucrarse</h2>

Aceptamos cualquier tipo de contribuciones, incluyendo reportes de bugs, solicitud de funciones, mejoras en la documentación, etc.
Para hacer una pregunta o iniciar una conversación, create an issue o únete al <a href ="https://discord.gg/sFCE2HcMCa"><b>One</b> Servidor de Discord</a>.

Si no estás familiarizado con el procedimiento para hacer un pull request en GitHub puedes revisar esta [guía](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).

Si has decidido contribuir, por favor revisa los lineamientos [aquí](CONTRIBUTING.md).
<br>También puedes ayudar al desarrollo de `One` a través de donaciones en [:heart: Patreon](https://www.patreon.com/onelanguage).

Gracias a todos los <a href ="https://github.com/One-Language/One/graphs/contributors">colaboradores</a>!!

Si te gustaría contribuir al desarrollo de este proyecto, puedes esctibirnos a: <maxbasecode@gmail.com>

<br>Created By Max Base @ 2019
![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="license">➤ Licencia</h2>

`One` está publicado bajo la Licencia Pública General GNU v3.0. Por favor revisa los términos en el archivo <a href="https://github.com/One-Language/One/blob/master/LICENSE">LICENCIA</a> incluido en el repositorio.

<!--[![Gitter](https://badges.gitter.im/ET_lang/community.svg)](https://gitter.im/ET_lang/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)-->
<!--[Official Community for a chat and discuss.](https://spectrum.chat/et?tab=chat)-->

[discordbadge]: https://img.shields.io/discord/834373930692116531?label=Discord&logo=discord&logoColor=white
[patreonbadge]: https://img.shields.io/endpoint.svg?url=https%3A%2F%2Fshieldsio-patreon.vercel.app%2Fapi%3Fusername%3Donelanguage%26type%3Dpledges
[sponsorbadge]: https://camo.githubusercontent.com/da8bc40db5ed31e4b12660245535b5db67aa03ce/68747470733a2f2f696d672e736869656c64732e696f2f7374617469632f76313f6c6162656c3d53706f6e736f72266d6573736167653d254532253944254134266c6f676f3d476974487562
[twitterbadge]: https://twitter.com/onelangteam
[discordurl]: https://discord.gg/sFCE2HcMCa
[patreonurl]: https://patreon.com/onelanguage
[twitterurl]: https://img.shields.io/twitter/follow/onelangteam.svg?style=flatl&label=Follow&logo=twitter&logoColor=white&color=1da1f2
