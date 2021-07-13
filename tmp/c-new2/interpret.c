/**
 The One Programming Language

 File: interpret.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "error.h"
#include "lexer.h"
#include "token.h"
#include "ast.h"
#include "parser.h"
#include "file.h"

#include "interpret.h"

extern Parser parser;

int interpret_source(char* source, const char* path)
{
	debug("interpret_source");
	debug("interpret_source: %s", source);

	// https://www.freebsd.org/cgi/man.cgi?query=sysexits&apropos=0&sektion=0&manpath=FreeBSD+4.3-RELEASE&format=html
	int ret = EXIT_SUCCESS;

	lexer_init(source);

	parser_init();
	parser.path = path;
	parser_scan();
	lexer_free();

	parser_start();
	parser_free();

	return ret;
}

int interpret_file(const char* path)
{
	debug("interpret_file");
	debug("interpret_file: %s", path);

	char* source = file_reads(path);
	int ret = interpret_source(source, path);
	free(source);
	return ret;
}
