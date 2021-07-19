# MISSION STATEMENT

## “One offers a unique design experience for programmers around the world, by providing creative, ingenious, and innovative solutions, it’s time for One programming language for all!”

# VISION STATEMENT

## “Compile and Unite with One Language”

# ONE

The best cost-efficient, fast and reliable language did not exist until now, with One language it is undeniable that you will reduce the cost of building software creatively and innovatively!
How? With One, which compiles plenty of languages in just one, the amount of work and the process of hiring multiple programmers specialized in different languages will be reduced drastically, your only need will be a One Language expert to carry on your work!
A game-changer and a revolution in the world of programming has emerged, with this multi-purpose language, the amount of time, money, manpower, and maintenance is set to a limit under your budget, guaranteed!


### PURPOSE

The One Language aims to introduce the ultimate solution to your time and cost barriers to achieve your goals faster efficiently and creatively.

Coding can be challenging when faced with issues that are often called “unsolvable” and it became common practice to overlook these issues and carry on working as if they were part of the coding process, which most programmers fall for and never try to fix.
With ONE, the developing team has solved the unsolvable and carried on without leaving any issues behind. With new tools that can enable coding to become easier and more reliable than before.


### DESIGN AND DEVELOPMENT GOALS

The One Language development team is on its way to achieving the following:
- Clean and easy syntax
- Multi-purpose language
- Useful functionality and runtime-library
- Bootstrapping and self-host compiler
- Ability to create executable files
- Cross-platform compatibility
- Support for different architectures and OSs
- An internal web-development framework
- Easier debugging: Programmers mostly spend their time on reading and debugging their code, which is a time wasted at the expense of writing the actual codes  ([you can see a discussion about this subject here](https://www.quora.com/It-is-true-that-developers-spend-most-of-their-time-reading-code-than-writing-code))
- Easier maintenance
- Static-type language (but it can auto-detect the type of your variables and values)
- Faster performance
- A compiler that also has some features of interpreters
- Modular system (a clean and nice structure of modules)
- A friendly package manager (easily installing third-party libraries, with just one single command)

### FEATURES OF THE LANGUAGE

**The project is still in the Alpha phase. And to be updated **

### DESIGN DECISIONS

- Modules referable to each other and dependable on other modules
- Ability to split a program into different parts / into separate files

### RUN-TIME SYSTEM CHOICE

At runtime, ONE doesn’t NULL, and the language supports null safety. So, you can make sure everything works at runtime, as you have already passed so many errors in compiling step.
Currently, Glibc is being used, and programmers are allowed to be used and linked since all libraries need Glibc. (pthread, libcurl, libopenssl, mysql/mariadb database, etc.) Yet, we are also planning to be able to generate executable files without the need for a C library (Glibc).

We generated C-intermediate code and used a C compiler to generate an executable file at the background of the compiler, but for the time being, at its early steps, we use LLVM for the back-end of the compiler. So, we can generate object-file and executable files for every OS and architecture. In the future, we will have our runtime library. Furthermore, programs compiled by One are mostly optimized with great performance.

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
