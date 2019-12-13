#include "../include/Element.h"

Sonda::Sonda(int id) {
    id_     = id;
    output_ = false;
    input_  = nullptr;
}

void Sonda::connectInput(Element* input) {
    input_ = input;
}

bool Sonda::getOutput(double currTime) {
    return input_->getOutput(currTime);
}

Sonda::~Sonda() {}

