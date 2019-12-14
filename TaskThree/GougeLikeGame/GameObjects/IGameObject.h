#pragma once
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
    void SetPos(Point p); // TODO move to protexted

protected:
    IGameObject(Point pos, char sym);
    ~IGameObject();

    void SetSym(char sym);

private:
    Point pos;
    char sym;
};

