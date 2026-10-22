#!/usr/bin/env bash

clear
bash build.sh
./lexer ../../input.one log
cat log
