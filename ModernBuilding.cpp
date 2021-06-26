//
// Created by Tyler Hartwig on 12/7/15.
//

#include <iostream>
#include "ModernBuilding.h"

// randomize the shape of the building
void ModernBuilding::randomize() {
    height = MAX_HEIGHT * 3 / 4 - (rand() % 10);
    center1 = IntPoint(rand() % (width / 2) + (width / 4), rand() % (length / 4) + (length / 4));
    center2 = IntPoint(rand() % (width / 2) + (width / 4), rand() % (length / 4) + (length / 2));

    int oneWidth = std::min(center1.X, width - center1.X);
    int oneLength = std::min(center1.Y, length - center1.Y);
    int twoWidth = std::min(center2.X, width - center2.X);
    int twoLength = std::min(center2.Y, length - center2.Y);

    if (rand() % 100 < 75) {
        if (rand() % 100 < 60)
            one = randomElipse(center1, oneWidth, oneLength);
        else
            one = randomCircle(center1, std::min(oneWidth, oneLength));
    } else {
        if (rand() % 100 < 75)
            one = randomRectangle(center1, oneWidth, oneLength);
        else
            one = randomSquare(center1, std::min(oneWidth, oneLength));
    }

    if (rand() % 100 < 70) {
        if (rand() % 100 < 70)
            two = randomElipse(center2, twoWidth, twoLength);
        else
            two = randomCircle(center2, std::min(twoWidth, twoLength));
    } else {
        if (rand() % 100 < 75)
            two = randomRectangle(center2, twoWidth, twoLength);
        else
            two = randomSquare(center2, std::min(twoWidth, twoLength));
    }


    Paths result;
    Clipper c;
    c.AddPath(one, ptSubject, true);
    c.AddPath(two, ptClip, true);
    int random = rand() % 100;
    if (random < 50){
        c.Execute(ctIntersection, result);
        clipType = ctIntersection;
    } else {
        c.Execute(ctUnion, result);
        clipType = ctUnion;
    }

    if(result.size())
        shape = result;
    else
        randomize();

    random = rand() % 100;
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

// Render the extrusion of the resulting path
void ModernBuilding::render(int level) {
    float textureUnit = 1.0f / WINDOWS;
    float currentTexPos = 0;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);
    glColor3fv(white);

    int test = shape.size();
    for(int i = 0; i < shape.size(); i++){
        unsigned long size = shape[i].size();


        for (int j = 0; j < size; j++) {
            IntPoint two;
            IntPoint one = shape[i][j];

            if (j == size - 1)
                two = shape[i][0];
            else
                two = shape[i][j + 1];

            Point base(one.X, 0, one.Y);
            Point right(two.X, 0, two.Y);
            Point left(one.X, 20, one.Y);

            Vector vOne = right - base;
            Vector vTwo = left - base;
            Vector normal = cross(vTwo, vOne);
            normal.normalize();

            int curWidth = std::max(std::abs(one.X - two.X), std::abs(one.Y - two.Y));

            glBegin(GL_QUADS);
            glNormal3f(normal[0], normal[1], normal[2]);
            glTexCoord2f(currentTexPos, 0);
            glVertex3f(one.X, 0, one.Y);
            glTexCoord2f(currentTexPos + curWidth * textureUnit, 0);
            glVertex3f(two.X, 0, two.Y);
            glTexCoord2f(currentTexPos + curWidth * textureUnit, textureUnit * height);
            glVertex3f(two.X, height, two.Y);
            glTexCoord2f(currentTexPos, textureUnit * height);
            glVertex3f(one.X, height, one.Y);
            glEnd();

            currentTexPos += curWidth * textureUnit;
        }
    }

    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);
    renderTop();
    renderBase();
}

// Generate ellipse using clipper library
Path ModernBuilding::randomElipse(IntPoint center, int width, int length) {
    Path path;

    for(int i = 0; i < 360; i++){
        int x, y;
        x = width * sin(i * PI / 180.0) + center.X;
        y = length * cos(i * PI / 180.0) + center.Y;
        path << IntPoint(x, y);
    }

    return path;
}

// Generate circle using clipper library
Path ModernBuilding::randomCircle(IntPoint center, int radius) {
    Path path;


    for(int i = 0; i < 360; i++){
        int x, y;
        x = radius * sin(i * PI / 180.0) + center.X;
        y = radius * cos(i * PI / 180.0) + center.Y;
        path << IntPoint(x, y);
    }

    return path;
}

// Generate rectangle using clipper libraries
Path ModernBuilding::randomRectangle(IntPoint center, int width, int length) {
    Path path;

    int half_width = width / 2;
    int half_length = length / 2;

    path << IntPoint(-half_width + center.X, half_length + center.Y)
        << IntPoint(-half_width + center.X, -half_length + center.Y)
        << IntPoint(half_width + center.X, -half_length + center.Y)
        << IntPoint(half_width + center.X, half_length + center.Y);

    return path;
}

// Generate a square using Clipper libraries
Path ModernBuilding::randomSquare(IntPoint center, int width) {
    Path path;

    int half_width = width / 2;

    path << IntPoint(-half_width + center.X, half_width + center.Y)
        << IntPoint(-half_width + center.X, -half_width + center.Y)
        << IntPoint(half_width + center.X, -half_width + center.Y)
        << IntPoint(half_width + center.X, half_width + center.Y);

    return path;
}

// Render the top or "roof" of  building
void ModernBuilding::renderTop() {
    glColor3fv(black);
    glNormal3f(0, 1, 0);
    if(clipType == ctUnion){
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(center1.X, height, center1.Y);
        for(int i = 0; i < one.size(); i++){
            glVertex3f(one[i].X, height, one[i].Y);
        }
        glVertex3f(one[0].X, height, one[0].Y);
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(center2.X, height, center2.Y);
        for(int i = 0; i < two.size(); i++){
            glVertex3f(two[i].X, height, two[i].Y);
        }
        glVertex3f(two[0].X, height, two[0].Y);
        glEnd();
    } else if(clipType == ctIntersection){
        for(auto sh : shape) {
            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i < sh.size(); i++) {
                glVertex3f(sh[i].X, height, sh[i].Y);
            }
            glEnd();
        }
    }
}

// Render a square base
void ModernBuilding::renderBase() {
    glColor3f(0.1, 0.1, 0.1);
    renderCube(width, length, 2);
}
