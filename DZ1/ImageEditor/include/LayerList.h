#ifndef LAYERLIST_H
#define LAYERLIST_H

#include "Layer.h"

using namespace std;

typedef struct node{
	Layer* data;
	struct node* next;
} LayerNode;

class LayerList {
	public:
		LayerList(int width, int height, unsigned char *image, int it);
		~LayerList();

		int getSize();
		LayerNode* getLayer(int number);

		void addLayer(int width, int height, int index);
		bool deleteLayer(int index);

	private:
		LayerNode *base;
		int listSize;

};


#endif