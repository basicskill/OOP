#pragma once

#include <exception>
#include <vector>
#include <string>
#include "Config.h"

using namespace std;

class Memory {
 public:
    static Memory& getInstance();
    Memory(const Memory& user) = delete;
    Memory& operator=(const Memory&) = delete;

    void set(string varName, string val);
    string get(string varName);
    inline bool ready() const { return (in_process_ < nw_); };
    inline void reserve() { if (ready()) ++in_process_; };


    void save(string filename);

 private:
    Memory() { nw_ = Config::getInstance().getValue("Nw"); };

    int nw_, in_process_ = 0;
    vector<string> variables_;
    vector<string> values_;

};

class VarNotAvalibleException : public exception {
    public:
    VarNotAvalibleException(const char* msg) : exception(), msg_(msg) {};
    const char * what () const throw () {
        return msg_;
    }
    private:
        const char* msg_;
};
