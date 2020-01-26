#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "Interfaces.h"
#include "Types.h"
#include "Operation.h"

#include <iostream>

bool digitString(const string s){
  return s.find_first_not_of( "0123456789" ) == string::npos;
}

bool Operation::check() {
    for (string val : in_ports_)
        if (!digitString(val))
            std::cout << val << endl; // Check with memory
}

void Operation::notify(ID id) {
    done_ = true;
    // Zamena t* brojem
}

void Add::evaluate() {
    std::stringstream ss;
    double val1, val2, solution;
    ss.str(in_ports_[0]);
    ss >> val1;
    ss.str(in_ports_[1]);
    ss >> val2;
    solution = val1 + val2;
    std::cout << "SWAP: " << token_ << " with " << solution;
}

void Mul::evaluate() {
    std::stringstream ss;
    double val1, val2, solution;
    ss.str(in_ports_[0]);
    ss >> val1;
    ss.str(in_ports_[1]);
    ss >> val2;
    solution = val1 * val2;
    std::cout << "SWAP: " << token_ << " with " << solution;
}

void Pow::evaluate() {
    std::stringstream ss;
    double val1, val2, solution;
    ss.str(in_ports_[0]);
    ss >> val1;
    ss.str(in_ports_[1]);
    ss >> val2;
    solution = std::pow(val1, val2);
    std::cout << "SWAP: " << token_ << " with " << solution;
}

void Equal::evaluate() {
    std::stringstream ss;
    double val;
    ss.str(in_ports_[0]);
    ss >> val;
}