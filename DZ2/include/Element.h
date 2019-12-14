#pragma once

#include <queue>
#include <string>
#include <vector>

using namespace std;

class Element {
    public:
        virtual void connectInput(Element* input) = 0;
        virtual void updateOutput(double currTime) = 0;
        virtual bool getOutput() { return output_; };
        int getID() { return id_; };
    protected:
        int id_;
        bool output_;
        vector<Element*> input_;
        friend class Graph;
};

class Sonda : public Element {
    public:
        Sonda(int id);
        void updateOutput(double currTime) override;
        void connectInput(Element* input) override;
        ~Sonda();
    private:
        bool last_state_;
};

class Source : public Element {
    public:
        void updateOutput(double currTime) override;
        void connectInput(Element* input) override;
    protected:
        queue<double> state_changes_;
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