#pragma once

#include <string>
#include "Circuit.h"

using namespace std;

// Class simulating output of logical circuit
class Simulator {
    public:
        Simulator(): time_step_(0), max_time_(0), circuit_(nullptr) {};
        void loadCircuit(const string& filepath);
        void simulate(const string& filepath);
        ~Simulator();
    private:
        Circuit* circuit_;
        double time_step_;
        double max_time_;
};