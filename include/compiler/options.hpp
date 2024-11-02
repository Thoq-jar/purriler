#pragma once
#include <string>
#include <vector>

struct CompilerOptions {
    std::vector<std::string> input_files;
    std::string out_dir = ".";
    std::string output_name = "a.out";
    bool show_version = false;
    bool show_help = false;
};

CompilerOptions parse_options(int argc, char* argv[]); 