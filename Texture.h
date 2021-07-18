/*
 Authors: Austin Mack, Tyler Hartwig
 Final Project: Procedurally Generated City
*/

#ifndef TEXTURE_H
#define TEXTURE_H
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;


/*
Description: This class holds information for a Pixel
Variables:
	r--the red component of a pixel
	g--the green component of a pixel
	b--the blue component of a pixel
*/
class Pixel{
public:
	Pixel(){
		r = 0;
		g = 0;
		b = 0;
	}
	Pixel& operator=(const Pixel& other)
	{
		this->r = other.r;
		this->g = other.g;
		this->b = other.b;
		return *this;
	}
	unsigned char r, g, b;
	int size;
};


class Texture{
	public:
		Texture(){
			data = new Pixel[SIZE];
		};
		~Texture(){
			delete[] data;
		};
		void pixelToChar(char* finalData){
			int charArraySize = SIZE * 3;
			for (int i = 0, j = 0; i < charArraySize, j < SIZE; i += 3, j++){
				Pixel curPix = data[j];
				finalData[i] = curPix.r;
				finalData[i + 1] = curPix.g;
				finalData[i + 2] = curPix.b;
			}
		}
	protected:
		void genWindow(int x, int y, double brightness){
			int r = 175;
			int g = 175;
			int b = 140;
			r -= rand() % 40 - 10;
			g -= rand() % 40 - 10;
			b -= rand() % 40 - 10;

			int rc = rand() % 255;
			int gc = rand() % 255;
			int bc = rand() % 255;

			//Creates a texture for a single window
			for (int i = 0; i < WINDOW_WIDTH; i++){
				for (int j = 0; j < WINDOW_WIDTH; j++){
					//Allows for little boxes of color
					int minI = rand() % 32;
					int maxI = minI + rand() % (32 - minI);
					int minJ = (WINDOW_WIDTH / 2) + rand() % (32 - (WINDOW_WIDTH / 2));
					int br = 1 + rand() % (7 - 2);
					double randBR = (double)br / 10;
					int br1 = 5 + rand() % (10 - 5);
					double randHighBR = (double)br1 / 10;
					//Indexes the color of the texture
					int index = ((x*WINDOW_WIDTH) + i) + (j*WINDOW_WIDTH*NUM_WINDOWS) + (WINDOW_WIDTH * WIDTH * y);
					//Bottom half of the window
					if (j > WINDOW_WIDTH / 2){
						int random = rand() % 100;
						if (random < 60){
							data[index].r = r*randBR*brightness;
							data[index].g = g*randBR*brightness;
							data[index].b = b*randBR*brightness;
						}
						else{
							data[index].r = rc*randBR*brightness;
							data[index].g = gc*randBR*brightness;
							data[index].b = bc*randBR*brightness;
						}

						
					}
					//Top half of the window
					else{
						data[index].r = r*randHighBR*brightness;
						data[index].g = g*randHighBR*brightness;
						data[index].b = b*randHighBR*brightness;
					}

					if (j > minJ){	
						if (i > minI && i < maxI){
							data[index].r = r*randBR*brightness;
							data[index].g = g*randBR*brightness;
							data[index].b = b*randBR*brightness;
						}
						
					}
				}
			}

		};
		Pixel* data;
		const int HEIGHT = 512;
		const int WIDTH = 512;
		const int WINDOW_WIDTH = 16;
		const int SIZE = HEIGHT*WIDTH;
		const int NUM_WINDOWS = 32;

};


#endif