/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/
#include "SmallBuilding.h"


void SmallBuilding::randomize() {
    height = SMALL_MAX_HEIGHT - rand() % 10;
    base_height = (rand() % MAX_BASE) + 1;
    rim_height = 1;
    has_rim = rand() % 3 < 1;
    has_mid_rim = rand() % 3 < 1 && has_rim;
    ac_units = rand() % (MAX_AC_UNIT + 1);
    if(rand() % 2)
        ac_units = 0;
    ac_rot = rand() % 360;
    for(int i = 0; i < ac_units; i++){
        int x = rand() % (width / 2);
        int z = rand() % (length / 2);
        x += (width / 4);
        z += length / 4;
        ac_loc[i] = Point(x, 0, z);
    }

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

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, ptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, NULL);
}

void SmallBuilding::render(int level) {
    glClearColor(0.1, 0.1, 0.1, 1);
    if(level > 0 || level == -1)
        renderBase();

    if(level > 1 || level == -1) {
        glPushMatrix();
        glTranslatef(1, 0, 1);
        renderBody();
        glPopMatrix();
    }

    if(level > 2 || level == -1) {
        if (has_rim) {
            glPushMatrix();
            glTranslatef(0, height - 1, 0);
            renderRim();
            glPopMatrix();
        }

        if (has_mid_rim) {
            glPushMatrix();
            glTranslatef(0, height / 2, 0);
            renderRim();
            glPopMatrix();
        }
    }

    if(level > 3 || level == -1) {
        for(int i = 0; i < ac_units; i++) {
            glPushMatrix();
            glTranslatef(ac_loc[i][0] + 1, height, ac_loc[i][2] + 1);
            glRotatef(ac_rot, 0, 1, 0);
            renderACUnit();
            glPopMatrix();
        }
    }

}

void SmallBuilding::renderBase() {
    glColor3fv(black);
    renderCube(width, length, base_height);
}

void SmallBuilding::renderBody() {
    glColor3f(1, 1, 1);
    renderTexture = true;
    glBindTexture(GL_TEXTURE_2D, texID);
    renderCube(width - 2, length - 2, height);
    glBindTexture(GL_TEXTURE_2D, NULL);
    renderTexture = false;
}


void SmallBuilding::renderRim() {
    glColor3fv(black);
    renderCube(width, length, rim_height);
}
