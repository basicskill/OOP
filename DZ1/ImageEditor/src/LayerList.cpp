#include "LayerList.h"
#include "Layer.h"
#include <iostream>

using namespace std;


// Init of base parameters
LayerList::LayerList(int width, int height, unsigned char *image, int it) {
	base = new LayerNode;

	base->data = new Layer(width, height);
	base->next = nullptr;

	base->data->loadImage(image, it);
	
	listSize = 1;
}


// Add new transparent Layer to end of list
void LayerList::addLayer(int width, int height) {
	// Allocate space for new LayerNode
	LayerNode *newLayer;
	newLayer = new LayerNode;

	// Create new Layer obejct
	newLayer->data = new Layer(width, height);
	newLayer->next = nullptr;

	// Select last element of list
	LayerNode *it = base;
	while (it->next) it = it->next;
	
	// Add new Layer to end of list
	it->next = newLayer;

	++listSize;
}


// Return pointer to i-th element of list
LayerNode* LayerList::getLayer(int number) {
	LayerNode* it = base;
	for (int i = 0; i < number; ++i) it = it->next;
	return it;
}


// Return List size
int LayerList::getSize() {
	return listSize;
}


// Remove Layer on requested index from list
bool LayerList::deleteLayer(int index) {
	// Check for invalid request
	if ((index <= 0) || (index >= listSize))
		return false;
		
	// Set tmp pointer to Layer to be deleted
	LayerNode *tmp = getLayer(index);

	// Set it pointer to Layer before deletion
	LayerNode *it = getLayer(index - 1);

	// Remove Layer on place 'index' from list
	it->next = tmp->next;

	// Free Layer on place 'index' from memory
	delete tmp->data;
	free(tmp);

	return true;
}


// Delete every Layer object in list
// Free all nodes
LayerList::~LayerList() {
	LayerNode *tmp;
	while (base) {
		tmp = base;
		base = base->next;
		delete tmp->data;
		free(tmp);
	}
}