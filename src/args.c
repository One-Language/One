const Args default_args = {
  .help = false,
  .version = false,
  .debug = false,
  .compiler_debug = false,
  .size_opt = 0,
  .speed_opt = 1,
  .emit_format = EMIT_LINK,
  .target = NULL,
  .output_file = NULL,
  .input_file_count = 0,
  .input_files = NULL,
  .library_count = 0,
  .libraries = NULL,
  .library_directory_count = 0,
  .library_directories = NULL,
  .argc = 0,
  .argv = NULL,
  .env = NULL,
  .force_target = false,
  .force_interpreter = false,
};

void parseArgs(int argc, const char* const* argv, const char* const* env, Args* args, ErrorContext* error_context)
{
  args->argc = argc;
  args->argv = argv;
  args->env = env;
  *args = default_args;

  ArrayList files;
  initArrayList(&files);

  ArrayList libraries;
  initArrayList(&libraries);

  ArrayList library_directories;
  initArrayList(&library_directories);

  ArrayList include_directories;
  initArrayList(&include_directories);

  for(int i = 1; i < argc; i++) {
    if(argv[i][0] != '-') { // it's a filename
      pushToArrayList(&files, (void*)argv[i]); // append filename to files list
    } else {
      if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
        args->help = true;
      } else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
        args->version = true;
      } else if(strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--debug") == 0) {
        args->debug = true;
      } else if(strcmp(argv[i], "--compiler-debug") == 0) {
        args->compiler_debug = true;
      }

      else if(strcmp(argv[i], "-O0") == 0) {
        args->speed_opt = 0;
      } else if(strcmp(argv[i], "-O1") == 0) {
        args->speed_opt = 1;
      } else if(strcmp(argv[i], "-O2") == 0) {
        args->speed_opt = 2;
      } else if(strcmp(argv[i], "-O3") == 0) {
        args->speed_opt = 3;
      }

      else if(strcmp(argv[i], "-Os") == 0) {
        args->size_opt = 1;
      } else if(strcmp(argv[i], "-Oz") == 0) {
        args->size_opt = 2;
      } else if(strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--emit") == 0) {
        i++;
        if(strcmp(argv[i], "llvm-bc") == 0) {
          args->emit_format = EMIT_LLVM_BC;
        } else if(strcmp(argv[i], "llvm-ir") == 0) {
          args->emit_format = EMIT_LLVM_IR;
        } else if(strcmp(argv[i], "link") == 0) {
          args->emit_format = EMIT_LINK;
        } else if(strcmp(argv[i], "obj") == 0) {
          args->emit_format = EMIT_OBJ;
        } else if(strcmp(argv[i], "asm") == 0) {
          args->emit_format = EMIT_ASM;
        } else if(strcmp(argv[i], "jit") == 0) {
          args->emit_format = EMIT_JIT;
        } else {
          addErrorf(error_context, NOPOS, WARNING, "The unknown emition type '%s' will be ignored", argv[i]);
        }
      } else if(strcmp(argv[i], "-L") == 0) {
        i++;
        if(i >= argc) {
          addError(error_context, "Option is missing the library path, ignoring the option", NOPOS, WARNING);
        } else {
          pushToArrayList(&library_directories, (void*)argv[i]);
        }
      } else if(strcmp(argv[i], "-l") == 0) {
        i++;
        if(i >= argc) {
          addError(error_context, "Option is missing the library name, ignoring the option", NOPOS, WARNING);
        } else {
          pushToArrayList(&libraries, (void*)argv[i]);
        }
      } else if(strncmp(argv[i], "-L", 2) == 0) {
        if(strlen(argv[i]) <= 2) {
          addError(error_context, "Option is missing the library path, ignoring the option", NOPOS, WARNING);
        } else {
          pushToArrayList(&library_directories, (void*)argv[i] + 2);
        }
      } else if(strncmp(argv[i], "-l", 2) == 0) {
        if(strlen(argv[i]) <= 2) {
          addError(error_context, "Option is missing the library name, ignoring the option", NOPOS, WARNING);
        } else {
          pushToArrayList(&libraries, (void*)argv[i] + 2);
        }
      } else if(strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--target") == 0) {
        i++;
        if(i >= argc) {
          addError(error_context, "Option is missing the target value, ignoring the option", NOPOS, WARNING);
        } else {
          args->target = (char*)argv[i];
        }
      } else if(strcmp(argv[i], "--force-target") == 0) {
        args->force_target = true;
      } else if(strcmp(argv[i], "--force-interpreter") == 0) {
        args->force_interpreter = true;
      } else if(strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
        i++;
        if(i >= argc) {
          addError(error_context, "Option is missing the output filepath, ignoring the option", NOPOS, WARNING);
        } else {
          args->output_file = (char*)argv[i];
        }
      } else {
        addErrorf(error_context, NOPOS, WARNING, "The unknown option '%s' will be ignored", argv[i]);
      }

    }
  }
}

void printHelpText(FILE* file, int argc, const char* const* argv)
{
  fprintf(file, "Usage: %s [options] file...\n", argv[0]);
  fprintf(file, "Options:\n");
  fprintf(file, "    -h, --help                Print out this help text.\n");
  fprintf(file, "    -g, --debug               Include debug information in the build.\n");
  fprintf(file, "    -O0, -O1, -O2, -O3        Set the speed optimization level. (default: -O1)\n");
  fprintf(file, "    -Os, -Oz                  Set the size optimization level.\n");
  fprintf(file, "    -e, --emit [llvm-bc|llvm-ir|asm|obj|link|jit]\n");
  fprintf(file, "                              Set the type that should be generated. (default: link|obj)\n");
  fprintf(file, "    -t, --target TARGET       Set the target to compile for. (default: host)\n");
  fprintf(file, "        --force-target        Run the JIT for the selected target, ignoring the host target\n");
  fprintf(file, "        --force-interpreter   Run the interpreter even if JIT is supported\n");
  fprintf(file, "    -o, --output FILE         Output the result to the given file.\n");
  fprintf(file, "    -l NAME                   Add the given library to the linker.\n");
  fprintf(file, "    -L PATH                   Add the given path to the possible library locations.\n");
  fprintf(file, "    -v, --version             Output the one version\n");
}

void freeArgs(Args* args)
{
  free(args->input_files);
  free(args->libraries);
  free(args->library_directories);
  *args = default_args;
}
