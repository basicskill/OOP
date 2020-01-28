#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Memory.h"

using namespace std;

Memory& Memory::getInstance() {
    static Memory instance;
    return instance;
}

void Memory::set(string varName, string val) {
    for (int i = 0; i < variables_.size(); ++i)
        if (variables_[i] == varName) {
            values_[i] = val;
            return;
        }

    variables_.push_back(varName);
    values_.push_back(val);
}

string Memory::get(string varName) {
    for (int i = 0; i < variables_.size(); ++i)
        if ( variables_[i] == varName)
            return values_[i];
    throw VarNotAvalibleException("Variable not in memory");
}

void Memory::save(string filename) {
    string outpath;
    outpath = filename.substr(0, filename.length()-4) + ".mem";
    ofstream outFile(outpath);

    for (int i = 0; i < variables_.size(); ++i)
        outFile << variables_[i] << " = " 
                << atof(values_[i].c_str()) << endl;
}