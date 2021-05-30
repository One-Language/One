/**
 The One Programming Language

 File: error.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "error.h"

void ErrorsInit(ErrorsContainer *errors) {
    errors->error_count = 0;
    errors->error_capacity = 10;
}

char *ErrorLevelName(ErrorLevel level) {
    switch (level) {
        case ERROR:
            return "ERROR";
            break;
        case WARNING:
            return "WARNING";
            break;
        case NOTE:
            return "NOTE";
            break;
        default:
            return "UNKNOWN";
    }
}

void ErrorsPrint(FILE *f, Error *error) {
    char *message;
    Location position;
    ErrorLevel level;
    printf("[%s] %s", ErrorLevelName(error->level), error->message);

    if (error->location.line != 0 && error->location.column != 0) {
        printf(" at line %d:%d", error->location.line, error->location.column);
    }

    if (error->filename!= NULL) {
        printf(" file %s", error->filename);
    }

    printf("\n");
}

void ErrorsPrints(FILE *f, ErrorsContainer *errors) {
    for (int i = 0; i < errors->error_count; i++) {
        ErrorsPrint(f, &errors->errors[i]);
    }
}

void ErrorsAdd(ErrorsContainer *errors, ErrorLevel level, Location location, char *message) {
//    error_count;
//    error_capacity;
}

void ErrorsFree(ErrorsContainer *errors) {
}

void error(char *message) {
    // TODO: this function will remove and ErrorsAdd() will be use!
    printf("[Error]: %s", message);
}
