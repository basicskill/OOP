#pragma once

#include <string>
#include <vector>
#include <list>
#include "../include/Element.h"

using namespace std;

class Graph {
    public:
        Graph(const string& filepath);
        double getFrequency() { return min_frequency_; };
        ~Graph();
        Element* findByID(int id);
    private:
        vector<Element*> elements_;
        list<int> sonde_;
        double min_frequency_;
};