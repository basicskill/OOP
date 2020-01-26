#pragma once

#include <string>
#include <iostream>

using namespace std;

// TODO: strategije!
class Compiler{
    public:

        Compiler(const Compiler& user) = delete;
        Compiler& operator=(const Compiler&) = delete;

        static Compiler& getInstance();
        void loadConfig(string filepath);
        void compile(string filepath);

    private:
        Compiler() { cout << "napravio kompajler\n"; }
        string inf2post(string infix);
        string readNext(string input, int* it);
        bool checkOperation(char c);
};