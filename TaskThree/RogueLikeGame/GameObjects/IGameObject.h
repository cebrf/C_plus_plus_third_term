#pragma once
#include "../pdcurses/curses.h"

struct Point
{
    Point(int x, int y) :
        x(x), y(y) { };

    int x;
    int y;
};

class IGameObject
{
public:
    Point GetPos();
    char GetSym();

    void SetPos(Point p);
    void SetSym(char sym);

    virtual char GetMove(WINDOW *win) = 0;

protected:
    IGameObject(Point pos, char sym);
    ~IGameObject();

private:
    Point pos;
    char sym;
};

