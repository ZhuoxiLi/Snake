#include "Block.h"

void Block::paint(XInfo &xinfo) {
    if(snake_paint){
        XFillRectangle(xinfo.display, xinfo.window, xinfo.gc, x+1, y+1, BLOCK_WIDTH - 2, BLOCK_WIDTH - 2);
    }else if(white){
        XFillRectangle(xinfo.display, xinfo.window, xinfo.gc, x+1, y+1, BLOCK_WIDTH - 2, BLOCK_WIDTH - 2);
    }else{
        XFillRectangle(xinfo.display, xinfo.window, xinfo.gc, x, y, BLOCK_WIDTH, BLOCK_WIDTH);
    }

}

Block::Block(int x, int y) : x(x), y(y) {
    snake_paint = 1;
    white = 0;
}

void Block::set_snake_paint(){
    snake_paint = 1;
}

void Block::set_Obs_black() {
    white = 0;
    snake_paint = 0;
}

void Block::set_obs_white() {
    white = 1;
    snake_paint = 0;
}

int Block::getX() {
    return x;
}

int Block::getY() {
    return y;
}
