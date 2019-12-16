#include <queue>
#include <sstream>
#include <string>
#include "../include/Element.h"
#include "../include/Sources.h"

using namespace std;

/* Source methods */

// Update output_ of derived Source object
// If there currTime is equal to next state change flip output_
void Source::updateOutput(double currTime) {
    if (!state_changes_.empty() && (state_changes_.front() - currTime) < 1e-4) {
        output_ = !output_;
        state_changes_.pop();
    }
}

// Source doesn't have input ports
// Trow exception if method is called
void Source::connectInput(Element* input, int port) {
    // TODO: trow exception
    // cout << "GRESKA" << endl;
}

/* WaveSource */

// Initialize WaveSource object and calculate state changes of source
WaveSource::WaveSource(int id, const int simTime, double frequency) 
    : Source { id } {

    // Wave period is inverse to frequency
    double period = 1 / frequency;
    
    // State changes in WaveSource ocurs every half of period
    for (double time = period / 2; time <= simTime; time += period / 2) {
        state_changes_.push(time);
    }

}

/* ArbitrarySource */

// Init ArbitrarySource from string of realtive state changes
ArbitrarySource::ArbitrarySource(int id, string& relativeChanges) 
    : Source { id } {

    // Read each time stamp from 'realtiveChanges' string
    // convert it to apsolut time stamps, and push it to
    // 'state_chages_'
    stringstream ss(relativeChanges);
    double time = 0, tmp;
    for (int i = 0; i < relativeChanges.size(); ++i) {
        ss >> tmp;
        time += tmp;
        state_changes_.push(time);
    }

}