FROM alpine:latest
LABEL The One Programming Language

# LLVM version
ARG LLVM_VERSION=12.0.1

# LLVM dependencies
RUN apk --no-cache add \
	autoconf \
	automake \
	cmake \
	freetype-dev \
	g++ \
	gcc \
	libxml2-dev \
	linux-headers \
	make \
	musl-dev \
	ncurses-dev \
	python3 py3-pip \
    git

# Build and install LLVM
RUN wget "https://github.com/llvm/llvm-project/archive/llvmorg-${LLVM_VERSION}.tar.gz" || { echo 'Error downloading LLVM version ${LLVM_VERSION}' ; exit 1; }

RUN tar zxf llvmorg-${LLVM_VERSION}.tar.gz && rm llvmorg-${LLVM_VERSION}.tar.gz

RUN cd llvm-project-llvmorg-${LLVM_VERSION} && mkdir build

WORKDIR  /llvm-project-llvmorg-${LLVM_VERSION}/build

RUN cmake ../llvm \
    -G "Unix Makefiles" -DLLVM_TARGETS_TO_BUILD="X86" \
    -DLLVM_ENABLE_PROJECTS="clang;lld" \
    -DCMAKE_BUILD_TYPE=MinSizeRel \
    || { echo 'Error running CMake for LLVM' ; exit 1; }

RUN make -j$(nproc) || { echo 'Error building LLVM' ; exit 1; }
RUN make install || { echo 'Error installing LLVM' ; exit 1; }
RUN cd ../.. && rm -rf llvm-project-llvmorg-${LLVM_VERSION}

ENV CXX=clang++
ENV CC=clang

# pre-commit installation
RUN pip install pre-commit

# Work directory setup
COPY . /One
WORKDIR /One

# CMake configuration & building
RUN mkdir build
RUN cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -H/One -B/One/build -G "Unix Makefiles"
RUN cmake --build ./build --config Debug --target all -j 6 --

# Change directory to build
WORKDIR /One/build

# Running example input.one
RUN ./lexer ../src/input.one log
RUN cat log

# Running tests
RUN ./lexer_test
RUN ./parser_test
RUN ./argument_test

# Tests Dashboard
CMD ctest --output-on-failure
