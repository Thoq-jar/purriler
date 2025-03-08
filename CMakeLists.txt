cmake_minimum_required(VERSION 3.20)
project(purriler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

if(APPLE)
    set(LLVM_DIR "/opt/homebrew/opt/llvm/lib/cmake/llvm")
    set(Clang_DIR "/opt/homebrew/opt/llvm/lib/cmake/clang")
else()

endif()

find_package(LLVM 19.1.2 REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})

add_executable(purriler 
    src/main.cpp
    src/options.cpp
    src/ui.cpp
)

if(APPLE)
    target_link_libraries(purriler
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
    )
else()
    target_link_libraries(purriler
        -Wl,--start-group
        clang-cpp
        LLVM
        -Wl,--end-group
    )
endif()

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_ID Clang)
