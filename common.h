#ifndef A1_COMMON_H
#define A1_COMMON_H


#include <list>
#include <iostream>
#include "Displayable.h"

using std::list;
using std::cerr;
using std::endl;

/*
 * Global game state variables
 */
const int Border = 1;
const int width = 800;
const int height = 600;
list<Displayable *> dList;           // list of Displayables

/*
 * Function to repaint a display list
 */
void repaint(XInfo &xinfo) {
    list<Displayable *>::const_iterator begin = dList.begin();
    list<Displayable *>::const_iterator end = dList.end();

    XClearWindow(xinfo.display, xinfo.window);

    // get height and width of window (might have changed since last repaint)

    XWindowAttributes windowInfo;
    XGetWindowAttributes(xinfo.display, xinfo.window, &windowInfo);
    unsigned int height = windowInfo.height;
    unsigned int width = windowInfo.width;

    // big black rectangle to clear background

    // draw display list
    while (begin != end) {
        Displayable *d = *begin;
        d->paint(xinfo);
        begin++;
    }
    XFlush(xinfo.display);
}

// get microseconds
unsigned long now() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

/*
 * Function to put out a message on error exits.
 */
void error(string str) {
    cerr << str << endl;
    exit(0);
}

#endif //A1_COMMON_H
