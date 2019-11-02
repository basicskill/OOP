#include "include/ImageEditor.h"
#include "include/LayerList.h"
#include "include/Layer.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

// Helper function for turning hex digit to integer
int hex2int(char hex);

// Initialize width, height, activeLayer, name
// Set active color to black
ImageEditor::ImageEditor() {
	width = height = 0;
	name = "";
	Layers = nullptr;
	activeLayer = 0;

	// Start with black as active color
	Color.R = Color.G = Color.B = 0;	
}

// Parse image string into width, height and Layer 0
// TODO: Break into small functions !!!
bool ImageEditor::loadImage(unsigned char *image) {

	// Check if Image already loaded
	// If yes remove it from memory
	if (!Layers) delete Layers;

	// image string mustj start with "BM"
	if ((image[0] != 'B') || (image[1] != 'M'))
		return false;

	// Iterator for image string
	int it = 3;
	
	// File name is placed between two '='
	if  (image[2] == '=') {
		while (image[it] != '=') {
			name += image[it++];
		}
	}

	// width and height bytes must start on k % 4 == 0 
	while (it % 4) ++it;

	// Decoding width and height from little-endian
	width  =  (int) image[it++] * pow(16, 0);
	width +=  (int) image[it++] * pow(16, 2);
	width +=  (int) image[it++] * pow(16, 4);
	width +=  (int) image[it++] * pow(16, 6);

	height  = (int) image[it++] * pow(16, 0);
	height += (int) image[it++] * pow(16, 2);
	height += (int) image[it++] * pow(16, 4);
	height += (int) image[it++] * pow(16, 6);

	Layers = new LayerList(width, height, image, it);
	activeLayer = 0;

	return true;
}

// Returns unsigned char array of image in BM encoding
// TODO: Break into small functions !!!
unsigned char* ImageEditor::saveImage() {

	// Calculation of array size
	int size = 2; 									// BM
	if (name != "") size += 2 + name.length();		// =name=
	if (!(size % 4)) size += 4 - (size % 4);		// fill to divisible by 4 
	size += 8;										// width and height (4 bytes)
	int row_size = 0;
	if (!(row_size % 4))							// fill to divisible by 4
		row_size += 4 - (row_size % 4);
	size += height * row_size;						// size of whole pixel matrix

	// Array allocation
	unsigned char *encoding;
	encoding = (unsigned char*) calloc(size, sizeof(unsigned char*));

	// Iterator for image string
	int it = 2;

	encoding[0] = 'B'; encoding[1] = 'M';

	// File name is placed between two '='
	// If file name is empty skip this step
	if  (name.length()) {
		encoding[it++] = '=';
		for (int i = 0; i < name.length(); ++i)
			encoding[it++] = name[i];
		encoding[it++] = '=';
	}

	// width and height bytes must start at position % 4 == 0 
	// 'A' is used for filling unimportant bytes
	while (it % 4) encoding[it++] = 'A';

	// Encoding width and height into little-endian
	int tmp = width;
	for (int i = 0; i < 4; i++) {
		encoding[it++] = tmp % 256;		// pow(16, 2) == 256
		tmp /= 256;
	}

	tmp = height;
	for (int i = 0; i < 4; i++) {
		encoding[it++] = tmp % 256;		// pow(16, 2) == 256
		tmp /= 256;
	}

	// Construct pixel matrix from every Layer in List
	pixel **img;
	img = exportImage();

	// Turn pixel matrix into BM format for rows and columns
	// PRIVREMENO
	for (int j = height - 1; j >= 0; --j) {
		for (int i = 0; i < width; ++i) {
			encoding[it++] = (unsigned char) img[i][j].B;
			encoding[it++] = (unsigned char) img[i][j].G;
			encoding[it++] = (unsigned char) img[i][j].R;
		}
		while (it % 4) encoding[it++] = 'A';
	}

	// Free temp pixel matrix
	for (int i = 0; i < width; i++) 
		free(img[i]);
	free(img);

	return encoding;

}

// Construct pixel matrix from every Layer in List
pixel** ImageEditor::exportImage() {
	// Init pixel matrix to be exported
	pixel** img;
	img = (pixel**) calloc(width, sizeof(pixel*));
	for (int i = 0; i < width; i++) 
		*(img + i) = (pixel*) calloc(height, sizeof(pixel));


	pixel px;
	int pixelOpacity, remainingOpacity;
	// Combine Layers
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j) {
			remainingOpacity = 100;
			for (int it = 0; it < Layers->getSize(); ++it) {

				px = Layers->getLayer(it)->data->getPixel(i, j);
				pixelOpacity = Layers->getLayer(it)->data->getOpacity();

				if (px.R == -1) continue;

				px.R *= (remainingOpacity / 100) * (pixelOpacity / 100);
				px.G *= (remainingOpacity / 100) * (pixelOpacity / 100);
				px.B *= (remainingOpacity / 100) * (pixelOpacity / 100);

				img[i][j].R += px.R;
				img[i][j].G += px.G;
				img[i][j].B += px.B;

				remainingOpacity -= pixelOpacity;

			}
		}
	return img;
}


// Add empty Layer to end of Layer list
// set last Layer to be active Layer
void ImageEditor::addLayer() {
	Layers->addLayer(width, height);
	activeLayer = Layers->getSize() - 1;
}


// Delete active Layer from Layer list
bool ImageEditor::deleteLayer() {
	return Layers->deleteLayer(activeLayer);
}


// Change active Layer, if in list bounds
void ImageEditor::selectLayer(int index) {
	if ((index >= 0) && (index < Layers->getSize()))
		activeLayer = index;
}


// Set active Layer opacity
void ImageEditor::setLayerOpacity(int opc) {
	Layers->getLayer(activeLayer)->data->setOpacity(opc);
}


// Set active color based on '#RRGGBB' string
// Asume string is always corect
void ImageEditor::setActiveColor(string hex) {
	Color.R = hex2int(hex[2]) + hex2int(hex[1]) * 16;
	Color.G = hex2int(hex[4]) + hex2int(hex[3]) * 16;
	Color.B = hex2int(hex[6]) + hex2int(hex[5]) * 16;
}


// Draw rectangle on Layer with active color
// x, y - position on pixel matrix
// w, h - width and height of rectagnle
// Check if rectagle is completely in Layer bounds
// if not fit it to size and pass arguments to Layer fillRect func 
void ImageEditor::fillRect(int x, int y, int w, int h) {
	if (x > width) return;
	if (y > height) return;

	if (x < 0) x = 0;
	if (y < 0) y = 0;

	if (x + w > width) w = width - x;
	if (y + h > height) h = height - y;

	Layers->getLayer(activeLayer)->data->fillRect(x, y, w, h, Color);
}


// Set rectangle on Layer to transparent color
// x, y - position on pixel matrix
// w, h - width and height of rectagnle
// Check if rectagle is completely in Layer bounds
// If not fit it to size and pass arguments to Layer fillRect func 
// *** Can't erase on base Layer ***
void ImageEditor::eraseRect(int x, int y, int w, int h) {
	if (x > width) return;
	if (y > height) return;

	if (x < 0) x = 0;
	if (y < 0) y = 0;

	if (x + w > width) w = width - x;
	if (y + h > height) h = height - y;

	Layers->getLayer(activeLayer)->data->eraseRect(x, y, w, h);
}

void ImageEditor::crop(int x, int y, int w, int h) {
	if (x > width) return;
	if (y > height) return;

	if (x < 0) x = 0;
	if (y < 0) y = 0;

	if (x + w > width) w = width - x;
	if (y + h > height) h = height - y;

	for (int i = 0; i < Layers->getSize(); ++i)
		Layers->getLayer(i)->data->crop(x, y, w, h);

	width = w;
	height = h;
}


void ImageEditor::blur(int size) {
	Layers->getLayer(activeLayer)->data->blur(size);
}


// Display all relevant info
void ImageEditor::getInfo() {
	// Image Editor info
	cout << endl;
	cout << "===== " << name << " =====" << endl;
	cout << "width: " << width << endl;
	cout << "height: " << height << endl;
	cout << "active Layer: " << activeLayer << endl;
	cout << "active color: " << "(";
	cout << Color.R << ", " << Color.G << ", " << Color.B << ")" << endl;
	cout << endl;

	// Information for each Layer in list
	for (int i =  0; i < Layers->getSize(); ++i)
		Layers->getLayer(i)->data->getInfo();
}


// Invert colors on active Layer
void ImageEditor::invertColors() {
	Layers->getLayer(activeLayer)->data->invertColors();
}


// Grayscale colors on active Layer
void ImageEditor::toGrayScale() {
	Layers->getLayer(activeLayer)->data->toGrayScale();
}

void ImageEditor::flipVertical() {
	Layers->getLayer(activeLayer)->data->flipVertical();
}

void ImageEditor::flipHorizontal() {
	Layers->getLayer(activeLayer)->data->flipHorizontal();
}
// Remove list of Layers
ImageEditor::~ImageEditor() {
	delete Layers;
}


// Return integer from hex digit
int hex2int(char hex) {
	if ((hex >= '0') && (hex <= '9'))
		return hex - '0';
	
	if ((hex >= 'A') && (hex <= 'F'))
		return 10 + (hex - 'A');

	// if ((hex >= 'a') && (hex <= 'f'))
	return 10 + (hex - 'a');
}