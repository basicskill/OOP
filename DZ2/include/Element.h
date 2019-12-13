#pragma once

#include <queue>
#include <string>

using namespace std;

class Element {
    public:
        virtual bool getOutput(double currTime) = 0;
        virtual void connectInput(Element* input) = 0;
        int getID() { return id_; };
    protected:
        int id_;
};

class Sonda : public Element {
    public:
        Sonda(int id);
        bool getOutput(double currTime) override;
        void connectInput(Element* input) override;
        ~Sonda();
    private:
        bool output_;
        Element* input_;
};

class Source : public Element {
    public:
        bool getOutput(double currTime) override;
        void connectInput(Element* input) override;
    protected:
        queue<double> state_changes_;
        bool output_;
};

class waveSource : public Source {
    public:
        waveSource(int id, const int simTime, double frequency);
        ~waveSource();
};

class arbitrarySource : public Source {
    public:
        arbitrarySource(int id, const string& state_changes);
        ~arbitrarySource();
};