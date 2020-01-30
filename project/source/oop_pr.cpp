#include <iostream>
#include "Compiler.h"
#include "Machine.h"
#include "Config.h"
#include "Sched.h"

using namespace std;

int main(int argc, char** argv) {
    
    if (argc != 3) { 
        cout << "Bad input args!\n";
        return 1;
    }
    string configName = argv[1];
    string inputName = argv[2];
    string imfName;

    Config::getInstance().init(configName);

    Compiler* compiler = new Compiler;
    compiler->setCompilationStrategy(
        Config::getInstance().getCompilation()
    );
    imfName = compiler->compile(inputName);

    Machine::getInstance().exec(imfName);

    return 0;
}
