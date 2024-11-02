#pragma once
#include <vector>
#include <map>

namespace analysis {
    class NumberAnalyzer {
    public:
        void addNumber(double num);
        double average() const;
        double sum() const;
        std::map<double, int> frequency() const;
        
    private:
        std::vector<double> numbers;
    };
} 