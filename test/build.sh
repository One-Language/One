FLAGS="-o"
FILES="../src/builtins/array.c ../src/builtins/error.c ../src/builtins/file.c ../src/ast/ast.c ../src/parser/parser.c ../src/parser/parser_token.c ../src/lexer/lexer.c ../src/lexer/tokenizer/token.c ../src/lexer/tokenizer/tokenizer.c -lLLVM-12 -D_ONE_TEST_"
CC="clang"

# compile argument
$CC argument.test.c $FLAGS argument $FILES
# compile lexer
$CC lexer.test.c $FLAGS lexer $FILES
# compile parser
$CC parser.test.c $FLAGS parser $FILES
# compiler ast
$CC ast.test.c $FLAGS ast $FILES

# run
./arguments
./lexer
./parser
./ast
