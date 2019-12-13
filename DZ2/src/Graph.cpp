#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/Graph.h"

using namespace std;

Graph::Graph(const string& filepath) {
    ifstream inFile (filepath);
    int maxTime;
    inFile >> maxTime;
    inFile >> numb_of_elements_;

    int elementType, id;
    string info;
    elements_.reserve(numb_of_elements_);
    for (int i = 0; i < numb_of_elements_; i++) {
        inFile >> id;
        inFile >> elementType;
        // TODO: input all elements
        switch (elementType) {
            case 0:
                cout << "Type: " << elementType << endl;
                break;
            case 1:
                cout << "Type: " << elementType << endl;
                break;
        
            default:
                // TODO: trow exception
                cout << "Unrecognized type!!" << endl;
                break;
        }
        getline(inFile, info, '\n');
        cout << info << endl;
        elements_[i] = id; // !!!
    }
}

Graph::~Graph() {
    // Free every vector element;
}