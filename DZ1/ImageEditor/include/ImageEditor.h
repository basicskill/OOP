#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "include/Layer.h"
#include "include/LayerList.h"
#include <string>

using namespace std;

class ImageEditor {
	public:
		ImageEditor();
		~ImageEditor();
		bool loadImage(unsigned char *input);
		unsigned char* saveImage();

		void getInfo();

		// Layer list manipulation
		void addLayer();
		bool deleteLayer();
		void selectLayer(int index);

		// Layer manipulation
		void setLayerOpacity(int opc);
		void setActiveColor(string hex);
		void fillRect(int x, int y, int w, int h);
		void eraseRect(int x, int y, int w, int h);
		void crop(int x, int y, int w, int h);

		// Color manipulation
		void invertColors();
		void toGrayScale();
		void blur(int size);

		// Flips
		void flipVertical();
		void flipHorizontal();

	private:
		int width, height;
		LayerList *Layers;
		string name;
		int activeLayer;
		pixel Color;

		pixel** exportImage();
};

#endif