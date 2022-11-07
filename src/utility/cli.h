typedef struct {
    int argc;
    char** argv;
} cli_args;

typedef struct {
    char* data;

    char* input;
    char* input_dir;

    char* output;
    char* output_dir;

    bool is_debug;
    bool is_raw_input;
} cli_options;

int cli_parse(cli_args* arguments);
