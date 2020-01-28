#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Machine.h"
#include "Event.h"
#include "Sched.h"

using namespace std;

Machine& Machine::getInstance() {
    static Machine instance;
    return instance;
}

void Machine::init(string file) {
    ifstream inFile(file);
    stringstream ss; 
    string line, token;
    string op, dest, var1, var2;
    Operation* tmp;

    inFile >> token;
    while (inFile.peek() != EOF) {
        inFile >> op;
        inFile >> dest;
        inFile >> var1;
        if (op == "=") {
            tmp = new Equal(token, dest, 1); // VREME
            tmp->setPort(0, var1);
        }
        else {
            inFile >> var2;
            switch (op[0]) {
            case '+':
                tmp = new Add(token, dest, 1);
                break;
            case '*':
                tmp = new Add(token, dest, 1);
                break;
            case '^':
                tmp = new Add(token, dest, 1);
                break;
            default:
                break;
            }
            tmp->setPort(0, var1);
            tmp->setPort(1, var2);
        }
        waiting_.push_back(tmp);
        inFile >> token;
    }
}

void Machine::scheduale() {
    int i = 0;
    while (i < waiting_.size()) {
        if (waiting_[i]->check()) {
            Event::create(waiting_[i], 1); // TODO: VREME
            waiting_[i]->setStart(Scheduler::Instance()->getCurTime());
            executing_.push_back(waiting_[i]);
            waiting_.erase(waiting_.begin() + i);
        } else ++i;
    }
    // cout << "###########\n";
}

void Machine::exec(string file) {
    init(file);
    cout << "Broj elemenata: " << waiting_.size() << endl;
    Logger::getInstance().init("fajl.log"); // HARCODE!

    scheduale();
    while (!waiting_.empty()) {
        // scheduale();
        Scheduler::Instance()->processNow();    
    }

    Logger::getInstance().close();
}

void Machine::upadeState(string name, string value) {

    for (int i = 0; i < waiting_.size(); ++i)
        waiting_[i]->updatePort(name, value);
    
    int i = 0;
    while (i < executing_.size())
        if (executing_[i]->done()) {
            delete executing_[i];
            executing_.erase(executing_.begin() + i);
        } else ++i;

    scheduale();
}