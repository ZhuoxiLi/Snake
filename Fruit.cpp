#include "Fruit.h"
#include "Snake.h"
#include <cstdlib>
#include <ctime>

void Fruit::paint(XInfo &xinfo) {
    XSetForeground(xinfo.display, xinfo.gc, getColor());
    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc, x+1, y+1, BLOCK_WIDTH - 2, BLOCK_WIDTH - 2);
    XSetForeground(xinfo.display, xinfo.gc, BlackPixel(xinfo.display, xinfo.screen));
}

Fruit::Fruit() {
    srand(time(NULL));
}

int randX() {
    return BLOCK_WIDTH * (rand() % 79);
}

int randY() {
    return BLOCK_WIDTH * (rand() % 51); //510
}

int Fruit::getX() {
    return x;
}

int Fruit::getY() {
    return y;
}

void Fruit::newPosition(list<Block *> obs, list<Block *> body) {
    int r = (rand() % 0x7F + 0x3F) << 16;
    int g = (rand() % 0x7F + 0x3F) << 8;
    int b = (rand() % 0x7F + 0x3F);
    color = r + g + b;

    while (true) {
        x = randX();
        y = randY();

        int conflict = 0;
        for (auto it : obs) {
            if((it->getX() == x) && (it->getY() == y)){
                conflict = 1;
            }
        }
        for (auto it : body) {
            if((it->getX() == x) && (it->getY() == y)){
                conflict = 1;
            }
        }

        if (!conflict) {  //check the new fruit not shows up at snake head
            break;
        }
    }
}

int Fruit::getColor() {
    return color;
}
