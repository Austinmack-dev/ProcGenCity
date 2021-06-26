/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/

#ifndef CITY_SMALLBUILDING_H
#define CITY_SMALLBUILDING_H

#include <cstdlib>
#include "Building.h"
#include "Algebra.h"

/*
 * class produces a very short building, with AC units on top, and possible "rims" around it
 */
class SmallBuilding : public Building {
private:
    const static int MAX_AC_UNIT = 3;
    const int SMALL_MAX_HEIGHT = MAX_HEIGHT / 3;
    int ac_units;
    Point ac_loc[MAX_AC_UNIT];
    float ac_rot;
    int base_height, rim_height;
    bool has_rim, has_mid_rim;
    void renderBase();
    void renderBody();
    void renderRim();

public:
    SmallBuilding(int width = 100000, int height = 100000) : Building(width, height){
        randomize();
    }
    void randomize();
    void render(int level = -1);
};


#endif //CITY_SMALLBUILDING_H
