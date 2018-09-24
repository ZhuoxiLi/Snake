#ifndef A1_FRUIT_H
#define A1_FRUIT_H

#include "Displayable.h"
#include "Block.h"
#include <list>

using std::list;

class Fruit : public Displayable {
public:
    virtual void paint(XInfo &xinfo);

    Fruit();

    int getColor();
    int getX();
    int getY();
    void newPosition(list<Block *> obs, list<Block *> body);

private:
    int x;
    int y;
    int color;
};


#endif //A1_FRUIT_H
