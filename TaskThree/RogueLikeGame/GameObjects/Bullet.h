#pragma once
#include <algorithm>
#include "IGameObject.h"
#include "ICharacter.h"
#include "Enemy.h"
#include "Player.h"
#include "FirstAidKit.h"
#include "ShootingEnemy.h"
#include "Level.h"

class Bullet :
    public IGameObject
{
public:
    Bullet(Point, Point, int);
    ~Bullet();

    void SetDirection(Point);
    Point GetDirection();
    int GetDamage();

    char GetAction(WINDOW&) override;

    void Collide(IGameObject&, Level&) override;
    void collideWith(Player&, Level&) override;
    void collideWith(Enemy&, Level&) override;
    void collideWith(Bullet&, Level&) override;
    void collideWith(ShootingEnemy&, Level&) override;
    void collideWith(FirstAidKit&, Level&) override;

    void Update(Level&) override;

protected:

private:
    Point direction;
    int damage;
};

