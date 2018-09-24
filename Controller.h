#ifndef A1_CONTROLLER_H
#define A1_CONTROLLER_H


#include <X11/Xutil.h>
#include "Fruit.h"
#include "Text.h"
#include "Snake.h"

class Controller {
public:
    /*
     * Initialize X and create a window
     */
    void initX(int argc, char *argv[], XInfo &xInfo);

    void eventLoop(XInfo xinfo, int frame, int speed, Controller controller);

    ~Controller();
private:
    Fruit *fruit = new Fruit();
    Text *scoreNum = new Text(120, 580, "0", 0);
    Text *score = new Text(30, 580, "Score:", 0);
    Text *fps = new Text (650, 550, "FPS:", 0);
    Text *fpsNum = new Text (740, 550, "30", 30);
    Text *speedDisplay = new Text (650, 580, "Speed:", 0);
    Text *speedNum = new Text (740, 580, "5", 5);
    Snake *snake = new Snake(SNACK_START_X, SNACK_START_Y, fruit, scoreNum);
    const int BufferSize = 10;
    int FPS = 30;


    void handleAnimation(XInfo &xinfo);
    int handleKeyPress(XInfo &xinfo, XEvent &event);
    void splash(XInfo &xinfo);
};


#endif //A1_CONTROLLER_H
