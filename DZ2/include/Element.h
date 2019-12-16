#pragma once

#include <queue>
#include <string>
#include <vector>

using namespace std;

class Element {
    public:
        virtual void connectInput(Element* input, int port) = 0;
        virtual void updateOutput(double currTime) = 0;
        virtual bool getOutput() { return output_; };
        int getID() { return id_; };
    protected:
        int id_;
        bool output_;
        vector<Element*> input_;

        bool visited_;
        friend class Graph;
};