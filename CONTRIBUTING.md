<h1 align="center"><strong>Contributing to the ONE Programming Language</strong></h1>

> Welcome new contributors! First of all thank you for contributing! :+1: :tada:

## How to Contribute

### **First, Discuss**

`The ONE Programming Language` is a very welcoming community. We appreciate your
ideas and your help. You need to communicate in
[our discord server](https://discord.com/invite/sFCE2HcMCa) or pick an issue and
share your perception of the solution you have. Don't forget to fork this
repository and to work on your contribution.

### **Then, make a PR**

Now that you finished the work, don't forget again to run pre-commit. Create the
pull request and use the description to provide context and motivation, as you
did in the issue. Otherwise, you can mention your PR in the issue that you tried
to solve. Once a pull request is created, we will verify the code and accept
your PR.

## Contribution Tools

### Pre-commit

A framework for managing and maintaining multi-language `pre-commit` hooks.
Pre-commit can be [installed](https://pre-commit.com/#installation) with `pip`,
`curl`, `brew` or `conda`.

You need to first install `pre-commit` and then install the `pre-commit` hooks
with `pre-commit install`. Now `pre-commit` will run automatically on git
commit!

If you have [Python](https://www.python.org/) at your system, so you can easily
install pre-commit via `pip install pre-commit`.

It's usually a good idea to run the hooks against all the files when adding new
hooks (usually `pre-commit` will only run on the changed files during git
hooks). Use `pre-commit run --all-files` to check all files.

To run a single hook use `pre-commit run --all-files <hook_id>`

To update use `pre-commit autoupdate`

- [Quick start](https://pre-commit.com/#quick-start)
- [Usage](https://pre-commit.com/#usage)
- [pre-commit-autoupdate](https://pre-commit.com/#pre-commit-autoupdate)

### Python

`Python` is an interpreted high-level general-purpose programming language.
`Python`'s design philosophy emphasizes code readability with its notable use of
significant indentation. `pip` is a package-management system written in
`Python` used to install and manage software packages. It connects to an online
repository of public packages, called the `Python Package Index`.

As I mentioned before you can use `pip` to install `pre-commit` on your system.

### yamllint

A linter for `YAML` files.

`yamllint` does not only check for syntax validity, but for weirdnesses like key
repetition and cosmetic problems such as lines length, trailing spaces,
indentation, etc. You can install `yamllint` using `pip` by the command:

```
pip install --user yamllint
```

- [yamllint on GitHub](https://github.com/adrienverge/yamllint)
- [yamllint documentation](https://yamllint.readthedocs.io/en/stable/)

### markdownlint

A `Node.js` style checker and lint tool for
`[Markdown](https://en.wikipedia.org/wiki/Markdown)/[CommonMark](https://commonmark.org/)`
files.

The `Markdown` markup language is designed to be easy to read, write, and
understand. It succeeds - and its flexibility is both a benefit and a drawback.
Many styles are possible, so formatting can be inconsistent. Some constructs
don't work well in all parsers and should be avoided. The CommonMark
specification standardizes parsers - but not authors.

`markdownlint` is a static analysis tool for `Node.js` with a library of rules
to enforce standards and consistency for `Markdown` files. It was inspired by -
and heavily influenced by - Mark Harrison's `markdownlint` for `Ruby`. The
initial rules, rule documentation, and test cases came directly from that
project.

To install `markdownlint` run:

```
npm install markdownlint --save-dev
```

To run `markdownlint` run from within the `One` directory:

```
markdownlint -c .github/linters/.markdown-lint.yml
```

- [markdownlint on GitHub](https://github.com/DavidAnson/markdownlint)

### Clang Format

`clang-format` is a tool to automatically format `C/C++/Objective-C` code, so
that developers don't need to worry about style issues during code reviews. It
is highly recommended to format your changed C++ code before opening pull
requests, which will save you and the reviewers' time.

- [Clang 13 documentation CLANGFORMAT](https://clang.llvm.org/docs/ClangFormat.html)

### Git hooks

Like many other `Version Control Systems`, `Git` has a way to fire off custom
scripts when certain important actions occur. There are two groups of these
hooks: client-side and server-side. Client-side hooks are triggered by
operations such as committing and merging, while server-side hooks run on
network operations such as receiving pushed commits. You can use these hooks for
all sorts of reasons.

The hooks are all stored in the hooks subdirectory of the `Git` directory. In
most projects, that’s `.git/hooks`. When you initialize a new repository with
`git init`, `Git` populates the hooks directory with a bunch of example scripts,
many of which are useful by themselves; but they also document the input values
of each script. All the examples are written as `shell scripts`, with some
`Perl` thrown in, but any properly named executable scripts will work fine – you
can write them in `Ruby` or `Python` or whatever language you are familiar with.
If you want to use the bundled hook scripts, you’ll have to rename them; their
file names all end with .sample.

To enable a hook script, put a file in the hooks subdirectory of your `.git`
directory that is named appropriately (without any extension) and is executable.
From that point forward, it should be called.

- [Git hooks documentation](https://git-scm.com/book/en/v2/Customizing-Git-Git-Hooks)

### Docker image

`One Docker image` is now on
[`DockerHub`](https://hub.docker.com/r/onelangorg/one)!

The main goal of this image is to serve as a development environment where to
run build code and run tests, before the release of `ONE`.

The
[`README_DOCKER.md`](https://github.com/One-Language/One/blob/master/README_DOCKER.md),
which is the readme file for the `One repository on DockerHub`, will show you
how to use this image for tests, or even as a workspace with `VSCode`.

You can pull the image by running:

```
docker pull onelangorg/one
```

Or build it on your machine, from within the `One` directory, using
`Dockerfile`:

```
docker build -f "Dockerfile" -t one:latest "."
```

Or `docker-compose.yml`:

```
docker-compose -f "docker-compose.yml" up -d --build
```

This image was built using
[`GitHub actions`](https://github.com/One-Language/One/blob/master/.github/workflows/docker-image.yml).
