/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/
#ifndef DENSE_H
#define DENSE_H

#include "Texture.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
class Dense : public Texture{
	private:
		const int NUM_WINDOWS = 32;
	public:
		Dense(){
			//For each window in the texture
			for (int i = 0; i < NUM_WINDOWS; i++){
				for (int j = 0; j < NUM_WINDOWS; j++){
					int onOff = rand() % 100;
					//Turn it on if its dense
					if (onOff < 10){
						int randBR1 = 6 + rand() % (10 - 6);

						genWindow(i, j, (double)randBR1 / 10);
					}
					//Turn it off if not
					else{
						int randBR2 = 0 + rand() % (2 - 1);
						genWindow(i, j, (double)randBR2 / 15);
					}
				}
			}
		}
};

#endif