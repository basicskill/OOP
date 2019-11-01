#ifndef LAYER_H
#define LAYER_H

// Struct representation of pixel
typedef struct {
	int R, G, B;
} pixel;


class Layer {
	public:
		Layer(int width, int height);
		~Layer();
		bool loadImage(unsigned char *image, int it);

		void getInfo();
		bool copy2img(pixel*** dest);
		bool checkBound(int x, int y);
		pixel getPixel(int x, int y);
		int getOpacity();

		void setOpacity(int opc);
		void fillRect(int x, int y, int w, int h, pixel C);
		void eraseRect(int x, int y, int w, int h);
		void crop(int x, int y, int w, int h);
		void blur(int size);

		void invertColors();
		void toGrayScale();

		// Flips
		void flipVertical();
		void flipHorizontal();
	private:
		pixel **img;
		int width, height;
		int opacity;

};

#endif