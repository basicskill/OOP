#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Interfaces.h"
#include "Types.h"
#include "Operation.h"
#include "Memory.h"
#include "Machine.h"


bool digitString(const string s){
  return s.find_first_not_of( "0123456789" ) == string::npos;
}

void Operation::setPort(int portNumber, string variable) {
    in_ports_.at(portNumber) = variable;
}

void Operation::updatePort(string varName, string newValue) {
    for (int i = 0; i < in_ports_.size(); ++i)
        if (in_ports_[i] == varName) in_ports_[i] = newValue;
}

bool Operation::check() {
    try {
        for (string val : in_ports_)
            if (!digitString(val))
                return false;
    }
    catch(VarNotAvalibleException& e) {
        return false;
    }
    
    return true;

}

void Operation::notify(ID id) {
    done_ = true;
    string result = evaluate();
    // Mesto za upisivanje
    // cout << token_;

    Machine::getInstance().upadeState(output_name_, result);
}

string Equal::evaluate() {
    Memory::getInstance().set(output_name_, in_ports_[0]);
}

string Add::evaluate() {
    double val1, val2, solution;
    val1 = atof(in_ports_[0].c_str());
    val2 = atof(in_ports_[1].c_str());
    solution = val1 + val2;
    return to_string(solution);
}

string Mul::evaluate() {
    double val1, val2, solution;
    val1 = atof(in_ports_[0].c_str());
    val2 = atof(in_ports_[1].c_str());
    solution = val1 * val2;
    return to_string(solution);
}

string Pow::evaluate() {
    double val1, val2, solution;
    val1 = atof(in_ports_[0].c_str());
    val2 = atof(in_ports_[1].c_str());
    solution = std::pow(val1, val2);
    return to_string(solution);
}