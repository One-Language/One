#ifndef _ERROR_H_
#define _ERROR_H_

#define MAX_ERROR_FORMAT 1024

typedef enum {
    ERROR,
    WARNING,
    NOTE,
} ErrorLevel;

typedef struct {
    char* message;
    Position position;
    ErrorLevel level;
} Error;

typedef struct {
    int error_count;
    int error_capacity;
    Error* errors;
} ErrorContext;

#endif
