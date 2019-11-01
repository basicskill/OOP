#include "Layer.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

// Layer init
Layer::Layer(int width, int height) { // FEJLOVI?
	// width, height and opacity init
	this->width = width;
	this->height = height;
	opacity = 0;
	
	// Dynamic matrix of pixels
	img = (pixel**) calloc(width, sizeof(pixel*));
	for (int i = 0; i < width; i++) 
		*(img + i) = (pixel*) calloc(height, sizeof(pixel));

	// Set all pixels to -1 (inactive)
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			img[i][j] = {-1, -1, -1};

}

// Load pixel matrix from char stream
bool Layer::loadImage(unsigned char *image, int it) {
	// Loading each pixel into matrix sequentially from hex stream
	// Bites are ordered BGR
	// New row starts on offset divisible by 4
	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			img[i][j].B = (int) image[it++];
			img[i][j].G = (int) image[it++];
			img[i][j].R = (int) image[it++];
		}
		while (it % 4) ++it;
	}

	return true;
}


bool Layer::copy2img(pixel*** dest) {
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			(*dest)[i][j] = img[i][j];
	return true;
}

// Print to stdout all relevent info
void Layer::getInfo() {
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++)
			cout	<< "(" 
					<< setw(3) << img[i][j].R << ", " 
					<< setw(3) << img[i][j].G << ", " 
					<< setw(3) << img[i][j].B 
					<< ") ";
		cout << endl;
	}
	cout << endl;
}


void Layer::setOpacity(int opc) {
	if ((opc >=0) && (opc <= 100))
		opacity = opc;
}


void Layer::fillRect(int x, int y, int w, int h, pixel C) {
	for (int i = x; i < x + w; ++i)
		for (int j = y; j < y + h; ++j)
			img[i][j] = C;
}


void Layer::eraseRect(int x, int y, int w, int h) {
	for (int i = x; i < x + w; ++i)
		for (int j = y; j < y + h; ++j)
			img[i][j] = {-1, -1, -1};
}


void Layer::crop(int x, int y, int w, int h) {
	pixel **newImg;
	newImg = (pixel**) calloc(w, sizeof(pixel*));
	for (int i = 0; i < w; i++) 
		*(newImg + i) = (pixel*) calloc(h, sizeof(pixel));
	
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j)
			newImg[i][j] = img[x + i][y + j];

	for (int i = 0; i < width; ++i)
		free(img[i]);
	free(img);

	img = newImg;

	width = w;
	height = h;
}


pixel Layer::getPixel(int x, int y) {
	return img[x][y];
}

int Layer::getOpacity() {
	return opacity;
}


bool Layer::checkBound(int x, int y) {
	return ((x >= 0) && (x < width) && (y >= 0) && (y < height));
}


void Layer::blur(int size) {
	pixel **newImg;
	newImg = (pixel**) calloc(width, sizeof(pixel*));
	for (int i = 0; i < width; i++) 
		*(newImg + i) = (pixel*) calloc(height, sizeof(pixel));

	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j) {
			int noPixels = 0;
			for (int x = i - size; x <= i + size; ++x)
				for (int y = j - size; y <= j + size; ++y)
					if ((checkBound(x, y) && img[x][y].R != -1)) {
						++noPixels;
						newImg[i][j].R += img[x][y].R;
						newImg[i][j].G += img[x][y].G;
						newImg[i][j].B += img[x][y].B;
					}
			newImg[i][j].R /= noPixels;
			newImg[i][j].G /= noPixels;
			newImg[i][j].B /= noPixels;
		}

	for (int i = 0; i < width; ++i)
		free(img[i]);
	free(img);

	img = newImg;
}


// Invert all set colors of Layer
// R' = 255 - R
// G' = 255 - G
// B' = 255 - B
void Layer::invertColors() {
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			if (img[i][j].R != -1) {
				img[i][j].R = 255 - img[i][j].R;
				img[i][j].G = 255 - img[i][j].G;
				img[i][j].B = 255 - img[i][j].B;
			}
}


void Layer::toGrayScale() {
	int tmp;
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			if (img[i][j].R != -1) {
				tmp = 0.3  * img[i][j].R 
					+ 0.59 * img[i][j].G
					+ 0.11 * img[i][j].B;
				img[i][j].R = tmp;
				img[i][j].G = tmp;
				img[i][j].B = tmp;
			}
}

void Layer::flipVertical() {
	pixel tmp;
	for (int i = 0; i < width / 2; ++i)
		for (int j = 0; j < height; ++j) {
			tmp = img[i][j];
			img[i][j] = img[width - 1 - i][j];
			img[width - 1 - i][j] = tmp;
		}
}


void Layer::flipHorizontal() {
	pixel tmp;
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height / 2; ++j) {
			tmp = img[i][j];
			img[i][j] = img[i][height - 1 - j];
			img[i][height - 1 - j] = tmp;
		}
}


// Free pixel matrix
Layer::~Layer() {
	for (int i = 0; i < width; ++i)
		free(img[i]);
	free(img);
}