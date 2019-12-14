#include "../include/Element.h"

Sonda::Sonda(int id) {
    id_     = id;
    output_ = false;
    last_state_ = false;
    input_.clear();
}

void Sonda::connectInput(Element* input) {
    if (!input_.empty())
        input_.clear();
    input_.push_back(input);
}

void Sonda::updateOutput(double currTime) {
    last_state_ = output_;
    output_ = input_.front()->getOutput();
}

Sonda::~Sonda() {}