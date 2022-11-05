typedef struct {
    int argc;
    char** argv;
} cli_args;

typedef struct {
    char* input;
    char* input_dir;

    char* output;
    char* output_dir;

    bool is_debug;
} cli_options;
