#include <iostream>
#include "Compiler.h"
#include "Event.h"

using namespace std;

int main() {
    Compiler::getInstance().compile( \
        "../Build/test_1/test.txt");
    return 0;
}