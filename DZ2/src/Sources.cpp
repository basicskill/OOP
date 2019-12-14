#include <queue>
#include <string>
#include <iostream>
#include "../include/Element.h"

using namespace std;

waveSource::waveSource(int id, const int simTime, double frequency) {
    id_ = id;
    output_ = false;
    for (double i = frequency / 2; i <= simTime; i += frequency / 2)
        state_changes_.push(i);
}

void Source::updateOutput(double currTime) {
    if (state_changes_.front() <= currTime) {
        output_ = !output_;
        state_changes_.pop();
    }
}

void Source::connectInput(Element* input, int port) {
    // TODO: trow exception
    cout << "GRESKA" << endl;
}

waveSource::~waveSource() {}