#pragma once

#include "Element.h"

// Derived class of Element for gate elements
// Gate is element that changes its output based on its inputs
class Gate : public Element {
    public:
        Gate(int id, int = 1);
        virtual void connectInput(Element* input, int port);
        virtual void updateOutput(double currTime) = 0;
};

// Derived class of Gate for Probe
// Probe is element that has output equal to its input
class Probe : public Gate {
    public:
        Probe(int id);
        void updateOutput(double currTime) override;
        ~Probe();
};

// Derived class of Gate for NOT gate
class NOT : public Gate {
    public:
        NOT(int id);
        void updateOutput(double currTime) override;
        ~NOT();
};

// Derived class of Gate for AND gate
class AND : public Gate {
    public:
        AND(int id, int numberOfPorts);
        void updateOutput(double currTime) override;
        ~AND();
};

// Derived class of Gate for OR gate
class OR : public Gate {
    public:
        OR(int id, int numberOfPorts);
        void updateOutput(double currTime) override;
        ~OR();
};