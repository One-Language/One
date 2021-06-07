# THE MISSION STATEMENT of _The One Language_

## One Language for all

In today’s world, there are so many programming languages, and each of them is used for different purposes. If you need executable programs, scripts, and websites for your project, to be able to do all these operations, you need more than 3 different languages.

_The One Language_ will be a game-changer because it is not focused on any specific area, it’s a multi-purpose language. It will serve all your needs, and become your only need.

### OUR AIM

_The One Language_ project aims at reducing the time needed for writing, developing, or maintaining programs.

During the process of writing codes, every programmer faces some common problems, but they do not think of solving these problems, but they try to get used to them. We, **_The One Language developing team_**, want to put an end to this. Our aim is **to solve all these problems and to present you a smooth developing experience**.

_The One Language_ aims to provide you **a new tool to write programs in an easier and better way**.

Developing **a brand-new solution to the design and creation processes of websites**, without the need of learning different languages is one of our intentions.

In short, the main purpose of One Language is **to provide programmers a single language for all of their needs and also making their lives easier.**

### DESIGN AND DEVELOPMENT GOALS

_The One Language_ development team is planning to reach the aims of the project by achieving these goals:

- Clean and easy syntax
- Multi-purpose language
- Useful functionality and runtime-library
- Bootstrapping and self-host compiler
- Ability to create executable files
- Cross-platform compatibility
- Support for different architectures and OSs
- An internal web-development framework
- Easier debugging: Programmers mostly spend their time on reading and debugging their code and not on writing ([you can see a discussion about this subject here](https://www.quora.com/It-is-true-that-developers-spend-most-of-their-time-reading-code-than-writing-code))
- Easier maintenance
- Static-type language (but it can auto-detect the type of your variables and values)
- Faster performance
- A compiler that also has some features of interpreters
- Modular system (a clean and nice structure of modules)
- A friendly package manager (easily installing third-party libraries, with just one single command)

### FEATURES OF THE LANGUAGE

**The project is still in Alpha. TO BE UPDATED.**

### DESIGN DECISIONS

- Modules referable to each other and dependable on other modules
- Ability to split a program into different parts / into separate files

### RUN-TIME SYSTEM CHOICE

At runtime, _One_ doesn’t have NULL, and the language supports null safety. So you can make sure everything works at runtime, as you have already passed so many errors at compiling step.

Currently, we use Glibc, and programmers are allowed to use and link it, because all the libraries need Glibc. (pthread, libcurl, libopenssl, mysql/mariadb database, etc.) Yet, we are also planning to be able to generate executable files without the need for C library (Glibc). We tried this before, and we were able to do it.
We generated C-intermediate code and used a C compiler to generate an executable file at the background of the compiler, but for the time being, at these first steps of the project, we use LLVM for the back-end of the compiler. So, we can generate object-file and executable files for every OS and architecture. In the future, we will have our own runtime library. Furthermore, programs compiled by _One_ are mostly optimized with great performance.

### LIBRARY

_The One Language_ will have a module/package marketplace to list all the packages compatible with _One_, and users will be able to see the lists of packages such as the most popular, the most downloaded, or recently updated packages.

Everyone will be allowed to create and publish packages. We will have a quality control team to review all packages, and we will flag the great and useful ones. If your package is flagged by our team, you will have our support to manage the bugs and probably the issues.

Support for third-party libraries is also among our future plans.

### INTEROPERABILITY

- Direct C Interface

### SUPPORTED PLATFORMS

- Linux
- Windows
- macOS
- BSD family
