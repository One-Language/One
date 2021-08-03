# compile argument
clang argument.test.c -o argument \
 ../src/builtins/array.c \
 ../src/builtins/error.c \
 ../src/builtins/file.c \
 ../src/ast/ast.c \
 ../src/parser/parser.c \
 ../src/parser/parser_token.c \
 ../src/lexer/lexer.c ../src/lexer/tokenizer/token.c ../src/lexer/tokenizer/tokenizer.c \
 -lLLVM-12 \
 -D_ONE_TEST_

# compile lexer
clang lexer.test.c -o lexer \
 ../src/builtins/array.c \
 ../src/builtins/error.c \
 ../src/builtins/file.c \
 ../src/ast/ast.c \
 ../src/parser/parser.c \
 ../src/parser/parser_token.c \
 ../src/lexer/lexer.c ../src/lexer/tokenizer/token.c ../src/lexer/tokenizer/tokenizer.c \
 -lLLVM-12 \
 -D_ONE_TEST_

# compile parser
clang parser.test.c -o parser \
 ../src/builtins/array.c \
 ../src/builtins/error.c \
 ../src/builtins/file.c \
 ../src/ast/ast.c \
 ../src/parser/parser.c \
 ../src/parser/parser_token.c \
 ../src/lexer/lexer.c ../src/lexer/tokenizer/token.c ../src/lexer/tokenizer/tokenizer.c \
 -lLLVM-12 \
 -D_ONE_TEST_

# compiler ast
clang ast.test.c -o ast \
 ../src/builtins/array.c \
 ../src/builtins/error.c \
 ../src/builtins/file.c \
 ../src/ast/ast.c \
 ../src/parser/parser.c \
 ../src/parser/parser_token.c \
 ../src/lexer/lexer.c ../src/lexer/tokenizer/token.c ../src/lexer/tokenizer/tokenizer.c \
 -lLLVM-12 \
 -D_ONE_TEST_

# run
./arguments
./lexer
./parser
./ast
