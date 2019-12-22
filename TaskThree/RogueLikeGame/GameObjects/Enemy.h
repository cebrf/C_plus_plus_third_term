#pragma once
#include "ICharacter.h"
#include "Player.h"
#include "Bullet.h"
#include "Level.h"
#include "FirstAidKit.h"
#include "ShootingEnemy.h"
#include "../pdcurses/curses.h"
#include <vector>

class Enemy :
    public ICharacter
{
public:
    Enemy(Point, char, int, int, int);
    ~Enemy();

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
};

