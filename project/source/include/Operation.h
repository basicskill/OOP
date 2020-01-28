#pragma once

#include <string>
#include <vector>
#include "Interfaces.h"
#include "Types.h"
#include "Logger.h"

using namespace std;

class Operation : public ITimedElement {
 public:
    Operation(string token, string outputName, double time) \
        : token_(token), output_name_(outputName), time_(time) {};
    Operation(const Operation& user) = delete;
    Operation& operator=(const Operation&) = delete;

    void setPort(int portNumber, string variable);
    void updatePort(string varName, string newValue);
    bool check();
    void notify(ID id);
    virtual string evaluate() = 0;

    inline bool done() const { return done_; };
    inline void setStart(double time) { 
        start_time_ = to_string((int) time);
    }

 protected:
    string token_, output_name_;
    string start_time_, end_time_;
    double time_;
    bool done_ = false;
    vector<string> in_ports_;
};

class Equal : public Operation {
 public:
    Equal(string token, string outputName, double time) \
        : Operation { token, outputName, time } {
        in_ports_.resize(1);
    };
 private:
    string evaluate() override;
};

class Add : public Operation {
 public:
    Add(string token, string outputName, double time) \
        : Operation { token, outputName, time } {
        in_ports_.resize(2);
    };
 private:
    string evaluate() override;
};

class Mul : public Operation {
 public:
    Mul(string token, string outputName, double time) \
        : Operation { token, outputName, time } {
        in_ports_.resize(2);
    };
 private:
    string evaluate() override;
};

class Pow : public Operation {
 public:
    Pow(string token, string outputName, double time) \
        : Operation { token, outputName, time } {
        in_ports_.resize(2);
    };
 private:
    string evaluate() override;
};
