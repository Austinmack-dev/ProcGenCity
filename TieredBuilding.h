/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/
#ifndef CITY_TIEREDBUILDING_H
#define CITY_TIEREDBUILDING_H


#include "Building.h"

/*
 * Class creates a building with multiple tiers. Every tier is textured
 * Every tier can also have rims
 */
class TieredBuilding : public Building{
private:
    const int TIERED_MAX_HEIGHT = MAX_HEIGHT * 2 / 3;
    const int MAX_TIERS = 4;
    int tiers;
    int base_height, rim_height, tier_height;
    int rim_offset, rim_width;
    bool has_rims;
    void renderBase();
    void renderBody(int level = -1);
public:
    TieredBuilding(int width = 100000, int height = 100000) : Building(width, height){
        randomize();
    }
    void randomize();
    void render(int level = -1);
};


#endif //CITY_TIEREDBUILDING_H
