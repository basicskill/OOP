#pragma once

#include <queue>
#include <string>
#include <vector>
#include "Element.h"

class Source : public Element {
    public:
        void updateOutput(double currTime) override;
        void connectInput(Element* input, int port) override;
    protected:
        queue<double> state_changes_;
};

class waveSource : public Source {
    public:
        waveSource(int id, const int simTime, double frequency);
        ~waveSource();
};

class arbitrarySource : public Source {
    public:
        arbitrarySource(int id, string& relativeChanges);
        ~arbitrarySource();
    private:
        double frequency_;
};