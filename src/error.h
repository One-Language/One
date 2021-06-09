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

#define debug(format, args...) printf("Debug: " format "\n", ##args)

void error(ErrorType type, const char* format, ...);

char* error_name(ErrorType type);

#define error_panic(format, ...) error(ERROR_PANIC, format, __VA_ARGS__)

#define error_warning(format, ...) error(ERROR_WARNING, format, __VA_ARGS__)

#define error_token(format, ...) error(ERROR_TOKEN, format, __VA_ARGS__)

#define error_parser(format, ...) error(ERROR_PARSER, format, __VA_ARGS__)

#endif //ONE_ERROR_H
