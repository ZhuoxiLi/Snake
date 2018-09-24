#include "Text.h"
#include <sstream>

Text::Text(int x, int y, string s, int snum)
        : x(x), y(y), s(s), snum(snum) {}

void Text::paint(XInfo &xinfo) {
    XDrawImageString(xinfo.display, xinfo.window, xinfo.gc,
                     this->x, this->y, this->s.c_str(),
                     static_cast<int>(this->s.length()));
}

void Text::setNum(int num) {
    s = static_cast<ostringstream *>(&(ostringstream() << num))->str();
    snum = num;
}

int Text::getNum() {
    return snum;
}