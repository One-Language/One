#ifndef _ARGS_H_
#define _ARGS_H_

typedef enum {
  EMIT_LLVM_BC,
  EMIT_LLVM_IR,
  EMIT_LINK,
  EMIT_OBJ,
  EMIT_ASM,
  EMIT_JIT,
} EmitFormat;

typedef struct {
  bool help;
  bool version;
  bool debug;
  bool compiler_debug;
  int size_opt;
  int speed_opt;
  EmitFormat emit_format;
  char* target;
  char* output_file;
  int input_file_count;
  char** input_files;
  int library_count;
  char** libraries;
  int library_directory_count;
  char** library_directories;
  int argc;
  const char* const* argv;
  const char* const* env;
  bool force_target;
  bool force_interpreter;
} Args;

#endif
