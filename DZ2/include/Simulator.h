#pragma once

#include <string>
#include "Graph.h"

using namespace std;

class Simulator {
    public:
        Simulator();
        void loadCircuit(const string& filepath);
        void simulate(const string& filepath);
        ~Simulator();
    private:
        Graph* circuit_;
        double freq_;
        double curr_time_, max_time_;
};
