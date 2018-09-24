#ifndef A1_TEXT_H
#define A1_TEXT_H

#include <string>
#include "Displayable.h"

using std::string;
using std::ostringstream;
using std::stringstream;

//from slide: draw string
class Text : public Displayable {
public:
    Text(int x, int y, string s, int snum);

    void setNum(int num);
    int getNum();
    virtual void paint(XInfo &xinfo);

private:
    int x;
    int y;
    string s;
    int snum;  //same as string s
};

#endif //A1_TEXT_H
