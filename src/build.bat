gcc one.c -c -o one.o -g
gcc cli.c -c -o cli.o -g
gcc file.c -c -o file.o -g
gcc one.o cli.o file.o -o one.exe -g
one -l input.one
