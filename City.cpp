/*
Authors: Austin Mack, Tyler Hartwig
Final Project: Procedurally Generated City
*/

#include "City.h"
#include "Car.h"

void City::render() {
    glPushMatrix();
    
    glTranslatef(-WIDTH / 2, 0, -HEIGHT / 2);
    // Render all the buildings
    for(int i = 0; i < NUM_WIDTH; i++){
        for(int j = 0; j < NUM_HEIGHT; j++){
            glPushMatrix();
            glTranslatef(i * 80 + i * STREET_WIDTH, 0, j * 80 + j * STREET_WIDTH);
            blocks[i][j].render();
            glPopMatrix();
        }
    }

    // Render floor between buildings
    renderStreets();

    // Render cars going down streets parallel to each other
    renderVerticalCars();

    // Render cars going down the other parallel streets
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(-1040, 0, 0);
    renderVerticalCars();
    glPopMatrix();

    glPopMatrix();

}

void City::randomize() {
    // Render random velocities and positions for cars
    for(int i = 0; i < NUM_CARS; i++){
        car_pos[i] = rand() % 1000;
        car_vel[i] = 1 + rand() % 2;
    }
}

void City::renderVerticalCars(){
    // render 2 lanes of cars on every parallel street
   for(int i = 0; i < NUM_STREETS; i++){
        glPushMatrix();
        glTranslatef(i * 96, 0, 0);
        renderCarsOnStreet();
        glPopMatrix();
    }
}

void City::renderCarsOnStreet(){
    // Render cars going down one street
    renderCars();
    glPushMatrix();
    glScalef(1, 1, -1);
    glTranslatef(-6, 0, -1000);
    renderCars();
    glPopMatrix();
}
void City::renderStreets() {
    // Render all the streets, use the texture generated
    glBindTexture(GL_TEXTURE_2D, texID);
    for(int i = 0; i < NUM_STREETS; i++){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texID);
        glPushMatrix();
        glTranslatef(BLOCK_WIDTH * (i + 1) + i * STREET_WIDTH, 0, 0);

        glColor3f(1, 1, 1);

        glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, HEIGHT);
        glVertex3f(0, 0, HEIGHT);
        glTexCoord2f(STREET_WIDTH, HEIGHT);
        glVertex3f(STREET_WIDTH, 0, HEIGHT);
        glTexCoord2f(STREET_WIDTH, 0);
        glVertex3f(STREET_WIDTH, 0, 0);
        glEnd();

        glDisable(GL_TEXTURE_2D);


        glLineWidth(5);
        glTranslatef(STREET_WIDTH / 2, 0, 0);
        glColor3f(0.3, 0.3, 0);
        glBegin(GL_LINES);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(1, 1);
        glVertex3f(0, 0, HEIGHT);
        glEnd();
        glPopMatrix();

        glEnable(GL_TEXTURE_2D);
        glColor3f(1, 1, 1);
        glPushMatrix();
        glTranslatef(0, 0, BLOCK_WIDTH * (i + 1) + i * STREET_WIDTH);
        glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, HEIGHT);
        glVertex3f(0, 0, HEIGHT);
        glTexCoord2f(STREET_WIDTH, HEIGHT);
        glVertex3f(STREET_WIDTH, 0, HEIGHT);
        glTexCoord2f(STREET_WIDTH, 0);
        glVertex3f(STREET_WIDTH, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, STREET_WIDTH);
        glVertex3f(0, 0, STREET_WIDTH);
        glTexCoord2f(WIDTH, STREET_WIDTH);
        glVertex3f(WIDTH, 0, STREET_WIDTH);
        glTexCoord2f(WIDTH, 0);
        glVertex3f(WIDTH, 0, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        // Render lines down streets
        glLineWidth(5);
        glTranslatef(0, 0, STREET_WIDTH / 2);
        glColor3f(0.3, 0.3, 0);
        glBegin(GL_LINES);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(1, 1);
        glVertex3f(WIDTH, 0, 0);
        glEnd();
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, NULL);
        glDisable(GL_TEXTURE_2D);
    }
}

void City::renderCars() {
    // render single lane down a street
    for(int i = 0; i < NUM_CARS; i++) {
        glPushMatrix();
        glTranslatef(90, 1, car_pos[i]);
        car.render();
        glTranslatef(2, 0, 0);
        car.render();
        glPopMatrix();
        car_pos[i] -= car_vel[i] / 50.0;
        if(car_pos[i] < 0)
            car_pos[i] = 1000;
    }
}
