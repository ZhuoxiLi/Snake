#ifndef A1_DISPLAYABLE_H
#define A1_DISPLAYABLE_H

#include <X11/Xlib.h>

/*
 * Information to draw on the window.
 */
struct XInfo {
    //Drawable d;
    Display *display;
    int screen;
    Window window;
    GC gc;
    int width;        // size of window
    int height;
};

#define SNACK_START_X 100
#define SNACK_START_Y 450
#define BLOCK_WIDTH 10


/*
 * An abstract class representing Displayable things.
 */
class Displayable {
public:
    virtual void paint(XInfo &xinfo) = 0;
};

#endif //A1_DISPLAYABLE_H
