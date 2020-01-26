#include <iostream>
#include <string>
#include <vector>
#include "Memory.h"

using namespace std;

Memory& Memory::getInstance() {
    static Memory instance;
    return instance;
}

void Memory::set(string varName, double val) {
    for (int i = 0; i < variables_.size(); ++i)
        if ( variables_[i] == varName) {
            values_[i] = val;
            return;
        }

    variables_.push_back(varName);
    values_.push_back(val);
}

double Memory::get(string varName) {
    for (int i = 0; i < variables_.size(); ++i)
        if ( variables_[i] == varName)
            return values_[i];
    cout << "MEMORY EXCEPTION";
}