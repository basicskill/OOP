#pragma once

#include <vector>
#include <string>

using namespace std;

class Memory {
 public:
    static Memory& getInstance();
    Memory(const Memory& user) = delete;
    Memory& operator=(const Memory&) = delete;

    void set(string varName, double val);
    double get(string varName);

 private:
    // Treba da procita Nw
    Memory() = default;

    int nw_ = 1; // !!
    vector<string> variables_;
    vector<double> values_;

};