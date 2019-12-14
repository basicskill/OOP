#pragma once

#include "Element.h"

class Sonda : public Element {
    public:
        Sonda(int id);
        void updateOutput(double currTime) override;
        void connectInput(Element* input, int port) override;
        ~Sonda();
};

class NOT : public Element {
    public:
        NOT(int id);
        void updateOutput(double currTime) override;
        void connectInput(Element* input, int port) override;
        ~NOT();
};