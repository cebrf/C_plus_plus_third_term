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
    Point GetPos();
    char GetSym();

protected:
    IGameObject(Point pos, char sym);
    ~IGameObject();

    void SetPos(Point p);
    void SetSym(char sym);

private:
    Point pos;
    char sym;
};

