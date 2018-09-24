#include "Snake.h"
#include <cmath>
#include <cstdio>
#include <string>

#include <iostream>
using namespace std;

int getColorDelta(int color, int size) {
    int red = (color >> 16) & 0xff;
    int green = (color >> 8) & 0xff;
    int blue = (color >> 0) & 0xff;

    int rdelta = (0xff - red) / size;
    int gdelta = (0xff - green) / size;
    int bdelta = (0xff - blue) / size;

    int r = (rdelta << 16) & 0xff0000;
    int g = (gdelta << 8) & 0x00ff00;
    int b = bdelta & 0x0000ff;
    return r + g + b;
}

void Snake::paint(XInfo &xinfo) {
    int delta = getColorDelta(color, (int)body.size());
    int count = 0;
    for (auto it : body) {
        XSetForeground(xinfo.display, xinfo.gc, color + count * delta);
        it->set_snake_paint();
        it->paint(xinfo);
        count+=1;
    }

    XSetForeground(xinfo.display, xinfo.gc, 0);
    for (auto it : obstacles) {
        it->set_Obs_black();
        it->paint(xinfo);
    }

    XSetForeground(xinfo.display, xinfo.gc, WhitePixel(xinfo.display, xinfo.screen));
    for (auto it : obstacles) {
        it->set_obs_white();
        it->paint(xinfo);
    }
    XSetForeground(xinfo.display, xinfo.gc, BlackPixel(xinfo.display, xinfo.screen));
}

void Snake::move(XInfo &xinfo) {
    int eat = 0;
    int newX = (body.front()->getX()) + BLOCK_WIDTH * dx;
    int newY = (body.front()->getY()) + BLOCK_WIDTH * dy;

    if (isDead(newX, newY)) {
        return;
    }

    wrap(newX, newY);

    if (newX == fruit->getX() && newY == fruit->getY()) {
        eat = 1;
        scoreNum->setNum(scoreNum->getNum() + 1);
        color = fruit->getColor();
        fruit->newPosition(obstacles, body);
    }

    stepFront(newX, newY, eat);
}

int Snake::checkFailStatus() {
    return !beginGame || !restart || makePause;
}

void Snake::setDy(int dy) {
    if (checkFailStatus()) return;
    if(this->dy != (-dy)) {
        this->dy = dy;
        dx = 0;
    }
}

void Snake::setDx(int dx) {
    if (checkFailStatus()) return;
    if(this->dx != (-dx)) {
        this->dx = dx;
        dy = 0;
    }
}

Snake::Snake(int x, int y, Fruit *pFruit, Text *pScoreNum) : x(x), y(y), fruit(pFruit), scoreNum(pScoreNum) {
    resetSnake();
    bulidObstacles();
    pFruit->newPosition(obstacles, body);
}

void Snake::bulidObstacles(){
    //left & right obstacles
    for(int i = 0; i <= (200 / BLOCK_WIDTH) - 1; i++){
        obstacles.push_front(new Block(0, i * BLOCK_WIDTH));
        obstacles.push_front(new Block(0, (i + (400/BLOCK_WIDTH)) * BLOCK_WIDTH));
        obstacles.push_front(new Block(800 - BLOCK_WIDTH, i * BLOCK_WIDTH));
        obstacles.push_front(new Block(800 - BLOCK_WIDTH, (i + (400/BLOCK_WIDTH)) * BLOCK_WIDTH));
    }

    //up & down obstacles
    for(int i = 0; i <= (400 / BLOCK_WIDTH) - 1; i++){
        obstacles.push_front(new Block((20 + i) * BLOCK_WIDTH, 0));
        obstacles.push_front(new Block((20 + i) * BLOCK_WIDTH, 600 - BLOCK_WIDTH));
    }

    //central obstacle
    for(int i = 0; i <= (200 / BLOCK_WIDTH) - 1; i++){
        obstacles.push_front(new Block((30 + i) * BLOCK_WIDTH, (20 + i) * BLOCK_WIDTH));
    }
}


void Snake::clearBlocks() {
    body.clear();
}

void Snake::resetSnake() {
    restart = 1;

    scoreNum->setNum(0);
    dx = -1;
    dy = 0;

    clearBlocks();
    // make 5 block as initialize snake body
    for (int i = 4; i >= 0; i--) {
        body.push_front(new Block(x + BLOCK_WIDTH * i, y));
    }

    fruit->newPosition(obstacles, body);
    color = 0;
}

int Snake::isPause() {
    return makePause;
}

void Snake::setPause(int pause) {
    makePause = pause;
}

int Snake::isBegin() {
    return beginGame;
}

void Snake::begin() {
    beginGame = 1;
}

int Snake::isRestart() {
    return restart;
}

void Snake::stepFront(int newX, int newY, int eat) {
    Block *b = new Block(newX, newY);
    body.push_front(b);

    if (!eat) {
        body.pop_back();
    }
}

void Snake::wrap(int &newX, int &newY){
    if ((newX < 0) || (newX > 790) || (newY < 0) || (newY > 590)) {
        if(dx == 0){
            if(newY < 0){
                newY += 600;
            }else{
                newY -= 600;
            }

        }else{
            if(newX < 0){
                newX += 800;
            }else{
                newX -= 800;
            }
        }

    }
}

bool Snake::isDead(int newX, int newY) {
    // check boundaries
    for (auto it : obstacles) {
        if (it->getX() == newX && it->getY() == newY) {
            restart = 0;
            return true;
        }
    }
    // check self hitting
    for (auto it : body) {
        if (it->getX() == newX && it->getY() == newY) {
            restart = 0;
            return true;
        }
    }
}

list<Block *> Snake::get_obs() {
    return obstacles;
}

list<Block *> Snake::get_body() {
    return obstacles;
}

void Snake::clearObs() {
    obstacles.clear();
}

