/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/

#ifndef CITY_BUILDING_H
#define CITY_BUILDING_H

#include <GL/glui.h>
#include <stdio.h>
#include "Texture.h"
#include "Dense.h"
#include "Sparse.h"
#include "Grouped.h"
#include "Lined.h"

/*
 * Abstract class for building, any building should inherit from this.
 * The important functions are randomize() and render()
 */
class Building{
protected:
    const int MAX_HEIGHT = 100;
    // The texture sizes used for a building
    const static int TEXTURE_WIDTH = 512;
    const static int TEXTURE_HEIGHT = 512;
    const int MAX_BASE = 2;
    int width, length, height;
    Texture *texture;
    bool renderTexture;
    char ptr[TEXTURE_WIDTH * TEXTURE_HEIGHT * 3];
    GLuint texID;
    const int WINDOWS = 32;
    const GLfloat black[3] = { 0.07, 0.07, 0.07 };
    const GLfloat white[3] = { 1, 1, 1 };

    void printGLError(){
        GLenum error = glGetError();
        if(error != GL_NO_ERROR)
            printf("error: %s\n", gluErrorString(error));
        else
            printf("no error!\n");
    }

    void renderCube(int width, int length, int height) {
        float texUnit = 1.0f / WINDOWS;
        float texHeight = texUnit * height;
        float texWidth = texUnit * width;

        glDisable(GL_TEXTURE_2D);


        glBegin(GL_QUADS);
            // Bottom
            glNormal3f(0, -1, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, length);
            glVertex3f(width, 0, length);
            glVertex3f(width, 0, 0);
        glEnd();

        if(renderTexture)
            glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
            // Pos Z
            glNormal3f(0, 0, 1);
            glTexCoord2f(1, texHeight);
            glVertex3f(0, 0, 0);
            glTexCoord2f(1 - texWidth, texHeight);
            glVertex3f(width, 0, 0);
            glTexCoord2f(1 - texWidth, 0);
            glVertex3f(width, height, 0);
            glTexCoord2f(1, 0);
            glVertex3f(0, height, 0);


            // Pos X
            glNormal3f(1, 0, 0);
            glTexCoord2f(1, 1);
            glVertex3f(width, 0, 0);
            glTexCoord2f(1 - texWidth, 1);
            glVertex3f(width, 0, length);
            glTexCoord2f(1 - texWidth, 1 - texHeight);
            glVertex3f(width, height, length);
            glTexCoord2f(1, 1 - texHeight);
            glVertex3f(width, height, 0);

        //glColor3f(0, 0, 1);
            // Neg Z
            glNormal3f(0, 0, -1);
            glTexCoord2f(texWidth, 1);
            glVertex3f(width, 0, length);
            glTexCoord2f(0, 1);
            glVertex3f(0, 0, length);
            glTexCoord2f(0, 1 - texHeight);
            glVertex3f(0, height, length);
            glTexCoord2f(texWidth, 1 - texHeight);
            glVertex3f(width, height, length);

            // Neg X
            glNormal3f(-1, 0, 0);
            glTexCoord2f(texWidth, texHeight);
            glVertex3f(0, 0, length);
            glTexCoord2f(0, texHeight);
            glVertex3f(0, 0, 0);
            glTexCoord2f(0, 0);
            glVertex3f(0, height, 0);
            glTexCoord2f(texWidth, 0);
            glVertex3f(0, height, length);
        glEnd();

        if(renderTexture)
            glDisable(GL_TEXTURE_2D);

        glColor3fv(black);
        glBegin(GL_QUADS);
            // Top
            glNormal3f(0, 1, 0);
            glVertex3f(0, height, 0);
            glVertex3f(0, height, length);
            glVertex3f(width, height, length);
            glVertex3f(width, height, 0);
        glEnd();


    }

    void renderACUnit(){
        renderCube(3, 2, 3);

        glPushMatrix();
        glTranslatef(1, 0, 0);
        renderCube(1, 3, 1);
        glPopMatrix();
    }

public:
    Building(int width = 0, int height = 0){
        this->width = width;
        this->length = height;
        randomize();
    }
    virtual void render(int level = -1) = 0;
    virtual void randomize(){

    }
    void setWidth(int width){
        this->width = width;
    };
    void setHeight(int height){
        this->height = height;
    };
};

#endif //CITY_BUILDING_H
