/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/
#include <stdlib.h>
#include "TieredBuilding.h"

void TieredBuilding::randomize() {
    height = TIERED_MAX_HEIGHT - rand() % 7;
    tiers = rand() % MAX_TIERS + 1;
    has_rims = rand() % 4 < 1;
    base_height = 1;
    tier_height = height / tiers;
    rim_height = rand() % 3 + 1;
    rim_offset = rim_height - 1 - rand() % 3;
    rim_offset = abs(rim_offset);
    rim_width = rand() % 2 + 1;


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

void TieredBuilding::render(int level) {
    if(level > 0 || level == -1)
        renderBase();
    if(level > 1 || level == -1)
        renderBody(level - 1);

}

void TieredBuilding::renderBase() {
    renderCube(width, length, base_height);
}

void TieredBuilding::renderBody(int level) {
    renderTexture = true;
    for(int i = 0; i < tiers; i++){
        if(i > level || level < 0){
            glPushMatrix();
            glTranslatef(1 + i, i * tier_height, 1 + i);
            glColor3fv(white);
            glBindTexture(GL_TEXTURE_2D, texID);
            renderCube(width - (i + 1) * 2, length - (i + 1) * 2, tier_height);
            glBindTexture(GL_TEXTURE_2D, NULL);

            if(has_rims) {
                glTranslatef(-rim_width, tier_height - 1 - rim_offset, -rim_width);
                int modifier = (2 * rim_width) - (i + 1) * 2;
                renderCube(width + modifier, length + modifier, rim_height);
            }


            glPopMatrix();
        }
    }
    renderTexture = false;
}
