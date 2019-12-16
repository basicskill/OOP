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


Circuit::Circuit(const string& filepath) {
    ifstream inFile(filepath);
    int simTime, numberOfElements;
    int elementType, id, numberOfPorts;

    inFile >> simTime;
    inFile >> numberOfElements;

    max_period_ = simTime;
    elements_.resize(numberOfElements);
    vector<double> stateChanges;

    for (int i = 0; i < numberOfElements; i++) {
        inFile >> id;
        inFile >> elementType;
        numberOfPorts = 1;

        // TODO: input all elements
        switch (elementType) {

            // Probe
            case 0:
                elements_[i] = new Probe(id, numberOfPorts);
                probes_.push_back(elements_[i]);
                break;
            
            // waveSource
            case 1: {
                double frequency;
                inFile >> frequency;                
                elements_[i] = new waveSource(id, simTime, frequency);
                break;
            }

            // arbitrarySource
            case 2: {
                string sequence;
                stateChanges.clear();
                getline(inFile, sequence);

                elements_[i] = new arbitrarySource(id, sequence);
                break;
            }

            // NOT gate
            case 3: {
                elements_[i] = new NOT(id, numberOfPorts);
                break;
            }
        
            // AND gate
            case 4: {
                inFile >> numberOfPorts;
                elements_[i] = new AND(id, numberOfPorts);
                break;
            }
                
            // OR gate
            case 5: {
                inFile >> numberOfPorts;
                elements_[i] = new OR(id, numberOfPorts);
                break;
            }

            default: {
                // TODO: trow exception
                cout << "Unrecognized type!!" << endl;
                break;
            }
        }
    }


    int from, to, inNumber;
    while (inFile.peek() != EOF) {
        inFile >> from >> to >> inNumber;
        findByID(to)->connectInput(findByID(from), inNumber);
    }
    
    inFile.close();
}


void Circuit::update(double currTime) {
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

bool Circuit::measure(int probeNumber) {
    return probes_.at(probeNumber)->getOutput();
}


Element* Circuit::findByID(int id) {
    for (auto it : elements_)
        if (it->getID() == id)
            return it;
    // Trow exception
}

Circuit::~Circuit() {
    // Free every vector element
    for (int i = 0; i < elements_.size(); i++)
        delete elements_[i];
}