cmake_minimum_required(VERSION 3.20)
project(compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

set(LLVM_DIR "/home/linuxbrew/.linuxbrew/lib/cmake/llvm")
set(Clang_DIR "/home/linuxbrew/.linuxbrew/lib/cmake/clang")

find_package(LLVM 19.1.2 REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})

add_executable(compiler src/main.cpp)

target_link_libraries(compiler
    -Wl,--start-group
    clang-cpp
    LLVM
    clangBasic
    clangDriver
    clangFrontend
    clangTooling
    clangCodeGen
    clangSerialization
    clangParse
    clangSema
    clangAnalysis
    clangAST
    clangLex
    -Wl,--end-group
)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_ID Clang)
