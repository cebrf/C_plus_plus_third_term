#pragma once
#include "IShootingCharacter.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "FirstAidKit.h"

class ShootingEnemy :
    public IShootingCharacter
{
public:
    ShootingEnemy(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage);
    ~ShootingEnemy();

    char GetMove(WINDOW*& win) override;

    bool Collide(IGameObject&) override;
    bool collideWith(Player&) override;
    bool collideWith(Enemy&) override;
    bool collideWith(Bullet&) override;
    bool collideWith(ShootingEnemy&) override;
    bool collideWith(FirstAidKit&) override;
protected:

private:
};

