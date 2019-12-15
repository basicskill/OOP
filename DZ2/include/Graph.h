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

        double getPeriod() { return max_period_; };
        int getSondeSize() { return sonde_.size(); };
        bool measure(int sondaNumber);

        ~Graph();

    private:
        vector<Element*> elements_;
        vector<Element*> sonde_;
        double max_period_;
};