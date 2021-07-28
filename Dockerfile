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

# LLVM installation
COPY install_llvm.sh /
RUN chmod +x install_llvm.sh
RUN ./install_llvm.sh ${LLVM_VERSION} && rm install_llvm.sh

ENV CXX=clang++
ENV CC=clang

# pre-commit installation
RUN pip install pre-commit

# Work directory setup
WORKDIR /One

COPY src/ ./src/
COPY test/ ./test/

# Building
WORKDIR /One/src

RUN cd parser && chmod +x build.sh && ./build.sh

RUN cd lexer && chmod +x build.sh && ./build.sh

RUN cd lexer && chmod +x test.sh && ./test.sh

# Testing
WORKDIR /One/test
RUN chmod +x build.sh && ./build.sh