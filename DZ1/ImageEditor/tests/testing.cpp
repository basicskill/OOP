#include "include/ImageEditor.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {

	// data loading
	unsigned char data[100];
	ifstream infile;
	infile.open("proba1.dat");
	infile >> data;

	ImageEditor *Editor = new ImageEditor();
	Editor->loadImage(data);
	Editor->getInfo();

	Editor->blur(1);
	Editor->getInfo();

	Editor->saveImage();

	delete Editor;

	return 0;
}