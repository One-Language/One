#!/usr/bin/env bash

gcc ../lexer/lexer.c ../lexer/tokenizer/token.c ../lexer/tokenizer/tokenizer.c *.c ../builtins/*.c ../ast/ast.c -o parser
