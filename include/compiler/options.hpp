#pragma once
#include <string>
#include <vector>

struct CompilerOptions {
    std::vector<std::string> input_files;
    std::vector<std::string> include_paths;
    std::vector<std::string> library_paths;
    std::string out_dir = ".";
    std::string output_name = "a.out";
    std::string build_system_file = "";
    bool show_version = false;
    bool show_help = false;
};

CompilerOptions parse_options(int argc, char* argv[]);
CompilerOptions parse_build_file(const std::string& file_path);