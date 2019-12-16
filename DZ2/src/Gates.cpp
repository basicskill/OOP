#include <iostream>
#include "../include/Gates.h"

using namespace std;

// Init id, output and number of ports
Gate::Gate(int id, int numberOfPorts) : Element { id } {
    input_.resize(numberOfPorts);
}

// Connect 'input' Element to 'input_' of Gate
void Gate::connectInput(Element* input, int port) {
    input_.at(port) = input;
}

// Update Probe output to its input
void Probe::updateOutput(double currTime) {
    output_ = input_.front()->getOutput();
}

// Update NOT Gate's output to inverse of it's input
void NOT::updateOutput(double currTime) {
    output_ = !(input_.at(0)->getOutput());
}

// Update AND Gate's output to conjuction of it's input
void AND::updateOutput(double currTime) {
    output_ = true;
    for (Element* it : input_) {
        output_ = output_ && it->getOutput();
    }
}

// Update AND Gate's output to disjunction of it's input
void OR::updateOutput(double currTime) {
    output_ = false;
    for (Element* it : input_) {
        output_ = output_ || it->getOutput();
    }
}