#include "../include/compiler/ui.hpp"
#include <iostream>
#include <string>

const std::string LOGO = R"(
         _._     _,-'""`-._
        (,-.`._,'(       |\`-/|
            `-.-' \ )-`( , o o)
                  `-    \`_`"'-
)";

void print_usage(const char* program) {
    const char* version = "1.0.0";
    std::cerr << "Purriler v" << version << " - A C++ Compiler on LLVM 19\n\n"
              << "Usage: " << program << " <input files...> [options]\n"
              << "Options:\n"
              << "  --out-dir=<path>    Output directory for generated files\n"
              << "  -o <name>           Name of the output binary\n"
              << "  -v, --version       Show version information\n"
              << "  -h, --help          Show this help message\n";
}

void print_progress(const std::string& message, int depth) {
    for (int i = 0; i < depth - 1; i++) {
        std::cout << "    │";
    }
    
    if (depth == 0) {
        std::cout << "[/] ";
    } else {
        std::cout << "    ├── [" << depth << "] ";
    }
    std::cout << message << "\n";
}

void print_result(bool success, const std::string& message, int depth) {
    for (int i = 0; i < depth - 1; i++) {
        std::cout << "    │";
    }
    
    if (depth == 0) {
        std::cout << (success ? "[+] " : "[-] ");
    } else {
        std::cout << "    └── " << (success ? "[+] " : "[-] ");
    }
    std::cout << message << "\n";
} 