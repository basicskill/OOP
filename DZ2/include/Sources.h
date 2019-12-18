#pragma once

#include <queue>
#include <string>
#include <vector>
#include "Element.h"

// Abstract class for Source Element
class Source : public Element {
    public:
        Source(int id) : Element { id } {};
        void updateOutput(double currTime) override;
        void connectInput(Element* input, int port) override;
    protected:
        queue<double> state_changes_;
};

// Derived class of Source with wave output defined with frequency
// given to constructior
class WaveSource : public Source {
    public:
        WaveSource(int id, const int simTime, double frequency);
        ~WaveSource() {};
};

// Derived class of Source with output that changes defined by
// string of relative output changes given to constructor
class ArbitrarySource : public Source {
    public:
        ArbitrarySource(int id, string& relativeChanges);
        ~ArbitrarySource() {};
    private:
        double frequency_;
};