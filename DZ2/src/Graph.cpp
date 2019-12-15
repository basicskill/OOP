#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "../include/Graph.h"
#include "../include/Element.h"
#include "../include/Gates.h"

using namespace std;

double vectorNZD(vector<double> timeStamps);

Graph::Graph(const string& filepath) {
    ifstream inFile(filepath);
    int simTime, numberOfElements;
    int elementType, id, numberOfPorts;

    inFile >> simTime;
    inFile >> numberOfElements;

    max_period_ = simTime;
    elements_.resize(numberOfElements);
    vector<double> state_changes_;

    for (int i = 0; i < numberOfElements; i++) {
        inFile >> id;
        inFile >> elementType;
        numberOfPorts = 1;

        // TODO: input all elements
        switch (elementType) {

            // Sonda
            case 0:
                elements_[i] = new Sonda(id, numberOfPorts);
                sonde_.push_back(elements_[i]);
                break;
            
            // waveSource
            case 1: {
                double frequency;
                inFile >> frequency;                
                elements_[i] = new waveSource(id, simTime, frequency);
                max_period_ = NZD(max_period_, frequency);
                break;
            }

            // arbitrarySource
            case 2: {
                state_changes_.clear();
                string line;
                getline(inFile, line);
                state_changes_.push_back(atof(line.c_str()));
                double arbFrequency = vectorNZD(state_changes_);
                elements_[i] = new arbitrarySource(id, state_changes_);
                max_period_ = NZD(max_period_, arbFrequency);
                break;
            }

            // NOT gate
            case 3: {
                elements_[i] = new NOT(id, numberOfPorts);
                break;
            }
        
            // AND gate
            case 4: {
                inFile >> numberOfElements;
                elements_[i] = new AND(id, numberOfElements);
                break;
            }
                
            // OR gate
            case 5: {
                inFile >> numberOfElements;
                elements_[i] = new OR(id, numberOfElements);
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


void Graph::update(double currTime) {
    Element* node;

    for (Element* it : elements_)
        it->visited_ = false;

    for (Element* sonda : sonde_) {
        stack<Element*> notUpdated;
        
        notUpdated.push(sonda);

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

bool Graph::measure(int sondaNumber) {
    return sonde_.at(sondaNumber)->getOutput();
}


Element* Graph::findByID(int id) {
    for (auto it : elements_)
        if (it->getID() == id)
            return it;
    // Trow exception
}

Graph::~Graph() {
    // Free every vector element
    for (int i = 0; i < elements_.size(); i++)
        delete elements_[i];
}

double vectorNZD(vector<double> timeStamps) {
    double minFreq = 0;
    for (int i = 1; i < timeStamps.size(); ++i)
        minFreq = NZD(minFreq, timeStamps[i] - timeStamps[i-1]);
}