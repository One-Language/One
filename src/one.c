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

void main_parse(int argc, char *argv[]) {
	printf("-->%d\n", argc);
	for(int i=0; i<argc; i++) {
		printf("   %s\n", argv[i]);
	}
}

int main(int argc, char *argv[]) {
	main_parse(argc, argv);
	main_help();
	return 0;
}
