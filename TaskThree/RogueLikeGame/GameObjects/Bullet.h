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
    Bullet(Point pos, Point direction, int damage);
    ~Bullet();

    void SetDirection(Point direction);
    Point GetDirection();
    int GetDamage();

    char GetAction(WINDOW& win) override;

    void Collide(IGameObject&, Level& level) override;
    void collideWith(Player&, Level& level) override;
    void collideWith(Enemy&, Level& level) override;
    void collideWith(Bullet&, Level& level) override;
    void collideWith(ShootingEnemy&, Level& level) override;
    void collideWith(FirstAidKit&, Level& level) override;

    void Update(Level& level) override;

protected:

private:
    Point direction;
    int damage;
};

