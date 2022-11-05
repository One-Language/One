typedef struct {
} Token;

typedef struct {
    char* input;
    int input_size;

    char* file;
    char* file_dir;

    Token** tokens;
    int token_size;
} Lexer;

Lexer* lexer_new(char*);
int lexer_run(Lexer*);
