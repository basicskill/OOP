#include <fstream>
#include <iostream>
#include <string>
#include "../include/Simulator.h"
#include "../include/Graph.h"

using namespace std;

void Simulator::loadCircuit(const string& filepath) {

    ifstream inFile(filepath);
    inFile >> max_time_;
    inFile.close();

    circuit_ = new Graph(filepath);
    time_step_ = circuit_->getFrequency() / 2;

}


void Simulator::simulate(const string& filepath) {

    // Open file hire

    bool newState;
    vector<bool> sondaStates(circuit_->getSondeSize());

    for (double time = time_step_; time < max_time_; time += time_step_) {
        circuit_->update(time);
        for (int i = 0; i < sondaStates.size(); ++i) {
            newState = circuit_->measure(i);
            if (newState != sondaStates[i])
                cout << sondaStates[i] << " -> " << newState
                     << ": " << time << "us" << endl;
            sondaStates[i] = newState;
        }
    }
}


Simulator::~Simulator() {
    delete circuit_;
}
