LLVM_VERSION=$1

wget "https://github.com/llvm/llvm-project/archive/llvmorg-${LLVM_VERSION}.tar.gz" || { echo 'Error downloading LLVM version ${LLVM_VERSION}' ; exit 1; }
tar zxf llvmorg-${LLVM_VERSION}.tar.gz && rm llvmorg-${LLVM_VERSION}.tar.gz

cd llvm-project-llvmorg-${LLVM_VERSION}
mkdir build
cd build

# Build and install LLVM:
cmake ../llvm \
    -G "Unix Makefiles" -DLLVM_TARGETS_TO_BUILD="X86" \
    -DLLVM_ENABLE_PROJECTS="clang;lld" \
    -DCMAKE_BUILD_TYPE=MinSizeRel \
    || { echo 'Error running CMake for LLVM' ; exit 1; }
make -j$(nproc) || { echo 'Error building LLVM' ; exit 1; }
make install || { echo 'Error installing LLVM' ; exit 1; }
cd ../..
rm -rf llvm-project-llvmorg-${LLVM_VERSION}
