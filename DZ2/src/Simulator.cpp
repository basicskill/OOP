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
    time_step_ = circuit_->getPeriod() / 2;

}


void Simulator::simulate(const string& filepath) {

    vector<ofstream*> outFiles;
    for (int i = 0; i < circuit_->getSondeSize(); ++i) {
        ofstream* out(new ofstream);
        out->open(filepath + "output_" + to_string(i) + ".txt");
        outFiles.push_back(out);
    }

    bool newState;
    vector<bool> sondaStates(circuit_->getSondeSize());



    for (double time = 0; time < max_time_; time += time_step_) {
        circuit_->update(time);
        for (int i = 0; i < sondaStates.size(); ++i) {
            newState = circuit_->measure(i);
            if (newState != sondaStates[i])
                (*outFiles[i]) << sondaStates[i] << " -> " << newState
                     << ": " << time << "us" << endl;
            sondaStates[i] = newState;
        }
    }
    for (int i = 0; i < outFiles.size(); ++i)
        outFiles[i]->close();
}


Simulator::~Simulator() {
    delete circuit_;
}
