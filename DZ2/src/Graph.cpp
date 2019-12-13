#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/Graph.h"
#include "../include/Element.h"

using namespace std;

Graph::Graph(const string& filepath) {
    ifstream inFile(filepath);
    int simTime, numberOfElements;
    int elementType, id;

    inFile >> simTime;
    inFile >> numberOfElements;

    min_frequency_ = simTime;

    elements_.resize(numberOfElements);
    for (int i = 0; i < numberOfElements; i++) {
        inFile >> id;
        inFile >> elementType;

        // TODO: input all elements
        switch (elementType) {

            // Sonda
            case 0:
                elements_[i] = new Sonda(id);
                sonde_.push_back(i);
                break;
            
            // waveSource
            case 1:
                double frequency;
                inFile >> frequency;                
                elements_[i] = new waveSource(id, simTime, frequency);
                if (frequency < min_frequency_)
                    min_frequency_ = frequency;
                break;
        
            default:
                // TODO: trow exception
                cout << "Unrecognized type!!" << endl;
                break;

        }
    }

    int from, to, inNumber;
    while (inFile.peek() != EOF) {
        inFile >> from >> to >> inNumber;
        cout << from << " " << to << endl;
        findByID(to)->connectInput(findByID(from));
    }
    
    inFile.close();
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