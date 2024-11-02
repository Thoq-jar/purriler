#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <string_view>

using namespace std;
namespace fs = filesystem;

void print_usage(const char* program) {
    cerr << "[-] Usage: " << program << " <input.cpp> [options]\n"
              << "Options:\n"
              << "  --out-dir=<path>    Output directory for generated files\n";
}

string parse_out_dir(int argc, char* argv[]) {
    string_view out_dir = ".";
    const string prefix = "--out-dir=";
    
    for (int i = 2; i < argc; i++) {
        string_view arg(argv[i]);
        if (arg.substr(0, prefix.length()) == prefix) {
            out_dir = arg.substr(prefix.length());
            break;
        }
    }
    
    fs::path dir_path(out_dir);
    if (!fs::exists(dir_path)) {
        fs::create_directories(dir_path);
    }
    
    return string(out_dir);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    string input_file = argv[1];
    string out_dir = parse_out_dir(argc, argv);
    
    fs::path input_path(input_file);
    fs::path base_name = input_path.stem();
    fs::path output_path = fs::path(out_dir) / base_name;
    
    string emit_ir_cmd = "clang++ -S -emit-llvm -fPIC "
        "-target x86_64-unknown-linux-gnu "
        "-I/home/linuxbrew/.linuxbrew/Cellar/llvm/19.1.2/include "
        "-I/home/linuxbrew/.linuxbrew/include "
        "-fno-rtti " + input_file + " -o " + output_path.string() + ".ll";
    
    string codegen_cmd = "llc -filetype=obj -relocation-model=pic "
        "-mtriple=x86_64-unknown-linux-gnu " + 
        output_path.string() + ".ll -o " + output_path.string() + ".o";
    
    string link_cmd = "clang++ -fPIC " + output_path.string() + ".o "
        "-L/home/linuxbrew/.linuxbrew/lib "
        "-o " + output_path.string();

    cout << "[/] Starting compilation pipeline:\n";
    
    cout << "[1] LLVM IR Generation...\n";
    if (system(emit_ir_cmd.c_str()) != 0) {
        cerr << "[-] LLVM IR Generation failed\n";
        return 1;
    }
    
    cout << "[2] LLVM CodeGen (Machine Code Generation)...\n";
    if (system(codegen_cmd.c_str()) != 0) {
        cerr << "[-] LLVM CodeGen failed\n";
        return 1;
    }
    
    cout << "[3] LLVM Emit Object...\n";
    if (system(link_cmd.c_str()) != 0) {
        cerr << "[-] Emit Object failed\n";
        return 1;
    }
    
    cout << "[!] Compilation pipeline completed successfully!\n";
    return 0;
}