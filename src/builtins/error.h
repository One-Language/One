//
// Created by Max on 9/4/2022.
//

#ifndef _ONE_BUILTINS_ERROR_H_
#define _ONE_BUILTINS_ERROR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
//#include "../stages/lexer/lexer.h"

// #include "../stages/lexer/lexer.h"

typedef struct {
    int offset;
    int line;
    int column;
} Location;

typedef enum
{
    ERROR_WARNING,
    ERROR_PANIC,

    ERROR_BUILTIN,

    ERROR_TOKEN,
    ERROR_LEXER,
    ERROR_PARSER,
    ERROR_AST,
    ERROR_TREE,
} ErrorType; // TODO

typedef enum {
    ERROR_LEXER_BAD_CHARACTER,
} ErrorSubType;

typedef struct {
    ErrorType type;
    ErrorSubType subtype;
    char* message;
    char* source;
    Location start;
    Location end;
} Error;

Error* error_init(ErrorType type, ErrorSubType subtype, char* message, char* source, Location start, Location end);

#define RESET "\033[0m"
#define BLACK "\033[30m" /* Black */
#define RED "\033[31m" /* Red */
#define GREEN "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m" /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m" /* Cyan */
#define WHITE "\033[37m" /* White */
#define BOLDBLACK "\033[1m\033[30m" /* Bold Black */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m" /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m" /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m" /* Bold White */

//#define check(format, args...) \
//	printf(GREEN "Check: " format " at %d on %s in %s" "\n" RESET, ##args, __LINE__, "file", __FUNCTION__);

//#define check(format, args...)

#ifdef _ONE_TEST_

#define debug(format, args...)    \
	printf(WHITE "Debug: " format \
				 "\n" RESET,      \
		 ##args);
	 // printf(WHITE "Debug: " format " at %d on %s in %s" \
	// 			 "\n" RESET,                           \
	// 	 ##args,                                       \
	// 	 __LINE__,                                     \
	// 	 "file",                                       \
	// 	 __FUNCTION__);
	 // #define debug(format, args...)

#define debug_parser(format, args...)   \
	printf(WHITE "Parser INFO: " format \
				 "\n" RESET,            \
		 ##args);
	 // printf(BLUE "Parser INFO: " format " at %d on %s in %s" \
	// 			"\n" RESET,                                 \
	// 	 ##args,                                            \
	// 	 __LINE__,                                          \
	// 	 "file",                                            \
	// 	 __FUNCTION__);
	 // #define debug_parser(format, args...)

#define debug_ast(format, args...)  \
	printf(BLUE "Ast INFO: " format \
				"\n" RESET,         \
		 ##args);
	 // printf(BLUE "Ast INFO: " format " at %d on %s in %s" \
	// 			"\n" RESET,                              \
	// 	 ##args,                                         \
	// 	 __LINE__,                                       \
	// 	 "file",                                         \
	// 	 __FUNCTION__);
	 // #define debug_ast(format, args...)

#define debug_tree(format, args...)  \
	printf(BLUE "Tree INFO: " format \
				"\n" RESET,          \
		 ##args);
	 // printf(BLUE "Tree INFO: " format " at %d on %s in %s" \
	// 			"\n" RESET,                               \
	// 	 ##args,                                          \
	// 	 __LINE__,                                        \
	// 	 "file",                                          \
	// 	 __FUNCTION__);
	 // #define debug_tree(format, args...)

#define debug_builtins(format, args...)    \
	printf(GREEN "Builtins Debug: " format \
				 "\n" RESET,               \
		 ##args);
	 // printf(GREEN "Builtins Debug: " format " at %d on %s in %s" \
	// 			 "\n" RESET,                                    \
	// 	 ##args,                                                \
	// 	 __LINE__,                                              \
	// 	 "file",                                                \
	// 	 __FUNCTION__);
	 // #define debug_builtins(format, args...)

//////////////////

#define info(format, args...)        \
	printf(BOLDWHITE "INFO: " format \
					 "\n" RESET,     \
		 ##args);
	 // printf(BOLDWHITE "INFO: " format " at %d on %s in %s" \
	// 				 "\n" RESET,                          \
	// 	 ##args,                                          \
	// 	 __LINE__,                                        \
	// 	 "file",                                          \
	// 	 __FUNCTION__);
	 // #define info(format, args...)

#define info_token(format, args...)         \
	printf(BOLDYELLOW "Token INFO: " format \
					  "\n" RESET,           \
		 ##args);
	 // printf(BOLDYELLOW "Token INFO: " format " at %d on %s in %s" \
	// 				  "\n" RESET,                                \
	// 	 ##args,                                                 \
	// 	 __LINE__,                                               \
	// 	 "file",                                                 \
	// 	 __FUNCTION__);
	 // #define info(info_token, args...)

#define info_lexer(format, args...)       \
	printf(BOLDCYAN "Lexer INFO: " format \
					"\n" RESET,           \
		 ##args);
	 // printf(BOLDCYAN "Lexer INFO: " format " at %d on %s in %s" \
	// 				"\n" RESET,                                \
	// 	 ##args,                                               \
	// 	 __LINE__,                                             \
	// 	 "file",                                               \
	// 	 __FUNCTION__);
	 // #define info_lexer(info_token, args...)

#define info_parser(format, args...)                             \
	printf(BOLDWHITE "Parser INFO: " format " at %d on %s in %s" \
					 "\n" RESET,                                 \
		 ##args,                                                 \
		 __LINE__,                                               \
		 "file",                                                 \
		 __FUNCTION__);
	 // #define info_parser(info_token, args...)

#define info_ast(format, args...)       \
	printf(BOLDBLUE "Ast INFO: " format \
					"\n" RESET,         \
		 ##args);
	 // printf(BOLDBLUE "Ast INFO: " format " at %d on %s in %s" \
	// 				"\n" RESET,                              \
	// 	 ##args,                                             \
	// 	 __LINE__,                                           \
	// 	 "file",                                             \
	// 	 __FUNCTION__);
	 // #define info_ast(info_token, args...)

#define info_tree(format, args...)       \
	printf(BOLDBLUE "Tree INFO: " format \
					"\n" RESET,          \
		 ##args);
	 // printf(BOLDBLUE "Tree INFO: " format " at %d on %s in %s" \
	// 				"\n" RESET,                               \
	// 	 ##args,                                              \
	// 	 __LINE__,                                            \
	// 	 "file",                                              \
	// 	 __FUNCTION__);
	 // #define info_tree(info_token, args...)

#define info_builtins(format, args...)    \
	printf(GREEN "Builtins INFO: " format \
				 "\n" RESET,              \
		 ##args);
	 // printf(GREEN "Builtins INFO: " format " at %d on %s in %s" \
	// 			 "\n" RESET,                                   \
	// 	 ##args,                                               \
	// 	 __LINE__,                                             \
	// 	 "file",                                               \
	// 	 __FUNCTION__);
	 // #define info_builtins(format, args...)

#else

#define debug(format, args...)

#define debug_parser(format, args...)

#define debug_ast(format, args...)

#define debug_tree(format, args...)

#define debug_builtins(format, args...)

/////////

#define info(format, args...)

#define info_token(format, args...)

#define info_lexer(format, args...)

#define info_parser(format, args...)

#define info_ast(format, args...)

#define info_tree(format, args...)

#define info_builtins(format, args...)

#endif

#define error_warning(format, ...) error(ERROR_WARNING, __LINE__, "file", __FUNCTION__, format, ##args)

#define error_panic(format, args...) error(ERROR_PANIC, __LINE__, "file", __FUNCTION__, format, ##args)

#define error_token(format, args...) error(ERROR_TOKEN, __LINE__, "file", __FUNCTION__, format, ##args)

#define error_lexer(format, args...) error(ERROR_TOKEN, __LINE__, "file", __FUNCTION__, format, ##args)

#define error_parser(format, args...) error(ERROR_PARSER, __LINE__, "file", __FUNCTION__, format, ##args)

#define error_ast(format, args...) error(ERROR_TREE, __LINE__, "file", __FUNCTION__, format, ##args)

#define error_tree(format, args...) error(ERROR_TREE, __LINE__, "file", __FUNCTION__, format, ##args)

#define error_builtins(format, args...) error(ERROR_PARSER, __LINE__, "file", __FUNCTION__, format, ##args)

/*
 * @function: error
 * @description: Occur a error/warning at the runtime, If that was not a warning so we will exit the program immediately
 * @arguments: ErrorType, int line, const char* file, const char* function, const char* format varg...
 * @return: void; nothing
 */
void error(ErrorType type, int line, const char* file, const char* function, const char* format, ...);

/*
 * @function: error_name
 * @description: Convert a ErrorType value to char*, mapping to its name
 * @arguments: ErrorType
 * @return: char*
 */
char* error_name(ErrorType type);

#endif // _ONE_BUILTINS_ERROR_H_
