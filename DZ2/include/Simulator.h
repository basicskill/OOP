#pragma once

#include <string>
#include "Circuit.h"

using namespace std;

// Class simulating output of logical circuit
class Simulator {
    public:
        Simulator();
        void loadCircuit(const string& filepath);
        void simulate(const string& filepath);
        ~Simulator();
    private:
        Circuit* circuit_;
        double time_step_;
        double max_time_;
};