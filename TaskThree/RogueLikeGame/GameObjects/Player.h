#pragma once
#include "../pdcurses/curses.h"
#include "IShootingCharacter.h"

#include "Bullet.h"
#include "Enemy.h"


class Player :
    public IShootingCharacter
{
public:
    Player();
    Player(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage);
    ~Player();

    char GetMove(WINDOW*& win) override;

    bool Collide(IGameObject&) override;
    bool collideWith(Player&) override;
    bool collideWith(Enemy&) override;
    bool collideWith(Bullet&) override;
protected:

private:
};

