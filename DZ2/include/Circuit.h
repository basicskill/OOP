#pragma once

#include <string>
#include <vector>
#include "../include/Element.h"

using namespace std;

// Class interpreting behaviour of logical circuit
class Circuit {
    public:
        Circuit(const string& filepath);
        Element* findByID(int id);
        void update(double currTime);

        int getProbesSize() { return probes_.size(); };
        bool getProbeOutput(int probeNumber);

        ~Circuit();

    private:
        vector<Element*> elements_;
        vector<Element*> probes_;
};