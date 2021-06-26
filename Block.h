/*
 Authors: Austin Mack, Tyler Hartwig
 Final Project: Procedurally Generated City
*/

#ifndef CITY_BLOCK_H
#define CITY_BLOCK_H

#include <ostream>
#include <iostream>
#include "Building.h"
#include "SmallBuilding.h"
#include "TieredBuilding.h"
#include "SkyscraperBuilding.h"
#include "ModernBuilding.h"

class Block{
private:
    int width, height;
    int heightDivs;
    int widthDivs[3];
    int heights[3];
    int widths[3][3];
    int numBuildings;
    Building** buildings;
public:
    Block(){
        height = 80, width = 80;
        randomize();
    }

    void render(){
        int buildingCounter = 0;
        int curHeight = 0;
        for(int i = 0; i < heightDivs; i++){
            int curWidth = 0;
            for(int j = 0; j < widthDivs[i]; j++){
                glPushMatrix();
                glTranslatef(curWidth, 0, curHeight);

                buildings[buildingCounter]->render();

                glPopMatrix();
                buildingCounter++;

                curWidth += widths[i][j];
            }
            curHeight += heights[i];
        }

    }

    void randomize(){
        numBuildings = 0;
        heightDivs = rand() % 2 + 2;

        int totalHeight = 0;
        int i;
        for(i = 0; i < heightDivs - 1; i++){
            heights[i] = height / heightDivs + (rand() % 6 - 3);
            totalHeight += heights[i];
        }
        heights[i] = height - totalHeight;

        for(int j = 0; j < heightDivs; j++){
            widthDivs[j] = rand() % 2 + 2;
            numBuildings += widthDivs[j];
            int totalWidth = 0;
            for(i = 0; i < widthDivs[j] - 1; i++){
                widths[j][i] = width / widthDivs[j] + (rand() % 6 - 3);
                totalWidth += widths[j][i];
            }
            widths[j][i] = width - totalWidth;
        }

        buildings = new Building*[numBuildings];

        int buildingCount = 0;
        for(int k = 0; k < heightDivs; k++){
            for(int l = 0; l < widthDivs[k]; l++) {
                int random = rand() % 100;
                if (random < 25)
                    buildings[buildingCount] = new SmallBuilding(widths[k][l], heights[k]);
                else if (random < 50)
                    buildings[buildingCount] = new TieredBuilding(widths[k][l], heights[k]);
                else if (random < 75)
                    buildings[buildingCount] = new SkyscraperBuilding(widths[k][l], heights[k]);
                else
                    buildings[buildingCount] = new ModernBuilding(widths[k][l], heights[k]);
                buildingCount++;
            }
        }
    }


};

#endif //CITY_BLOCK_H
