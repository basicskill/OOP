#include <queue>
#include <string>
#include <iostream>
#include "../include/Element.h"

using namespace std;

waveSource::waveSource(int id, const int simTime, double frequency) {
    id_ = id;
    output_ = false;
    double period = 1 / frequency;
    for (double time = period / 2; time <= simTime; time += period / 2) {
        state_changes_.push(time);
    }
}

void Source::updateOutput(double currTime) {
    if (!state_changes_.empty() && (state_changes_.front() - currTime) < 1e-4) {
        output_ = !output_;
        state_changes_.pop();
    }
}

void Source::connectInput(Element* input, int port) {
    // TODO: trow exception
    cout << "GRESKA" << endl;
}

arbitrarySource::arbitrarySource(int id, vector<double> relativeChanges){
    id_ = id;
    output_ = false;
    double time = 0;
    for (int i = 0; i < relativeChanges.size(); ++i) {
        time += relativeChanges[i];
        state_changes_.push(time);
    }
}

double NZD(double a1, double b1) {
    int a = a1 * 1000;
    int b = b1 * 1000;

    if (a == 0) 
        return b;
    else {
        while (b > 0)
            if (a > b) a = a - b;
            else b = b - a;
    }
    return ((double) a) / 1000;
}