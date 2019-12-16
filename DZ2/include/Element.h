#pragma once

#include <queue>
#include <string>
#include <vector>

using namespace std;

// Abstract class for circuit Element
class Element {
    public:
        Element(int id);
        virtual void connectInput(Element* input, int port) = 0;
        virtual void updateOutput(double currTime) = 0;
        virtual bool getOutput();
        vector<Element*> getInput();
        int getID();
    protected:
        int id_;
        bool output_;
        vector<Element*> input_;
};