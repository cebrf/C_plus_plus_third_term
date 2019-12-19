#pragma once
#include "../pdcurses/curses.h"

class Player;
class Enemy;
class Bullet;
class ShootingEnemy;
class FirstAidKit;

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

    virtual char GetMove(WINDOW*& win) = 0;

    virtual bool Collide(IGameObject&) = 0;
    virtual bool collideWith(Player&) = 0;
    virtual bool collideWith(Enemy&) = 0;
    virtual bool collideWith(Bullet&) = 0;
    virtual bool collideWith(ShootingEnemy&) = 0;
    virtual bool collideWith(FirstAidKit&) = 0;

    Point getDirection(char move, bool& isShoot);

protected:

    IGameObject(Point pos, char sym);
    ~IGameObject();

private:
    Point pos;
    char sym;
};

