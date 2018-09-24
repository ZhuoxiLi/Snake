#include <X11/Xlib.h>
#include "Controller.h"
#include "common.h"

Controller::~Controller() {
    snake->clearBlocks();
    snake->clearObs();
    delete scoreNum;
    delete score ;
    delete fps;
    delete fpsNum;
    delete speedDisplay;
    delete speedNum;
    delete snake;
}

void Controller::eventLoop(XInfo xinfo, int frame, int speed, Controller controller) {
    // Add stuff to paint to the display list; fruit at the first place
    dList.push_front(score);
    dList.push_front(scoreNum);
    dList.push_front(fps);
    dList.push_front(fpsNum);
    dList.push_front(speedDisplay);
    dList.push_front(speedNum);
    dList.push_front(snake);
    dList.push_front(fruit);

    XEvent event;
    unsigned long lastRepaint = 0;

    while (true) {
        if (XPending(xinfo.display) > 0) {
            XNextEvent(xinfo.display, &event);
            switch (event.type) {
                case KeyPress:
                    if (controller.handleKeyPress(xinfo, event) == -1) return; // 'q' pressed, quit.
                    break;
            }
        }

        int defaultspeed = 5;
        if (frame) {
            FPS = frame;
            fpsNum->setNum(frame);
        }
        if (speed) {
            defaultspeed = speed;
            speedNum->setNum(speed);
        }
        unsigned long end = now();    // get time in microsecond
        if ((!snake->isBegin())||(!snake->isRestart())) {
            if (end - lastRepaint > 1000000 / FPS) {
                controller.splash(xinfo);
                lastRepaint = now(); // remember when the paint happened
            }
        } else {
            unsigned long time1 = now();
            unsigned long time2 = now();
            if (end - lastRepaint > 1000000 / FPS) {
                while (true) {
                    if (time2 - time1 > (300000 / defaultspeed)) {
                        if ((!snake->isPause())) {
                            controller.handleAnimation(xinfo);
                        }
                        break;
                    }
                    time2 = now();
                }
                repaint(xinfo);
                lastRepaint = now(); // remember when the paint happened
            }

        }

        if (XPending(xinfo.display) == 0) {
            usleep(1000000 / FPS - (end - lastRepaint));
        }
    }
}

void Controller::initX(int argc, char **argv, XInfo &xInfo) {
    XSizeHints hints;
    unsigned long white, black;

    /*
     * Display opening uses the DISPLAY	environment variable.
     * It can go wrong if DISPLAY isn't set, or you don't have permission.
     */
    xInfo.display = XOpenDisplay("");
    if (!xInfo.display) {
        error("Can't open display.");
    }

    /*
     * Find out some things about the display you're using.
     */
    xInfo.screen = DefaultScreen(xInfo.display);

    white = XWhitePixel(xInfo.display, xInfo.screen);
    black = XBlackPixel(xInfo.display, xInfo.screen);

    hints.x = 100;
    hints.y = 100;
    hints.width = width;
    hints.height = height;
    hints.max_height = height;
    hints.max_width= width;
    hints.min_height = height;
    hints.min_width = width;
    hints.flags = PPosition | PSize | PMinSize | PMaxSize;

    xInfo.window = XCreateSimpleWindow(
            xInfo.display,                // display where window appears
            DefaultRootWindow(xInfo.display), // window's parent in window tree
            hints.x, hints.y,            // upper left corner location
            hints.width, hints.height,    // size of the window
            Border,                        // width of window's border
            black,                        // window border colour
            white);                    // window background colour

    XSetStandardProperties(
            xInfo.display,        // display containing the window
            xInfo.window,        // window whose properties are set
            "animation",        // window's title
            "Animate",            // icon's title
            None,                // pixmap for the icon
            argv, argc,            // applications command line args
            &hints);            // size hints for the window

    /*
     * Create Graphics Contexts
     */
    xInfo.gc= XCreateGC(xInfo.display, xInfo.window, 0, 0);
    XSetForeground(xInfo.display, xInfo.gc, BlackPixel(xInfo.display, xInfo.screen));
    XSetBackground(xInfo.display, xInfo.gc, WhitePixel(xInfo.display, xInfo.screen));
    XSetFillStyle(xInfo.display, xInfo.gc, FillSolid);
    XSetLineAttributes(xInfo.display, xInfo.gc,
                       1, LineSolid, CapButt, JoinRound);

    XSelectInput(xInfo.display, xInfo.window,
                 ButtonPressMask | KeyPressMask |
                 PointerMotionMask |
                 EnterWindowMask | LeaveWindowMask |
                 StructureNotifyMask);  // for resize events

    // size font size
    XFontStruct * font;
    font = XLoadQueryFont (xInfo.display, "12x24");
    XSetFont(xInfo.display, xInfo.gc, font->fid);

    /*
     * Put the window on the screen.
     */
    XMapRaised(xInfo.display, xInfo.window);
    XFlush(xInfo.display);
}

void Controller::handleAnimation(XInfo &xinfo) {
    snake->move(xinfo);
}

int Controller::handleKeyPress(XInfo &xinfo, XEvent &event) {
    KeySym key;
    char text[BufferSize];

    XLookupString(
            (XKeyEvent * ) & event,    // the keyboard event
            text,                    // buffer when text will be written
            BufferSize,            // size of the text buffer
            &key,                    // workstation-independent key symbol
            NULL);                    // pointer to a composeStatus structure (unused)


    switch (key) {
        case XK_Up:
            snake->setDy(-1);
            break;
        case XK_Down:
            snake->setDy(1);
            break;
        case XK_Left:
            snake->setDx(-1);
            break;
        case XK_Right:
            snake->setDx(1);
            break;
        case XK_q:
            return -1;// quit
        case XK_w:
            snake->setDy(-1);
            break;
        case XK_s:
            snake->setDy(1);
            break;
        case XK_a:
            snake->setDx(-1);
            break;
        case XK_d:
            snake->setDx(1);
            break;
        case XK_p:
            snake->setPause(1);
            break;
        case XK_c:
            snake->setPause(0);
            break;
        case XK_b:
            snake->begin();
            break;
        case XK_r:
            if (snake->isRestart() != 0) return 0;
            snake->resetSnake();
            break;
    }

    return 0;
}

void Controller::splash(XInfo &xinfo) {
    // get height and width of window (might have changed since last repaint)

    XClearWindow(xinfo.display, xinfo.window);
    XWindowAttributes windowInfo;
    XGetWindowAttributes(xinfo.display, xinfo.window, &windowInfo);
    unsigned int height = windowInfo.height;
    unsigned int width = windowInfo.width;

    // big black rectangle to clear background

    // draw display list
            int unit = 40;
            int five = 5;
    XDrawString(xinfo.display, xinfo.window, xinfo.gc, 390, 100, "Snake", 5);
    if(!snake->isBegin()) {
        XDrawString(xinfo.display, xinfo.window, xinfo.gc, 380, 100+(unit*9), "Zhuoxi Li", 9);
        XDrawString(xinfo.display, xinfo.window, xinfo.gc, 390, 100+(unit*10), "z565li", 6);
        XDrawString(xinfo.display, xinfo.window, xinfo.gc, 330-(3*five), 100+(unit*8), "[b]: Begin Game", 15);
    }

    XDrawString(xinfo.display, xinfo.window, xinfo.gc, 330, 100+unit, "[w]/Up: Go Up", 13);
    XDrawString(xinfo.display, xinfo.window, xinfo.gc, 330-(5*five), 100+(unit*2), "[s]/Down: Go Down", 17);
    XDrawString(xinfo.display, xinfo.window, xinfo.gc, 330-(5*five), 100+(unit*3), "[a]/Left: Go Left", 17);
    XDrawString(xinfo.display, xinfo.window, xinfo.gc, 330-(6*five), 100+(unit*4), "[d]/Right: Go Right", 19);
    XDrawString(xinfo.display, xinfo.window, xinfo.gc, 330-(3*five), 100+(unit*5), "[p]: Pause Game", 15);
    XDrawString(xinfo.display, xinfo.window, xinfo.gc, 330-(5*five), 100+(unit*6), "[c]: Continue Game", 18);
    XDrawString(xinfo.display, xinfo.window, xinfo.gc, 330-(5*five), 100+(unit*7), "[q]: Quit the Game", 18);
    if(snake->isBegin()){
        XDrawString(xinfo.display, xinfo.window, xinfo.gc, 330-(5*five), 100+(unit*8), "[r]: Restart Game", 17);
    }
    XFlush(xinfo.display);
}