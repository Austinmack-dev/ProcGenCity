/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/

#ifndef SPARSE_H
#define SPARSE_H
#include "Texture.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
class Sparse : public Texture{
	private:
		const int NUM_WINDOWS = 32;
	public:
		Sparse(){
			//For each window in the texture
			for (int i = 0; i < NUM_WINDOWS; i++){
				for (int j = 0; j < NUM_WINDOWS; j++){
					int onOff = rand() % 100;
					//Turn on the window if the value is very low
					if (onOff > 98){
						int randBR1 = 6 + rand() % (10 - 6);

						genWindow(i, j, (double)randBR1 / 10);
					}
					//Turn off the window if the value is high
					else{
						int randBR2 = 0 + rand() % (2 - 1);
						genWindow(i, j, (double)randBR2 / 15);
					}
				}
			}
		}
};

#endif