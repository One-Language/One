//
// Created by max on 6/9/21.
//

#ifndef ONE_ERROR_H
#define ONE_ERROR_H

typedef enum
{
	ERROR_WARNING,
	ERROR_PANIC,
	ERROR_TOKEN,
	ERROR_PARSER,
} ErrorType;

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
//	printf(GREEN "Check: " format "\n" RESET, ##args);

//#define check(format, args...)

#define debug(format, args...) \
	printf(WHITE "Debug: " format "\n" RESET, ##args);

#define debug_token(format, args...) \
	printf(YELLOW "Debug: " format "\n" RESET, ##args);

#define debug_lexer(format, args...) \
	printf(CYAN "Debug: " format "\n" RESET, ##args);

#define debug_parser(format, args...) \
	printf(GREEN "Debug: " format "\n" RESET, ##args);

#define info_token(format, args...) \
	printf(BOLDYELLOW "INFO: " format "\n" RESET, ##args);

#define info_lexer(format, args...) \
	printf(BOLDCYAN "INFO: " format "\n" RESET, ##args);

#define info_parser(format, args...) \
	printf(BOLDGREEN "INFO: " format "\n" RESET, ##args);

//#define debug(format, args...)

void error(ErrorType type, const char* format, ...);

char* error_name(ErrorType type);

#define error_panic(format, args...) error(ERROR_PANIC, format, ##args)

#define error_warning(format, ...) error(ERROR_WARNING, format, ##args)

#define error_token(format, args...) error(ERROR_TOKEN, format, ##args)

#define error_parser(format, args...) error(ERROR_PARSER, format, ##args)

#endif //ONE_ERROR_H
