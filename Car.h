/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/

#ifndef CITY_CAR_H
#define CITY_CAR_H

#include <math.h>
#include <OpenGL/OpenGL.h>
#include <stddef.h>
#include <stdio.h>

class Car{
private:
    const static int TEXTURE_WIDTH = 32;
    const static int TEXTURE_HEIGHT = 32;
    GLuint texID;

public:
    void render(){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glBegin(GL_QUADS);
        glColor3f(1, 1, 0);
        glTexCoord2f(0, 1);
        glVertex3f(-1, 1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(-1, -1, 0);
        glTexCoord2f(1, 0);
        glVertex3f(1, -1, 0);
        glTexCoord2f(1, 1);
        glVertex3f(1, 1, 0);

        glColor3f(1, 0, 0);
        glTexCoord2f(0, 1);
        glVertex3f(-1, 1, 1);
        glTexCoord2f(0, 0);
        glVertex3f(-1, -1, 1);
        glTexCoord2f(1, 0);
        glVertex3f(1, -1, 1);
        glTexCoord2f(1, 1);
        glVertex3f(1, 1, 1);
        glEnd();

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        glBindTexture(GL_TEXTURE_2D, NULL);
        glDisable(GL_TEXTURE_2D);
    }
    Car(){
        // Create a circular texture that fades
        unsigned char ptr[TEXTURE_WIDTH * TEXTURE_HEIGHT * 4];
        for(int i = 0; i < TEXTURE_WIDTH; i++){
            for(int j = 0; j < TEXTURE_HEIGHT; j++) {
                double distance = sqrt(pow(i - TEXTURE_WIDTH / 2, 2.0) + pow(j - TEXTURE_HEIGHT / 2, 2.0));
                float alpha = 1 - distance / (TEXTURE_WIDTH / 2);
                if(alpha < 0)
                    alpha = 0;
                ptr[(i + j * TEXTURE_WIDTH) * 4] = 255;
                ptr[(i + j * TEXTURE_WIDTH) * 4 + 1] = 255;
                ptr[(i + j * TEXTURE_WIDTH) * 4 + 2] = 255;
                ptr[(i + j * TEXTURE_WIDTH) * 4 + 3] = 255.0 * alpha;
                //printf("i: %i j: %i - %i, %i, %i, %i\n", i, j, ptr[i * 4 + j * TEXTURE_WIDTH],ptr[i * 4 + j * TEXTURE_WIDTH + 1],ptr[i * 4 + j * TEXTURE_WIDTH + 2],ptr[i * 4 + j * TEXTURE_WIDTH + 3]);
            }
        }


        // Send the images to the graphics card and set up texture parameters
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, NULL);
    }

};

#endif //CITY_CAR_H
