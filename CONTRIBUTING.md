# Pre-commit

A framework for managing and maintaining multi-language pre-commit hooks.
Pre-commit can be [installed](https://pre-commit.com/#installation) with
`pip`, `curl`, `brew` or `conda`.

You need to first install pre-commit and then install the pre-commit hooks
with `pre-commit install`. Now pre-commit will run automatically on git
commit!

If you have python at your system, so you can easily install pre-commit via `pip install pre-commit`.

It's usually a good idea to run the hooks against all the files when
adding new hooks (usually pre-commit will only run on the changed files
during git hooks). Use `pre-commit run --all-files` to check all files.

To run a single hook use `pre-commit run --all-files <hook_id>`

To update use `pre-commit autoupdate`

- [Quick start](https://pre-commit.com/#quick-start)
- [Usage](https://pre-commit.com/#usage)
- [pre-commit-autoupdate](https://pre-commit.com/#pre-commit-autoupdate)
