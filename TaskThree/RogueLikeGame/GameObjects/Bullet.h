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

    char GetMove(WINDOW*& win) override;

    bool Collide(IGameObject&) override;
    bool collideWith(Player&) override;
    bool collideWith(Enemy&) override;
    bool collideWith(Bullet&) override;
protected:

private:
    Point direction;

};

