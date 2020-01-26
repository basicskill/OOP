#include <fstream>
#include <iostream>
#include <string>
#include "Machine.h"

using namespace std;


void Machine::exec(string file) {
    ifstream inFile(file);
    string line;
    string op, dest, var1, var2;
    while (inFile.peek() != EOF) {
        inFile >> line ;
        inFile >> op ;
        inFile >> dest;
        inFile >> var1;
        if (op != "=") inFile >> var2;
        else var2 = "";
        cout << dest << " <- " 
             << var1 << op << var2 << endl;
    }
    
}