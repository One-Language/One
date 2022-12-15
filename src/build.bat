gcc one.c -c -o one.o
gcc cli.c -c -o cli.o
gcc one.o cli.o -o one.exe
one -l input.one
