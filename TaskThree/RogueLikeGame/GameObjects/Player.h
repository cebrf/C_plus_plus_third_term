#pragma once
#include "../pdcurses/curses.h"
#include "IShootingCharacter.h"
#include "ShootingEnemy.h"
#include "Bullet.h"
#include "Enemy.h"
#include <algorithm>
#include "FirstAidKit.h"
#include "Level.h"

class Player :
    public IShootingCharacter
{
public:
    Player();
    Player(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage);
    ~Player();

    char GetAction(WINDOW& win) override;

    void Collide(IGameObject&, Level&) override;
    void collideWith(Player&, Level&) override;
    void collideWith(Enemy&, Level&) override;
    void collideWith(Bullet&, Level&) override;
    void collideWith(ShootingEnemy&, Level&) override;
    void collideWith(FirstAidKit&, Level&) override;

    void Update(Level& level) override;

protected:

private:
};

