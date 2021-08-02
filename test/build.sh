clang lexer.test.c -o lexer \
 ../src/builtins/array.c \
 ../src/builtins/error.c \
 ../src/builtins/file.c \
 ../src/ast/ast.c \
 ../src/parser/parser.c \
 ../src/parser/parser_token.c \
 ../src/lexer/lexer.c ../src/lexer/tokenizer/token.c ../src/lexer/tokenizer/tokenizer.c \
 -lLLVM-12 -D_ONE_TEST_
./lexer
