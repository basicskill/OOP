#pragma once

#include <string>
#include <iostream>
#include <exception>

using namespace std;

class CompilationStrategy {
 public:
    virtual void compile(string filepath) = 0;
 protected:
    string inf2post(string infix);
    string readNext(string input, int* it);
    bool checkOperation(string c);
    bool checkOperation(char c);
};

class SimpleCompilationStrategy : public CompilationStrategy{
 public:
    virtual void compile(string filepath) override;
};

class AdvancedCompilationStrategy : public CompilationStrategy{
 public:
    virtual void compile(string filepath) override {};
};


class Compiler {
 public:
    Compiler() = default;

    void compile(string filepath) const { compilation_strategy_->compile(filepath); };
    void setCompilationStrategy(string strategyName) {
        delete compilation_strategy_;
        if (strategyName == "simple")
            compilation_strategy_ = new SimpleCompilationStrategy;
        else if (strategyName == "advanced")
            compilation_strategy_ = new AdvancedCompilationStrategy;
    };

 private:
    CompilationStrategy* compilation_strategy_ = nullptr;
};

class UnknownCompilationStrategyException : public exception {
    public:
    UnknownCompilationStrategyException(const char* msg) : exception(), msg_(msg) {};
    const char * what () const throw () {
        return msg_;
    }
    private:
        const char* msg_;
};