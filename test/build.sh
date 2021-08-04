FLAGS="-o"
FILES="../src/builtins/array.c ../src/builtins/error.c ../src/builtins/file.c ../src/ast/ast.c ../src/parser/parser.c ../src/parser/parser_token.c ../src/lexer/lexer.c ../src/lexer/tokenizer/token.c ../src/lexer/tokenizer/tokenizer.c -lLLVM-12 -D_ONE_TEST_"

# compile argument
clang argument.test.c $FLAGS argument $FILES
# compile lexer
clang lexer.test.c $FLAGS lexer $FILES
# compile parser
clang parser.test.c $FLAGS parser $FILES
# compiler ast
clang ast.test.c $FLAGS ast $FILES

# run
./arguments
./lexer
./parser
./ast
