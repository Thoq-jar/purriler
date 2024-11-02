#include "../include/compiler/options.hpp"
#include "../include/compiler/ui.hpp"
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using std::string;
using std::vector;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    CompilerOptions options = parse_options(argc, argv);
    
    if (options.show_version) {
        std::cout << LOGO << "\n";
        const char* version = "1.1c.0";
        std::cout << "Purriler v" << version << "\n";
        return 0;
    }
    
    if (options.show_help) {
        std::cout << LOGO << "\n";
        print_usage(argv[0]);
        return 0;
    }
    
    print_progress("Starting compilation pipeline");
    
    vector<string> obj_files;
    for (const string& input_file : options.input_files) {
        fs::path input_path(input_file);
        fs::path base_name = input_path.stem();
        fs::path output_path = fs::path(options.out_dir) / base_name;
        
        print_progress("Processing " + input_file, 1);

        string emit_ir_cmd = string("clang++ -S -emit-llvm -fPIC ")
            + "-target " + 
            (fs::exists("/opt/homebrew") ? "arm64-apple-darwin" : "x86_64-unknown-linux-gnu") + " ";
        
        for (const auto& flag : options.compiler_flags) {
            emit_ir_cmd += flag + " ";
        }
        
        for (const auto& path : options.include_paths) {
            emit_ir_cmd += "-I" + path + " ";
        }
        
        for (const auto& path : options.library_paths) {
            emit_ir_cmd += "-L" + path + " ";
        }
        
        emit_ir_cmd += "-fno-rtti " + input_file + " -o " + output_path.string() + ".ll";
        
        print_progress("Emit LLVM IR", 2);
        if (system(emit_ir_cmd.c_str()) != 0) {
            print_result(false, "Failed to emit LLVM IR", 3);
            return 1;
        }
        print_result(true, "LLVM IR generated successfully", 3);
        
        string codegen_cmd = string("llc -filetype=obj -relocation-model=pic ")
            + "-mtriple=" + 
            (fs::exists("/opt/homebrew") ? "arm64-apple-darwin" : "x86_64-unknown-linux-gnu") + " "
            + output_path.string() + ".ll -o " + output_path.string() + ".o 2>/dev/null";
        
        print_progress("LLVM CodeGen (Machine Code Generation)", 2);
        if (system(codegen_cmd.c_str()) != 0) {
            print_result(false, "CodeGen failed", 3);
            return 1;
        }
        print_result(true, "Machine code generated successfully", 3);
        
        obj_files.push_back(output_path.string() + ".o");
        if (!options.keep_files) {
            fs::remove(output_path.string() + ".ll");
        }
    }
    
    print_progress("LLVM Emit Object", 1);
    string link_cmd = string("clang++ -fPIC ");
    for (const auto& obj_file : obj_files) {
        link_cmd += obj_file + " ";
    }
    link_cmd += "-o " + (fs::path(options.out_dir) / options.output_name).string() + " 2>/dev/null";
    if (system(link_cmd.c_str()) != 0) {
        print_result(false, "Failed to emit object file(s)", 2);
        return 1;
    }
    print_result(true, "Sucessfully emited object file(s)", 2);
    
    fs::path final_binary = fs::path(options.out_dir) / options.output_name;
    print_result(true, "Compilation pipeline completed successfully!", 1);
    print_result(true, "Final binary: " + final_binary.string(), 1);
    
    if (!options.keep_files) {
        for (const auto& obj_file : obj_files) {
            fs::remove(obj_file);
        }
    }
    
    return 0;
}