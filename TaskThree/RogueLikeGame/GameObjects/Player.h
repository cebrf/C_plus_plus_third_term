#pragma once
#include "../pdcurses/curses.h"
#include "IShootingChatacter.h"

#include "Bullet.h"
#include "Enemy.h"


class Player :
    public IShootingChatacter
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

