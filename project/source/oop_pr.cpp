#include <iostream>
#include "Compiler.h"
#include "Sched.h"

using namespace std;

int main() {
    cout << "GOTOVO\n";
      
    Compiler::getInstance().compile( \
       "../Build/test_1/test.txt");

    cout << Scheduler::Instance()->getCurTime();

    return 0;
}
