#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "../include/Graph.h"
#include "../include/Element.h"
#include "../include/Gates.h"

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
                sonde_.push_back(elements_[i]);
                break;
            
            // waveSource
            case 1:
                double frequency;
                inFile >> frequency;                
                elements_[i] = new waveSource(id, simTime, frequency);
                if (frequency < min_frequency_)
                    min_frequency_ = frequency;
                break;

            // arbitrarySource
            case 2:
                cout << "FALI!";
                break;

            // NOT gate
            case 3:
                elements_[i] = new NOT(id);
                break;
        
            // AND gate
            case 4:
                // elements_[i] = new AND(id);
                break;
                
            // OR gate
            case 5:
                // elements_[i] = new OR(id);
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