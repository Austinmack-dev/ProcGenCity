/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/

#ifndef LINED_H
#define LINED_H

class Lined : public Texture{
	private:
		const static int NUM_WINDOWS = 32;
	public:
		Lined(){
			//Generate random j values
			bool randJ[NUM_WINDOWS];
			int percentage = 5 + rand() % 20;
			for (int i = 0; i < NUM_WINDOWS; i++){
				randJ[i] = rand() %  100 < percentage;
			}
			//For each window in the texture
			for (int i = 0; i < NUM_WINDOWS; i++){
				for (int j = 0; j < NUM_WINDOWS; j++){
					int onOff = rand() % 100;
					//If the number is higher than 40 and the randJ exists
					if (onOff < 30 && randJ[j]){
						int randBR1 = 6 + rand() % (10 - 6);
						genWindow(rand()%NUM_WINDOWS, j, (double)randBR1 / 10);
					}
					//If not turn the windows off
					else{
						int randBR2 = 0 + rand() % (2 - 1);
						genWindow(rand()%NUM_WINDOWS, j, (double)randBR2 / 15);
					}
				}
			}
		}
};

#endif