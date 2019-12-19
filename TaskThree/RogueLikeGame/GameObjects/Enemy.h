#pragma once
#include "ICharacter.h"
#include "Player.h"
#include "Bullet.h"
#include "FirstAidKit.h"
#include "ShootingEnemy.h"
#include <vector>

class Enemy :
    public ICharacter
{
public:
    Enemy(Point pos, char sym, int hp, int damage, int maxHp);
    ~Enemy();

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

