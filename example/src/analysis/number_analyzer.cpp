#include "number_analyzer.hpp"
#include <numeric>
#include <map>

namespace analysis {
    void NumberAnalyzer::addNumber(double num) {
        numbers.push_back(num);
    }
    
    double NumberAnalyzer::average() const {
        if (numbers.empty()) return 0.0;
        return sum() / numbers.size();
    }

    double NumberAnalyzer::sum() const {
        return std::accumulate(numbers.begin(), numbers.end(), 0.0);
    }

    std::map<double, int> NumberAnalyzer::frequency() const {
        std::map<double, int> freq;
        for (const auto& num : numbers) {
            freq[num]++;
        }
        return freq;
    }
} 