#include <fstream>
#include <iostream>
#include <string>
#include "../include/Simulator.h"
#include "../include/Graph.h"

using namespace std;

Simulator::Simulator(): 
        frequency_(0), curr_time_(0), max_time_(0) {}


void Simulator::loadCircuit(const string& filepath) {

    ifstream inFile(filepath);
    inFile >> max_time_;
    inFile.close();
    curr_time_  = 0;

    circuit_ = new Graph(filepath);
    frequency_ = circuit_->getFrequency();

}


void Simulator::simulate(const string& filepath) {
    cout << "TODO SIMULATE!" << endl;
}


Simulator::~Simulator() {
    delete circuit_;
}
