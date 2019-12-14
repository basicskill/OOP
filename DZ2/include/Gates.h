#pragma once

#include "Element.h"

class Gate : public Element{
    public:
        Gate(int id, int numberOfPorts);
        virtual void connectInput(Element* input, int port);
        virtual void updateOutput(double currTime) = 0;
};

class Sonda : public Gate {
    public:
        Sonda(int id, int numberOfPorts) : Gate { id, numberOfPorts } {};
        void updateOutput(double currTime) override;
        ~Sonda();
};

class NOT : public Gate {
    public:
        NOT(int id, int numberOfPorts) : Gate { id, numberOfPorts } {};
        void updateOutput(double currTime) override;
        ~NOT();
};

class AND : public Gate {
    public:
        AND(int id, int numberOfPorts) : Gate { id, numberOfPorts } {};
        void updateOutput(double currTime) override;
        ~AND();
};

class OR : public Gate {
    public:
        OR(int id, int numberOfPorts) : Gate { id, numberOfPorts } {};
        void updateOutput(double currTime) override;
        ~OR();
};