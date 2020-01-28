#pragma once

#include <fstream>
#include <string>
#include "Operation.h"

using namespace std;

class Logger {
 public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    inline void init(string file) {
        logging_file_.open(file);
    }

    inline void close() {
        logging_file_.close();
    }

    void log(string logText) {
        logging_file_ << logText << endl;
    }

 private:
    Logger() = default;
    ofstream logging_file_;
};