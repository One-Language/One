gcc one.c -c -o one.o
gcc cli.c -c -o cli.o
gcc file.c -c -o file.o
gcc one.o cli.o file.o -o one.exe
one -l input.one
