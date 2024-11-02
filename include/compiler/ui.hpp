#pragma once
#include <string>

extern const std::string LOGO;

void print_usage(const char* program);
void print_progress(const std::string& message, int depth = 0);
void print_result(bool success, const std::string& message, int depth = 0); 