/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/
#ifndef GROUPED_H
#define GROUPED_H
#include "Texture.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
class Grouped : public Texture{
	private:
		const int NUM_WINDOWS = 32;

	public:
		Grouped(){
			int groups = rand() % 10;
			if (rand() % 100 < 30){
				groups += 10;
			}
			//For each window in the texture
			for (int i = 0; i < NUM_WINDOWS; i++){
				for (int j = 0; j < NUM_WINDOWS; j++){
					int randBR = 0 + rand() % (2 - 1);
					genWindow(i, j, (double)randBR/15);
				}
			}
			//For each group
			for (int g = 0; g < groups; g++){
				int randI = rand() % 23;
				int randJ = rand() % 23;
				int groupSize = 2 + rand() % (6 - 2);
				
				for (int i = randI; i < randI + groupSize; i++){
					for (int j = randJ; j < randJ + groupSize; j++){
						int random = rand() % 100;
						//Turn a random number of windows on in the group
						if (random < 20){
							int randBR1 = 6 + rand() % (10 - 6);

							genWindow(i, j, (double)randBR1 / 10);
						}
						//Turn a random number of windows off in the group
						else{
							int randBR2 = 0 + rand() % (2 - 1);
							genWindow(i, j, (double)randBR2 / 15);
						}
					}
				}
			}
		}
};

#endif