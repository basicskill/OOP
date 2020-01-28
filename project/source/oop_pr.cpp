#include <iostream>
#include "Compiler.h"
#include "Machine.h"
#include "Config.h"
#include "Sched.h"

using namespace std;

// TODO: argumenti komandne linije
int main() {
    Config::getInstance().init("../testing/test_0/config.txt");
    Compiler::getInstance().compile( \
       "../testing/test_0/test.txt");

    Machine::getInstance().exec("../testing/test_0/test.imf");

    return 0;
}
