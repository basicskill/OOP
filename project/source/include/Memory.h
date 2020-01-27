#pragma once

#include <exception>
#include <vector>
#include <string>

using namespace std;

class Memory {
 public:
    static Memory& getInstance();
    Memory(const Memory& user) = delete;
    Memory& operator=(const Memory&) = delete;


    void set(string varName, string val);
    string get(string varName);

 private:
    // Treba da procita Nw
    Memory() = default;

    int nw_ = 1; // !!
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
