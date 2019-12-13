#pragma once

#include <string>
#include <vector>

using namespace std;

class Graph {
    public:
        Graph(const string& filepath);
        ~Graph();
    private:
        int numb_of_elements_;
        vector<int> elements_; // Element*
};