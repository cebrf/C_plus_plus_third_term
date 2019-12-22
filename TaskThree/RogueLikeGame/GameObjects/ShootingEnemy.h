#pragma once
#include "IShootingCharacter.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "FirstAidKit.h"
#include "Level.h"

class ShootingEnemy :
    public IShootingCharacter
{
public:
    ShootingEnemy(Point, char, int, int, int, int);
    ~ShootingEnemy();

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

