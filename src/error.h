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
//#define debug(format, args...)

void error(ErrorType type, const char* format, ...);

char* error_name(ErrorType type);

#define error_panic(format, args...) error(ERROR_PANIC, format, ##args)

#define error_warning(format, ...) error(ERROR_WARNING, format, ##args)

#define error_token(format, args...) error(ERROR_TOKEN, format, ##args)

#define error_parser(format, args...) error(ERROR_PARSER, format, ##args)

#endif //ONE_ERROR_H
