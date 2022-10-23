.PHONY: check
check:
	pre-commit run --all-files

.PHONY: update
update:
	pre-commit autoupdate
