#pragma once

#include <string>

using namespace std;

class Simulator {
    public:
        Simulator();
        void loadCircuit(const string& filepath);
        void simulate(const string& filepath);
        ~Simulator();
    private:
        // Graph circuit_;
        double freq_;
        double curr_time, max_time_;
};
