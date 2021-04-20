build: one

out/one.o: src/one.c
	gcc -c src/one.c -o out/one.o -Wall -Wextra

one: out/one.o
	gcc out/one.o -o one -Wall -Wextra

clean:
	-rm -rf out/*.o
	-rm -f one
