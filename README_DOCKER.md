<div align="center">

<p>
    <a href="https://onelang.org/" alt="The One Programming Language">
        <img width="150" src="https://avatars.githubusercontent.com/u/40718659?s=200&v=4" alt="The One Programming Language">
    </a>
</p>

# The One Programming Language

[Onelang.org](https://onelang.org) |
[Help wanted](https://github.com/One-Language/One/issues/new)

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

<!-- prettier-ignore-start -->
<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->

</div>

Welcome to <a href="https://onelang.org">One</a>!</br>
It is an open source, self-hosted, bootstrapping <b>system programming language</b> which makes it easy to
build reliable and efficient software.
It is being developed by <a href="https://github.com/BaseMax">Max</a>, <a href="https://github.com/jbampton">John</a> and other open-source contributors.

### Compiler for the One Language will be released in a few months

The main goal of this image is to serve as a development environment where to run build code and run tests, before the release of `ONE`.

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!-- TABLE OF CONTENTS -->
<h2 id="table-of-contents">Table of Contents</h2>
<details open="open">
  <ol>
    <li><a href="#features-of-one">Quick reference</a></li>
    <li><a href="#roadmap">Supported tags and respective <code>Dockerfile</code> links</a></li>
    <li><a href="#code-examples">How to use this image for development</a></li>
    <li><a href="#get-involved">Get Involved</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="features-of-one">➤ Quick reference</h2>

- Docker repository maintained by: [BaseMax](https://hub.docker.com/u/basemax), and [Kotbi](https://hub.docker.com/u/kotbionelang).

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ Supported tags and respective <code>Dockerfile</code> links</h2>

- [latest](https://github.com/One-Language/One/blob/master/Dockerfile): This docker image contains the following packages:\
  autoconf \
  automake \
  cmake \
  freetype-dev \
  g++ \
  gcc \
  libxml2-dev \
  linux-headers \
  make \
  musl-dev \
  ncurses-dev \
  python3 \
  pre-commit \
  git\
  LLVM

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="roadmap">➤ How to use this image for development</h2>

- To run this image:

```
docker run -it  onelangorg/one:latest
```

- To get the container ID and the container NAME:

```
docker ps
```

- To run the code using `*.sh` files:

```
# SRC
docker exec -it <container ID> sh -c 'cd src/parser && chmod +x build.sh && ./build.sh'
docker exec -it <container ID> sh -c 'cd src/lexer && chmod +x build.sh && ./build.sh'
docker exec -it <container ID> sh -c 'cd src/lexer && chmod +x test.sh && ./test.sh'
# TESTS
docker exec -it <container ID> sh -c 'cd src/lexer && chmod +x build.sh && ./build.sh'
```

- To run the code using executable (pre-built with CMake) files:

```
# SRC
docker exec -it <container ID> sh -c 'cd build && ./lexer input.one'
docker exec -it <container ID> sh -c 'cd build && ./parser input.one'
docker exec -it <container ID> sh -c 'cd build && ./ast input.one'
# TESTS
docker exec -it <container ID> sh -c 'cd build && ./lexer_test'
docker exec -it <container ID> sh -c 'cd build && ./parser_test'
docker exec -it <container ID> sh -c 'cd build && ./argument_test'
docker exec -it <container ID> sh -c 'cd build && ./ast_test'
```

- If you use VSCode for development, you can use this container remotely. To do so, you will need [Visual Studio Code Remote Development](https://github.com/Microsoft/vscode-remote-release). After running your container, you can work from within the container:

1. run the container

   <img width="100%" src="https://user-images.githubusercontent.com/37270435/127685518-84d90537-6c1e-4e25-be4c-ffbc4123e35c.png" alt="Run the container">

2. connect to the container

   <img width="100%" src="https://user-images.githubusercontent.com/37270435/127685616-0237494b-8cb6-48e8-9aec-764e25a70577.png" alt="Connect to the container">

3. Now you can work from within the docker container and the previous step will open this new VSCode window

   <img width="100%" src="https://user-images.githubusercontent.com/37270435/127685983-3fcb3c3f-15c0-4f64-9376-40e8fb176518.png" alt="Vscode remote container window">

4. Choose `One` directory

   <img width="100%" src="https://user-images.githubusercontent.com/37270435/127686121-9e04d137-0cbb-45c8-815c-f339a21bc623.png" alt="One directory">

5. finally here you go!

   <img width="100%" src="https://user-images.githubusercontent.com/37270435/127686195-47d8cae2-9703-4da0-849e-dfc604d31598.png" alt="One remote container workspace">

- To remove the container:

```
docker rm <container name>
```

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<!--Get Involved-->
<h2 id="get-involved">➤ Get Involved</h2>

We welcome all kinds of contributions, including bug reports, feature requests, documentation improvements, etc.
To ask a question or open a discussion, create an issue or join the <a href ="https://discord.gg/sFCE2HcMCa"><b>One</b> Discord Server</a>.

If you are not familiar with making a pull request on GitHub, please read this [guide](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests).

If you have decided to contribute, please first read the guidelines [here](CONTRIBUTING.md).
<br>You can also help in the development of `One` by making some donations on [Patreon](https://www.patreon.com/onelanguage).

Thanks to all the <a href ="https://github.com/One-Language/One/graphs/contributors">contributors</a>!!

If you would like to contribute to the development of this project, you can mail us at: <maxbasecode@gmail.com>

<br>Created By Max Base @ 2019

![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<h2 id="license">➤ License</h2>

`One` is released under the GNU General Public License v3.0. Please refer to the terms in the <a href="https://github.com/One-Language/One/blob/master/LICENSE">LICENSE</a> file included in the repository.

[discordbadge]: https://img.shields.io/discord/834373930692116531?label=Discord&logo=discord&logoColor=white
[patreonbadge]: https://img.shields.io/endpoint.svg?url=https%3A%2F%2Fshieldsio-patreon.vercel.app%2Fapi%3Fusername%3Donelanguage%26type%3Dpledges
[sponsorbadge]: https://camo.githubusercontent.com/da8bc40db5ed31e4b12660245535b5db67aa03ce/68747470733a2f2f696d672e736869656c64732e696f2f7374617469632f76313f6c6162656c3d53706f6e736f72266d6573736167653d254532253944254134266c6f676f3d476974487562
[twitterbadge]: https://twitter.com/onelangteam
[instagrambadge]: https://img.shields.io/badge/Instagram-Up-brightgreen
[licensebadge]: https://img.shields.io/github/license/One-Language/One
[discordurl]: https://discord.gg/sFCE2HcMCa
[patreonurl]: https://patreon.com/onelanguage
[twitterurl]: https://img.shields.io/twitter/follow/onelangteam.svg?style=flatl&label=Follow&logo=twitter&logoColor=white&color=1da1f2
[instagramurl]: https://www.instagram.com/one.lang
[licenseurl]: https://github.com/One-Language/One/blob/master/LICENSE
