#pragma once
#include <algorithm>
#include "IGameObject.h"
#include "ICharacter.h"
#include "Enemy.h"
#include "Player.h"

class Bullet :
    public IGameObject
{
public:
    Bullet(Point pos, Point direction, int damage);
    ~Bullet();

    void SetDirection(Point direction);
    Point GetDirection();
    int GetDamage();

    char GetMove(WINDOW*& win) override;

    bool Collide(IGameObject&) override;
    bool collideWith(Player&) override;
    bool collideWith(Enemy&) override;
    bool collideWith(Bullet&) override;
protected:

private:
    Point direction;
    int damage;
};

