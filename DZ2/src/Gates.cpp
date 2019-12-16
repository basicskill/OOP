#include <iostream>
#include "../include/Gates.h"

using namespace std;

Gate::Gate(int id, int numberOfPorts) {
    id_     = id;
    output_ = false;
    input_.resize(numberOfPorts);
}

void Gate::connectInput(Element* input, int port) {
    input_.at(port) = input;
}



void Probe::updateOutput(double currTime) {
    output_ = input_.front()->getOutput();
}


void NOT::updateOutput(double currTime) {
    output_ = !(input_.at(0)->getOutput());
}


void AND::updateOutput(double currTime) {
    output_ = true;
    for (Element* it : input_) {
        output_ = output_ && it->getOutput();
    }
}

void OR::updateOutput(double currTime) {
    output_ = false;
    for (Element* it : input_) {
        output_ = output_ || it->getOutput();
    }
}