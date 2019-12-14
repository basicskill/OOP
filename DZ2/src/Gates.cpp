#include <iostream>
#include "../include/Gates.h"

using namespace std;

Sonda::Sonda(int id) {
    id_     = id;
    output_ = false;
    input_.clear();
}

void Sonda::connectInput(Element* input, int port) {
    if (port != 0) cout << "EXCEPTION";
    if (!input_.empty())
        input_.clear();
    input_.push_back(input);
}

void Sonda::updateOutput(double currTime) {
    output_ = input_.front()->getOutput();
}

Sonda::~Sonda() {}

NOT::NOT(int id) {
    id_     = id;
    output_ = false;
    input_.clear();
}

void NOT::connectInput(Element* input, int port) {
    if (port != 0) cout << "EXCEPTION";
    if (!input_.empty())
        input_.clear();
    input_.push_back(input);
}

void NOT::updateOutput(double currTime) {
    output_ = !(input_.at(0)->getOutput());
}