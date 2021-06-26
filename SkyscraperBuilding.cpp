/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/

#include "SkyscraperBuilding.h"

void SkyscraperBuilding::randomize() {
    height = MAX_HEIGHT - (rand() % 20);

    int random = rand() % 100;
    if(random < 25){
        texture = new Sparse();
    } else if(random < 30){
        texture = new Dense();
    } else if(random < 75){
        texture = new Grouped();
    } else {
        texture = new Lined();
    }

    texture->pixelToChar(ptr);

    delete texture;

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, ptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, NULL);
}

void SkyscraperBuilding::renderBody() {
    renderTexture = true;
    glBindTexture(GL_TEXTURE_2D, texID);
    glColor3fv(white);
    renderCube(width, length, height);
    glBindTexture(GL_TEXTURE_2D, NULL);
    renderTexture = false;
}

void SkyscraperBuilding::render(int level) {
    renderBody();
}
