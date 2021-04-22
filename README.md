# The One Programming Language

One is an open source, self-hosted, bootstrapping **system programming language**. It is easy to build, reliable, and efficient performance software.

The compiler will be released in next few months.

# Objectives and Features:

- Easy
- Compiler
- Ability to create output file (x86_64, i386)
- System programming
- Intermediate level
- Web Programming
  - Automatic generate html, css code. so you not need to learn so many language to develop a website
  - Use variables in CSS, so we can easily get colors or size from database or etc.
  - Auto minify page result
- Network, API programming
- Performance and high speed
- Supports inline assembly code
- No require specific libraries and tools on user system in normal mode (in the future)
- No require external runtime libraries in normal mode (in the future)
- No require external compilers for compile steps (in the future)

# Concept

```c
main {
   ret 0
}
```
Convert to C:

```c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
   global_argc = argc;
   global_argv = argv;
   return (int) 0;
}
```

----


```c
i32 main {
   ret 10
}
```

Convert to C:

```c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
   global_argc = argc;
   global_argv = argv;
   return (int) 10;
}
```

----

```c
main {
   string in = "Hello, World!"
   __ in
   return in.length
}
```

Convert to C:

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

-------------

## Old Cli Development

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

## Old GUI Development (Web, Software)

This architecture is only designed for website and software (native). In the 
future, it will also be available for mobile apps (native).

Mobile structures are not yet complete and need more thought and attention.

An example of the language at work:

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

Convert to HTML/CSS/JS base:

```html
<html>
	<head>
		<title>Name - Main</title>
		<meta name="description" content="Descriptions">
		<meta name="keyword" content="keywords">
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
				<li>
				Home
				</li>
				<li>
				About
				</li>
				<li>
				Contact Us
				</li>
			</ul>
		</header>
	</body>
</html>
```

The end result:

<p align="center">
 <img alt="Screen Of Render" src="https://github.com/ET-Lang/ET/raw/master/tests/42-architecture-sample.png" width="80%">
</p>

# Learning

Refer to the [Wiki](https://github.com/ET-Lang/ET/wiki) to start learning this language.

# Introduction

#### Start activity

- Initial start: 2010 about 9 years ago
- Beginning : 2012 about 7 years ago

#### OS

- [x] Gnu / Linux
- [x] Windows
- [ ] MacOS (Not complete)
- [ ] BSD


#### Filename extensions: `.one`

-------

Send your message for sponsorship and to support us. (MaxBaseCode {[@]} Gmail {[DOT]} Com)

Created By Max Base @ 2019

<!--
[![Gitter](https://badges.gitter.im/ET_lang/community.svg)](https://gitter.im/ET_lang/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
-->
<!--
[Official Community for a chat and discuss.](https://spectrum.chat/et?tab=chat)
-->

Discord server: https://discord.gg/sFCE2HcMCa
