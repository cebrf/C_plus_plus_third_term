#pragma once
#include "IGameObject.h"
class Bullet :
    public IGameObject
{
public:
    Bullet(Point pos, Point direction);
    ~Bullet();

    void SetDirection(Point direction);
    Point GetDirection();

protected:

private:
    Point direction;

};

