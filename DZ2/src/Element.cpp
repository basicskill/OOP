#include "../include/Element.h"

// Init id_ and output_
Element::Element(int id) : id_(id), output_(false) {}

// Return output of element
bool Element::getOutput() { 
    return output_; 
}

// Return ID of element
int Element::getID() { 
    return id_; 
}