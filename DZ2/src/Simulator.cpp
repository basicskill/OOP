#include <fstream>
#include <iostream>
#include <string>
#include "../include/Simulator.h"
#include "../include/Circuit.h"

using namespace std;


// Initialize circuit Circuit object, max_time_ and time_step_ 
// loaded from file at 'filepath'
void Simulator::loadCircuit(const string& filepath) {

    // Read only simulation time from top of the file
    ifstream inFile(filepath);
    inFile >> max_time_;
    inFile.close();

    // Default smallest time step
    time_step_ = 0.05;

    // If there already is loaded circuit, delete it
    if (circuit_ != nullptr) delete circuit_;

    // Init Circuit object
    circuit_ = new Circuit(filepath);

}

// Simulate probe state of Circuit for every time step
// Write every change of probe state to file at 'filepath'
void Simulator::simulate(const string& filepath) {

    // Create file for every probe and open that file
    // Place ofstream pointers in outFiles vector
    vector<ofstream*> outFiles;
    for (int i = 0; i < circuit_->getSondeSize(); ++i) {
        ofstream* out(new ofstream);
        out->open(filepath + "output_" + to_string(i) + ".txt");
        outFiles.push_back(out);
    }

    // Keep state of probe in previous time step
    vector<bool> sondaStates(circuit_->getSondeSize());
    bool newState;

    // Simulate circuit for each time step
    for (double time = 0; time < max_time_; time += time_step_) {

        // Update all states
        circuit_->update(time);

        // Check if output has changed for every probe 
        for (int i = 0; i < sondaStates.size(); ++i) {
            newState = circuit_->measure(i);
            if (newState != sondaStates[i])
                (*outFiles[i]) << sondaStates[i] << " -> " << newState
                     << ": " << time << "us" << endl;
            sondaStates[i] = newState;
        }

    }

    // Close all opened files
    for (int i = 0; i < outFiles.size(); ++i)
        outFiles[i]->close();

}

// Free Circuit object
Simulator::~Simulator() {
    delete circuit_;
}
