#include "../include/compiler/options.hpp"
#include <filesystem>
#include <string_view>

namespace fs = std::filesystem;

CompilerOptions parse_options(int argc, char* argv[]) {
    CompilerOptions options;
    const std::string dir_prefix = "--out-dir=";
    
    for (int i = 1; i < argc; i++) {
        std::string_view arg(argv[i]);
        if (arg.substr(0, dir_prefix.length()) == dir_prefix) {
            options.out_dir = arg.substr(dir_prefix.length());
        } else if (arg == "-o" && i + 1 < argc) {
            options.output_name = argv[++i];
        } else if (arg == "-v" || arg == "--version") {
            options.show_version = true;
        } else if (arg == "-h" || arg == "--help") {
            options.show_help = true;
        } else {
            options.input_files.push_back(std::string(arg));
        }
    }
    
    fs::path dir_path(options.out_dir);
    if (!fs::exists(dir_path)) {
        fs::create_directories(dir_path);
    }
    
    return options;
} 