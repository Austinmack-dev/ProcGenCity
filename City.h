/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/
#ifndef CITY_CITY_H
#define CITY_CITY_H


#include "Block.h"
#include "Car.h"

class City {
private:
    const static int NUM_WIDTH = 11;
    const static int NUM_HEIGHT = 11;
    const static int NUM_STREETS = 10;
    const static int STREET_WIDTH = 16;
    const static int BLOCK_WIDTH = 80;
    const static int NUM_CARS = 100;
    const int TEXTURE_WIDTH = 64;
    const int TEXTURE_HEIGHT = 64;
    const int WIDTH = 1000;
    const int HEIGHT = 1000;
    GLuint texID;
    Block blocks[NUM_WIDTH][NUM_HEIGHT];
    Car car;
    float car_pos[NUM_CARS];
    float car_vel[NUM_CARS];
public:
    int move;
    City(){
        char *streetTexture = new char[TEXTURE_WIDTH * TEXTURE_HEIGHT * 3];
        int base = 5;
        for(int i = 0; i < TEXTURE_WIDTH * TEXTURE_HEIGHT * 3; i++){
            streetTexture[i] = base + rand() % 7;
        }
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, streetTexture);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, NULL);

        delete [] streetTexture;
        randomize();
    }

    ~City(){
    }

    void render();
    void renderStreets();
    void randomize();
    void renderCars();

    void renderCarsOnStreet();

    void renderVerticalCars();
};


#endif //CITY_CITY_H
