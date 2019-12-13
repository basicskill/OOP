#include <queue>
#include <string>
#include <iostream>
#include "../include/Element.h"

using namespace std;

waveSource::waveSource(int id, const int simTime, double frequency){
    id_ = id;
    output_ = false;
    for (double i = 0; i <= simTime; i += frequency / 2)
        state_changes_.push(i);
}

bool Source::getOutput(double currTime) {
    if (state_changes_.front() <= currTime) {
        output_ = !output_;
        state_changes_.pop();
    }
    return output_;
}

void Source::connectInput(Element* input) {
    // TODO: trow exception
    cout << "GRESKA" << endl;
}

waveSource::~waveSource() {}