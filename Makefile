.PHONY: check
check:
	pre-commit run --all-files

.PHONY: checkinstall
checkinstall:
	pre-commit install

.PHONY: checkupdate
checkupdate:
	pre-commit autoupdate
