#pragma once

#include <string>
#include <vector>
#include "../include/Element.h"

using namespace std;

class Graph {
    public:
        Graph(const string& filepath);
        Element* findByID(int id);
        void update(double currTime);

        double getFrequency() { return min_frequency_; };
        int getSondeSize() { return sonde_.size(); };
        bool measure(int sondaNumber);

        ~Graph();

    private:
        vector<Element*> elements_;
        vector<Element*> sonde_;
        double min_frequency_;
};