#include "../include/compiler/options.hpp"
#include <filesystem>
#include <string_view>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

CompilerOptions parse_options(int argc, char* argv[]) {
    CompilerOptions options;
    const std::string dir_prefix = "--out-dir=";
    const std::string build_prefix = "--build-system=";
    
    for (int i = 1; i < argc; i++) {
        std::string_view arg(argv[i]);
        if (arg.substr(0, build_prefix.length()) == build_prefix) {
            std::string file_path = std::string(arg.substr(build_prefix.length()));
            if (fs::path(file_path).extension() != ".purr") {
                std::cerr << "Error: Build system file must have .purr extension\n";
                exit(1);
            }
            options.build_system_file = file_path;
            return parse_build_file(options.build_system_file);
        } else if (arg.substr(0, dir_prefix.length()) == dir_prefix) {
            options.out_dir = arg.substr(dir_prefix.length());
        } else if (arg == "-o" && i + 1 < argc) {
            options.output_name = argv[++i];
        } else if (arg == "-I" && i + 1 < argc) {
            options.include_paths.push_back(argv[++i]);
        } else if (arg == "-L" && i + 1 < argc) {
            options.library_paths.push_back(argv[++i]);
        } else if (arg == "-v" || arg == "--version") {
            options.show_version = true;
        } else if (arg == "-h" || arg == "--help") {
            options.show_help = true;
        } else {
            options.input_files.push_back(std::string(arg));
        }
    }
    
    if (fs::exists("/opt/homebrew")) {
        options.include_paths.push_back("/opt/homebrew/opt/llvm/include");
        options.include_paths.push_back("/opt/homebrew/include");
    }
    
    fs::path dir_path(options.out_dir);
    if (!fs::exists(dir_path)) {
        fs::create_directories(dir_path);
    }
    
    return options;
}

CompilerOptions parse_build_file(const std::string& file_path) {
    CompilerOptions options;
    std::ifstream file(file_path);
    std::string line;
    
    std::string current_array;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        if (line.find("sources = [") != std::string::npos) {
            current_array = "sources";
        } else if (line.find("include_paths = [") != std::string::npos) {
            current_array = "include_paths";
        } else if (line.find("library_paths = [") != std::string::npos) {
            current_array = "library_paths";
        } else if (line.find("output_dir = ") != std::string::npos) {
            options.out_dir = line.substr(line.find("\"") + 1);
            options.out_dir = options.out_dir.substr(0, options.out_dir.find("\""));
        } else if (line.find("output_name = ") != std::string::npos) {
            options.output_name = line.substr(line.find("\"") + 1);
            options.output_name = options.output_name.substr(0, options.output_name.find("\""));
        } else if (line.find("]") != std::string::npos) {
            current_array = "";
        } else if (!line.empty() && current_array != "") {
            std::string value = line.substr(line.find("\"") + 1);
            value = value.substr(0, value.find("\""));
            
            if (current_array == "sources") {
                options.input_files.push_back(value);
            } else if (current_array == "include_paths") {
                options.include_paths.push_back(value);
            } else if (current_array == "library_paths") {
                options.library_paths.push_back(value);
            }
        }
    }
    
    fs::path dir_path(options.out_dir);
    if (!fs::exists(dir_path)) {
        fs::create_directories(dir_path);
    }
    
    return options;
}