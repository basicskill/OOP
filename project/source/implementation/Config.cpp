#include <string>
#include <fstream>
#include "Config.h"

using namespace std;

void Config::init(string filename) {
    ifstream inFile(filename);
    string name, equal;
    double value;

    while (inFile.peek() != EOF) {
        inFile >> name;
        inFile >> equal;
        if (name != "compilation") {
            inFile >> value;
            names_.push_back(name);
            values_.push_back(value);
        } else inFile >> compilation_;
    }
}

double Config::getValue(string name) {
    for (int i = 0; i < names_.size(); ++i)
        if (names_[i] == name) return values_[i];
    // throw Exception;
}