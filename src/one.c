#include "one.h"

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
	}
	// $ one run
	else if(strcmp(argv[1], "run") == 0) {
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
