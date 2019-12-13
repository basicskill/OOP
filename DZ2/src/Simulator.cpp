#include <fstream>
#include <iostream>
#include <string>
#include "../include/Simulator.h"
#include "../include/Graph.h"

using namespace std;

Simulator::Simulator(): 
        freq_(0), curr_time_(0), max_time_(0) {}


void Simulator::loadCircuit(const string& filepath) {
    circuit_ = new Graph(filepath);
}


void Simulator::simulate(const string& filepath) {
    cout << "TODO SIMULATE!" << endl;
}


Simulator::~Simulator() {
    delete circuit_;
}
