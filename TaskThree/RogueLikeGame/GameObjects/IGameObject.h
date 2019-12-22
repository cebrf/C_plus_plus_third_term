#pragma once
#include "../pdcurses/curses.h"
#include <functional>

class Player;
class Enemy;
class Bullet;
class ShootingEnemy;
class FirstAidKit;
class Level;

struct Point
{
    Point(int x, int y) :
        x(x), y(y) { };

    int x;
    int y;

    bool operator <(const Point& rhs) const
    {
        if (this->x == rhs.x)
            return this->y < rhs.y;
        return this->x < rhs.x;
    }
};

class IGameObject
{
public:
    Point GetPos();
    char GetSym();

    void SetPos(Point);
    void SetSym(char);

    virtual char GetAction(WINDOW&) = 0;

    virtual void Collide(IGameObject&, Level&) = 0;
    virtual void collideWith(Player&, Level&) = 0;
    virtual void collideWith(Enemy&, Level&) = 0;
    virtual void collideWith(Bullet&, Level&) = 0;
    virtual void collideWith(ShootingEnemy&, Level&) = 0;
    virtual void collideWith(FirstAidKit&, Level&) = 0;

    virtual void Update(Level&) = 0;

    Point getDirection(char, bool&);

    std::function<bool(const std::pair<int, int>, IGameObject&)> makeMove
        = [](const std::pair<int, int>, IGameObject&) { return 0; };

protected:

    IGameObject(Point, char);
    ~IGameObject();

private:
    Point pos;
    char sym;
};

