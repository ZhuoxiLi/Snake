/*
CS 349 A1 Skeleton Code - Snake

- - - - - - - - - - - - - - - - - - - - - -

Commands to compile and run:

    g++ -o snake snake.cpp -L/usr/X11R6/lib -lX11 -lstdc++
    ./snake

Note: the -L option and -lstdc++ may not be needed on some machines.
*/



/*
 * Header files for X functions
 */
#include <X11/Xutil.h>

#include "Controller.h"

/*
 * Start executing here.
 *	 First initialize window.
 *	 Next loop responding to events.
 *	 Exit forcing window manager to clean up - cheesy, but easy.
 */
int main(int argc, char *argv[]) {
    XInfo xInfo;
    Controller c;
    c.initX(argc, argv, xInfo);

    if (argc != 1) {
        c.eventLoop(xInfo, atoi(argv[1]), atoi(argv[2]), c);
    } else {
        c.eventLoop(xInfo, 0, 0, c);
    }

    XCloseDisplay(xInfo.display);
}
