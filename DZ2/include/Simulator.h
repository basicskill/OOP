#pragma once

#include <string>
#include "Graph.h"

using namespace std;

class Simulator {
    public:
        Simulator(): time_step_(0), max_time_(0) {};
        void loadCircuit(const string& filepath);
        void simulate(const string& filepath);
        ~Simulator();
    private:
        Graph* circuit_;
        double time_step_;
        double max_time_;
};