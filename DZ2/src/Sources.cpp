#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include "../include/Element.h"
#include "../include/Sources.h"

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

arbitrarySource::arbitrarySource(int id, string& relativeChanges){
    id_ = id;
    output_ = false;
    double time = 0, tmp;

    stringstream ss(relativeChanges);
    for (int i = 0; i < relativeChanges.size(); ++i) {
        ss >> tmp;
        time += tmp;
        state_changes_.push(time);
    }
}