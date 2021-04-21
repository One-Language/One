build: out one

out:
	mkdir -p out
	mkdir -p out/lexer
	mkdir -p out/parser
	mkdir -p out/compiler

out/lexer/lexer.o: src/lexer/lexer.c src/lexer/lexer.h
	gcc -c src/lexer/lexer.c -o out/lexer/lexer.o -Wall -Wextra

out/lexer/source.o: src/lexer/source.c src/lexer/source.h
	gcc -c src/lexer/source.c -o out/lexer/source.o -Wall -Wextra

out/one.o: src/one.c src/one.h
	gcc -c src/one.c -o out/one.o -Wall -Wextra

out/io.o: src/io.c src/io.h
	gcc -c src/io.c -o out/io.o -Wall -Wextra

one: out/one.o out/io.o out/lexer/lexer.o out/lexer/source.o
	gcc \
		out/one.o \
		out/io.o \
		out/lexer/lexer.o \
		out/lexer/source.o \
		-o one -Wall -Wextra

clean:
	-rm -rf out/*.o
	-rm -f one
