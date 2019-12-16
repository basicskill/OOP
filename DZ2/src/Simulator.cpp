#include <fstream>
#include <string>
#include "../include/Circuit.h"
#include "../include/Simulator.h"

using namespace std;

// Init Simulator parameters
Simulator::Simulator(): time_step_(0), max_time_(0), circuit_(nullptr) {};

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
    for (Element* probe : circuit_->getProbes()) {
        ofstream* out(new ofstream);
        out->open(filepath.substr(0, filepath.size()-4) + "_" 
                    + to_string(probe->getID()) + ".txt");
        outFiles.push_back(out);
    }

    // Keep state of probe in previous time step
    vector<bool> probeStates(circuit_->getProbes().size());
    bool newState;

    // Simulate circuit for each time step
    for (double time = 0; time < max_time_; time += time_step_) {

        // Update all states
        circuit_->update(time);

        // Check if output has changed for every probe 
        for (int i = 0; i < probeStates.size(); ++i) {
            newState = circuit_->getProbeOutput(i);
            if (newState != probeStates[i])
                (*outFiles[i]) << probeStates[i] << " -> " << newState
                     << ": " << time << "us" << endl;
            probeStates[i] = newState;
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
