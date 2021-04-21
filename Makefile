build: out one

out:
	mkdir -p out
	mkdir -p out/lexer
	mkdir -p out/parser
	mkdir -p out/buffer
	mkdir -p out/compiler

out/buffer/sds.o: src/buffer/sds.c src/buffer/sds.h src/buffer/sdsalloc.h src/buffer/testhelp.h
	gcc -c src/lexer/token.c -o out/lexer/token.o -Wall -Wextra

out/lexer/token.o: src/lexer/token.c src/lexer/token.h
	gcc -c src/lexer/token.c -o out/lexer/token.o -Wall -Wextra

out/lexer/source.o: src/lexer/source.c src/lexer/source.h
	gcc -c src/lexer/source.c -o out/lexer/source.o -Wall -Wextra

out/lexer/lexer.o: src/lexer/lexer.c src/lexer/lexer.h
	gcc -c src/lexer/lexer.c -o out/lexer/lexer.o -Wall -Wextra

out/one.o: src/one.c out/io.o out/lexer/token.o out/lexer/source.o out/lexer/lexer.o 
	gcc \
		src/one.c \
		out/io.o \
		out/lexer/lexer.o \
		out/lexer/token.o \
		out/lexer/source.o \
		-o out/one.o -Wall -Wextra

out/io.o: src/io.c src/io.h
	gcc -c src/io.c -o out/io.o -Wall -Wextra

one: out/one.o
	mv out/one.o one

clean:
	-rm -rf out/*/*.o
	-rm -rf out/*.o
	-rm -f one
	-rm -f src/*.o
	-rm -f src/*/*.o
