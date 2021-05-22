all:
	mkdir -p `dirname build/objs/codegen/assignments.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/codegen/assignments.o src/codegen/assignments.c
	 
	mkdir -p `dirname build/objs/codegen/casts.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/codegen/casts.o src/codegen/casts.c
	 
	mkdir -p `dirname build/objs/codegen/codegen.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/codegen/codegen.o src/codegen/codegen.c
	 
	mkdir -p `dirname build/objs/codegen/const.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/codegen/const.o src/codegen/const.c
	 
	mkdir -p `dirname build/objs/codegen/general.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/codegen/general.o src/codegen/general.c
	 
	mkdir -p `dirname build/objs/codegen/operations.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/codegen/operations.o src/codegen/operations.c
	 
	mkdir -p `dirname build/objs/codegen/symbols.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/codegen/symbols.o src/codegen/symbols.c
	 
	mkdir -p `dirname build/objs/codegen/types.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/codegen/types.o src/codegen/types.c
	 
	mkdir -p `dirname build/objs/common/arraylist.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/common/arraylist.o src/common/arraylist.c
	 
	mkdir -p `dirname build/objs/common/exec.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/common/exec.o src/common/exec.c
	 
	mkdir -p `dirname build/objs/common/hashtable.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/common/hashtable.o src/common/hashtable.c
	 
	mkdir -p `dirname build/objs/common/queue.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/common/queue.o src/common/queue.c
	 
	mkdir -p `dirname build/objs/common/util.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/common/util.o src/common/util.c
	 
	mkdir -p `dirname build/objs/driver/args.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/driver/args.o src/driver/args.c
	 
	mkdir -p `dirname build/objs/driver/compile.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/driver/compile.o src/driver/compile.c
	 
	mkdir -p `dirname build/objs/driver/error.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/driver/error.o src/driver/error.c
	 
	mkdir -p `dirname build/objs/driver/file.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/driver/file.o src/driver/file.c
	 
	mkdir -p `dirname build/objs/driver/jit.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/driver/jit.o src/driver/jit.c
	 
	mkdir -p `dirname build/objs/parser/ast.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/parser/ast.o src/parser/ast.c
	 
	mkdir -p `dirname build/objs/parser/ast-printer.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/parser/ast-printer.o src/parser/ast-printer.c
	 
	mkdir -p `dirname build/objs/parser/parser.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/parser/parser.o src/parser/parser.c
	 
	mkdir -p `dirname build/objs/parser/scanner.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/parser/scanner.o src/parser/scanner.c
	 
	mkdir -p `dirname build/objs/parser/token.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/parser/token.o src/parser/token.c
	 
	mkdir -p `dirname build/objs/tumble.o`
	gcc `llvm-config --cflags` -I./src -Wall -O3 -c -o build/objs/tumble.o src/tumble.c
	 
	mkdir -p `dirname build/bin/tumble`
	g++ `llvm-config --cflags` -I./src -Wall -O3 -o build/bin/tumble build/objs/codegen/assignments.o build/objs/codegen/casts.o build/objs/codegen/codegen.o build/objs/codegen/const.o build/objs/codegen/general.o build/objs/codegen/operations.o build/objs/codegen/symbols.o build/objs/codegen/types.o build/objs/common/arraylist.o build/objs/common/exec.o build/objs/common/hashtable.o build/objs/common/queue.o build/objs/common/util.o build/objs/driver/args.o build/objs/driver/compile.o build/objs/driver/error.o build/objs/driver/file.o build/objs/driver/jit.o build/objs/parser/ast.o build/objs/parser/ast-printer.o build/objs/parser/parser.o build/objs/parser/scanner.o build/objs/parser/token.o build/objs/tumble.o `llvm-config --ldflags --libs --system-libs`
