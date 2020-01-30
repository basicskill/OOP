#pragma once

#include <string>
#include <vector>

using namespace std;

class Config {
 public:
    static Config& getInstance() {
        static Config instance;
        return instance;
    }
    Config(const Config& user) = delete;
    Config& operator=(const Config&) = delete;

    void init(string filename);
    double getValue(string name);
    string getCompilation() { return compilation_; };
 private:
    Config() = default;
    vector<string> names_;
    vector<double> values_;
    string compilation_;
};