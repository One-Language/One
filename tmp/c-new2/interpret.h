/**
 The One Programming Language

 File: interpret.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef ONE_INTERPRET_H
#define ONE_INTERPRET_H

int interpret_file(const char* path);

int interpret_source(char* source, const char* path);

#endif //ONE_INTERPRET_H
