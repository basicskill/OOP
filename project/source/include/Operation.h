#pragma once

#include <string>
#include <vector>
#include "Interfaces.h"
#include "Types.h"

using namespace std;

class Operation : public ITimedElement {
 public:
    Operation(string token, double time) : token_(token), time_(time) {};
    // Ubi one ostale

    bool check();
    void notify(ID id);
    virtual void evaluate() = 0;

 protected:
    string token_;
    double time_;
    bool done_ = false;
    vector<string> in_ports_;
};


class Add : public Operation {
 public:
    Add(string token, double time) : Operation { token, time } {
        in_ports_.resize(2);
    };
 private:
    void evaluate() override;
};

class Mul : public Operation {
 public:
    Mul(string token, double time) : Operation { token, time } {
        in_ports_.resize(2);
    };
 private:
    void evaluate() override;
};

class Pow : public Operation {
 public:
    Pow(string token, double time) : Operation { token, time } {
        in_ports_.resize(2);
    };
 private:
    void evaluate() override;
};

class Equal : public Operation {
 public:
    Equal(string token, double time) : Operation { token, time } {
        in_ports_.resize(1);
    };
 private:
    void evaluate() override;
};