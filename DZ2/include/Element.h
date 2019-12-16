#pragma once

#include <queue>
#include <string>
#include <vector>

using namespace std;

// Abstract class for circuit Element
class Element {
    public:
        Element(int id) : id_(id), output_(false) {};
        virtual void connectInput(Element* input, int port) = 0;
        virtual void updateOutput(double currTime) = 0;
        virtual bool getOutput() { return output_; };
        int getID() { return id_; };
    protected:
        int id_;
        bool output_;
        vector<Element*> input_;

        bool visited_;
        friend class Circuit;
};