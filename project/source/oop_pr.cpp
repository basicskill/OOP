#include <iostream>
#include "Compiler.h"
#include "Machine.h"
#include "Config.h"
#include "Sched.h"

using namespace std;

// TODO: argumenti komandne linije
int main() {
    Config::getInstance().init("../testing/test_1/config.txt");
    Compiler::getInstance().compile( \
       "../testing/test_1/test.txt");

    Machine::getInstance().exec("../testing/test_1/test.imf");

    return 0;
}
