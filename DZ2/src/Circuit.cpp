#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include "../include/Circuit.h"
#include "../include/Element.h"
#include "../include/CircuitExceptions.h"
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

        // Choose constructor based on 'elementType'
        switch (elementType) {

            // Probe
            case 0: {
                elements_[i] = new Probe(id);
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
                elements_[i] = new NOT(id);
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

            // If element is not predefined, throw exception
            default: {
                throw CircuitException("Element type doesn't exist!");
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
// State is calculated with postorder tree traversal
void Circuit::update(double currTime) {

    // Local pointers for tree traversal
    Element* node; 
    Element* lastVisited;

    // Stack used to avoid recursion in traversal
    stack<Element*> notUpdated;

    // For each probe update its output
    for (Element* probe : probes_) {

        // Last visited doesn't exist at the begining
        lastVisited = nullptr;
        
        // Probe is pushed to stack
        notUpdated.push(probe);

        // Traversal is working until it empties the stack
        while (!notUpdated.empty()) {

            // Set node to top of the stack
            node = notUpdated.top();

            // If all node's daughters are already updated, update node
            // All daughters are updated when the last visited node is 
            // first node in current node's input_ vector
            if ((node->getInput().empty()) || (node->getInput().front() == lastVisited)) {
                node->updateOutput(currTime);
                notUpdated.pop();
            }
            // If daughters aren't updated, add them to notUpdated stack
            else
                for (Element* it : node->getInput()) 
                    notUpdated.push(it);

            // Set lastVisited to current node
            lastVisited = node;
        }
        
    }
}

// Return output of probe at 'probeNumber' position
// in 'probes_' list
bool Circuit::getProbeOutput(int probeNumber) {
    return probes_.at(probeNumber)->getOutput();
}
vector<Element*> Circuit::getProbes() {
    return probes_;
}

// Return pointer to Circuit element with given ID
Element* Circuit::findByID(int id) {
    for (auto it : elements_)
        if (it->getID() == id)
            return it;
    throw CircuitException("ID doesn't exist");
}

// Free every element in vector of elements
Circuit::~Circuit() {
    for (int i = 0; i < elements_.size(); i++)
        delete elements_[i];
}