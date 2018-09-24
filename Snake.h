#ifndef A1_SNAKE_H
#define A1_SNAKE_H


#include "Block.h"
#include "Fruit.h"
#include "Text.h"
#include <list>
#include <sys/time.h>
#include <unistd.h>

using std::list;

class Snake : public Displayable {
public:
    virtual void paint(XInfo &xinfo);

    void move(XInfo &xinfo);

//    void newPosition(int newX, int newY);

    void setDy(int dy);

    void setDx(int dx);

    Snake(int x, int y, Fruit *pFruit, Text *pScoreNum);

    void bulidObstacles();

    void clearBlocks();

    void resetSnake();

    void clearObs();

    int isPause();

    void setPause(int pause);

    int isBegin();

    void begin();

    int isRestart();

    list<Block *> get_body();

    list<Block *> get_obs();

private:
    //x, y are coordinates when initialize
    int x;
    int y;
    //dx,dy could be 1(right), -1(left), 0(not move)
    int dx;
    int dy;
    list<Block *> body;
    list<Block *> obstacles;

    int color = 0;
    int makePause = 0;        //0 for playing, 1 for pause
    int beginGame = 0;            //0 before the first round, 1 after
    int restart = 1;          //1 at first first, set to 0 when died
    Fruit *fruit;
    Text *scoreNum;

    void stepFront(int newX, int newY, int eat);

    void wrap(int &newX, int &newY);

    bool isDead(int newX, int newY);

    int checkFailStatus();
};


#endif //A1_SNAKE_H
