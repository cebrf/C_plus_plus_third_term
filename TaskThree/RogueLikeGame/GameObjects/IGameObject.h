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

    void SetPos(Point p);
    void SetSym(char sym);

    virtual char GetAction(WINDOW*& win) = 0;

    virtual void Collide(IGameObject&, Level& level) = 0;
    virtual void collideWith(Player&, Level& level) = 0;
    virtual void collideWith(Enemy&, Level& level) = 0;
    virtual void collideWith(Bullet&, Level& level) = 0;
    virtual void collideWith(ShootingEnemy&, Level& level) = 0;
    virtual void collideWith(FirstAidKit&, Level& level) = 0;

    virtual void Update(Level& level) = 0;

    Point getDirection(char move, bool& isShoot);

    std::function<bool(const std::pair<int, int>, IGameObject&)> makeMove
        = [](const std::pair<int, int> direction, IGameObject& character) { return 0; };

protected:

    IGameObject(Point pos, char sym);
    ~IGameObject();

private:
    Point pos;
    char sym;
};

