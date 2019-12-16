#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "../include/Circuit.h"
#include "../include/Element.h"
#include "../include/Gates.h"
#include "../include/Sources.h"

using namespace std;

// Initialize circuit elements from 'filepath'
// Connect each element from definitions in second part
// of file at 'filepath'
Circuit::Circuit(const string& filepath) {

    int simTime, numberOfElements;
    int elementType, id, numberOfPorts;

    // Open file for reading
    ifstream inFile(filepath);

    // Load simulation time and number of elements from
    // top of the file
    inFile >> simTime;
    inFile >> numberOfElements;

    // Reserve space for 'numberOfElements'
    elements_.resize(numberOfElements);

    // Initialize every element
    for (int i = 0; i < numberOfElements; i++) {

        // Load id and type
        inFile >> id;
        inFile >> elementType;
        numberOfPorts = 1;

        // Choose constructor based on 'elementType'
        switch (elementType) {

            // Probe
            case 0: {
                elements_[i] = new Probe(id, numberOfPorts);
                probes_.push_back(elements_[i]);
                break;
            }
            
            // WaveSource
            case 1: {

                // Load additional element specification
                double frequency;
                inFile >> frequency;                

                elements_[i] = new WaveSource(id, simTime, frequency);
                break;

            }

            // ArbitrarySource
            case 2: {

                // Load additional element specification
                string sequence;
                getline(inFile, sequence);

                elements_[i] = new ArbitrarySource(id, sequence);
                break;

            }

            // NOT gate
            case 3: {
                elements_[i] = new NOT(id, numberOfPorts);
                break;
            }
        
            // AND gate
            case 4: {

                // Read number of ports
                inFile >> numberOfPorts;

                elements_[i] = new AND(id, numberOfPorts);
                break;

            }
                
            // OR gate
            case 5: {

                // Read number of ports
                inFile >> numberOfPorts;

                elements_[i] = new OR(id, numberOfPorts);
                break;

            }

            // If element is not predefined, trow exception
            default: {
                // TODO: trow exception
                cout << "Unrecognized type!!" << endl;
                break;
            }
        }
    }

    // Read element connections until end of file
    int from, to, inNumber;
    while (inFile.peek() != EOF) {
        inFile >> from >> to >> inNumber;
        findByID(to)->connectInput(findByID(from), inNumber);
    }
    
    // Close input file
    inFile.close();

}

// Calculate state of each element in time defined by 'currTIme'
void Circuit::update(double currTime) {
    // TODO: Probaj drugacije parsiranje
    // TODO: Komentarisi
    Element* node;
    for (Element* it : elements_)
        it->visited_ = false;

    for (Element* probe : probes_) {
        stack<Element*> notUpdated;
        
        notUpdated.push(probe);

        while (!notUpdated.empty()) {
            node = notUpdated.top();
            if (!notUpdated.top()->visited_) {
                node->visited_ = true;
                for (Element* it : node->input_) 
                    notUpdated.push(it);
            }
            else {
                node->updateOutput(currTime);
                notUpdated.pop();
            }
        }
        
    }
}

// Return output of probe at 'probeNumber' position
// in 'probes_' list
bool Circuit::getProbeOutput(int probeNumber) {
    return probes_.at(probeNumber)->getOutput();
}

// Return pointer to Circuit element with given ID
Element* Circuit::findByID(int id) {
    for (auto it : elements_)
        if (it->getID() == id)
            return it;
    // Trow exception
}

// Free every element in vector of elements
Circuit::~Circuit() {
    for (int i = 0; i < elements_.size(); i++)
        delete elements_[i];
}