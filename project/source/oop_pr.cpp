#include <iostream>
#include <string>
#include "Compiler.h"
#include "Machine.h"
#include "Config.h"
#include "Logger.h"
#include "Sched.h"

using namespace std;

int main(int argc, char** argv) {
    
    // Check for valid input
    if (argc != 3) { 
        cout << "Bad input args!\n";
        return 1;
    }

    string configName = argv[1];
    string inputName = argv[2];
    string logName = inputName.substr(0, inputName.length()-4) + ".log";
    string imfName;

    // Read configuration file
    Config::getInstance().init(configName);

    // Init log file
    Logger::getInstance().init(logName);

    // Compiler init
    Compiler* compiler = new Compiler;
    compiler->setCompilationStrategy(
        Config::getInstance().getCompilation()
    );
    
    // Compile input
    imfName = compiler->compile(inputName);

    // Execute compiled file
    Machine::getInstance().exec(imfName);

    Logger::getInstance().close();

    return 0;
}
