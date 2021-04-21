/*
 * Copyright 2021 - Max Base, <maxbasecode@gmail.com>
 * This file is part of One Programming Language.
 *
 * one-language is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * one-language is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with one-language.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "one.h"

void error(char *message) {
	fprintf(stderr, message);
}

void main_help(void) {
	print(
		"One is a programming language and its here to manage your One programs.\n"
		"\n"
		"Usage:\n"
		"\n"
		"	one <command> [arguments]\n"
		"\n"
		"The commands are:\n"
		"\n"
		"	build       compile packages and dependencies\n"
		"	run         compile and run One program\n"
		"	version     print One version\n"
		"\n"
	);
}

void main_badcommand(int argc, char *argv[]) {
	if(argc > 1) {
		printf("one %s: unknown command\n", argv[1]);
		printf("Run 'one help' for usage.\n");
	}
}
void main_badparam(void) {
	print("parameter flag provided but not supported!\n");
}

void main_badflag(void) {
	print("argument flag provided but not supported!\n");
}

void main_version(int argc) {
	if(argc > 2) {
		main_badflag();
	}
	print("One version one" VERSION " " ARCH "\n");
}

void main_build(int argc, char *argv[]) {
	if(argc <= 2) {
		main_badflag();
		print("Please enter your one filename program!\n");
		return;
	}
	char *data = read_file(argv[2]);
	if(data == NULL) {
		error("We cannot read your input file, probably it's not available or it's OS-permission problem!\n");
		return;
	}

	Source s = source_new_data(data);
	printf("%s\n------------------\n", s.data);
	lexer_scan(&s);
}

void main_run(int argc, char *argv[]) {
	main_build(argc, argv);
}

void main_parse(int argc, char *argv[]) {
	// printf("-->%d\n", argc);
	// for(int i=0; i<argc; i++) {
	// 	printf("   %s\n", argv[i]);
	// }

	// $ one
	if(argc == 1) {
		main_help();
		return;
	}

	// $ one version
	if(strcmp(argv[1], "version") == 0) {
		main_version(argc);
	}
	// $ one build
	else if(strcmp(argv[1], "build") == 0) {
		main_build(argc, argv);
	}
	// $ one run
	else if(strcmp(argv[1], "run") == 0) {
		main_run(argc, argv);
	}
	// $ one help
	else if(strcmp(argv[1], "help") == 0) {
		main_help();
	}
	// otherwise
	else {
		main_badcommand(argc, argv);
	}

}

int main(int argc, char *argv[]) {
	main_parse(argc, argv);
	return 0;
}
