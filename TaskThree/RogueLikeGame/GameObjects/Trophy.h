#pragma once
#include "IGameObject.h"
#include "ICharacter.h"
#include "Player.h"
#include "Bullet.h"
#include "FirstAidKit.h"
#include "ShootingEnemy.h"
#include "Level.h"

class Trophy :
    public IGameObject
{
public:
    Trophy(Point, char);
    ~Trophy();

    char GetAction(WINDOW&) override;

    void Collide(IGameObject&, Level&) override;
    void collideWith(Player&, Level&) override;
    void collideWith(Enemy&, Level&) override;
    void collideWith(Bullet&, Level&) override;
    void collideWith(ShootingEnemy&, Level&) override;
    void collideWith(FirstAidKit&, Level&) override;
    void collideWith(Trophy&, Level&) override;

    void Update(Level&) override;

protected:

private:

};
