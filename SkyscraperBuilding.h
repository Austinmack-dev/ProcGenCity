/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/
#ifndef CITY_SKYSCRAPERBUILDING_H
#define CITY_SKYSCRAPERBUILDING_H


#include "Building.h"

/*
 * class produces a very tall simple building
 */
class SkyscraperBuilding : public Building {
private:
    void renderBody();
public:
    SkyscraperBuilding(int width = 100000, int height = 100000) : Building(width, height){
        randomize();
    }
    void render(int level = -1);
    void randomize();
};


#endif //CITY_SKYSCRAPERBUILDING_H
