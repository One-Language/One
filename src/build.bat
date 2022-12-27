gcc one.c -c -o one.o -g
gcc cli.c -c -o cli.o -g
gcc file.c -c -o file.o -g
gcc token.c -c -o token.o -g
gcc lexer.c -c -o lexer.o -g
gcc parser.c -c -o parser.o -g
gcc ast.c -c -o ast.o -g
gcc string.c -c -o string.o -g
gcc array.c -c -o array.o -g
gcc generator.c -c -o generator.o -g
gcc value.c -c -o value.o -g
gcc one.o cli.o file.o lexer.o token.o parser.o ast.o string.o array.o generator.o value.o -o one.exe -g
@REM one -l input.one -x
@REM one -p input.one
@REM one -p input.one -x
one -g input.one
