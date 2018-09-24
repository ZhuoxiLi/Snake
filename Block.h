#ifndef A1_BLOCK_H
#define A1_BLOCK_H


#include "Displayable.h"

class Block : public Displayable {
public:
    virtual void paint(XInfo &xinfo);

    Block(int x, int y);

    int getX();
    int getY();
    void set_snake_paint();
    void set_obs_white();
    void set_Obs_black();


private:
    int x;
    int y;
    int snake_paint;
    int white;
};


#endif //A1_BLOCK_H
