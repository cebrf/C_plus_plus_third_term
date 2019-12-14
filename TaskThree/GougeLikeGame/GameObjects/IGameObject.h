//#pragma once
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
    IGameObject(Point pos, char sym);
    ~IGameObject();

protected:
    void SetPos(Point p);
    Point GetPos();
    void SetSym(char sym);
    char GetSym();

private:
    Point pos;
    char sym;
};

