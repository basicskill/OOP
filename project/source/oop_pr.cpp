#include <iostream>
#include "Compiler.h"
#include "Machine.h"
#include "Sched.h"

using namespace std;

int main() {
    Compiler::getInstance().compile( \
       "../testing/test_1/test.txt");

    Machine::getInstance().exec("../testing/test_1/test.imf");

    return 0;
}
