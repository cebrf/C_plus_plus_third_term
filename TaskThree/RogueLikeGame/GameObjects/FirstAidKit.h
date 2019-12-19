#pragma once
#include "IGameObject.h"
#include "ICharacter.h"
#include "Player.h"
#include "Bullet.h"
#include "FirstAidKit.h"
#include "ShootingEnemy.h"

class FirstAidKit :
    public IGameObject
{
public:
    FirstAidKit(Point pos, char sym, int healingForce);
    ~FirstAidKit();
    
    void SetHealingForce(int healingForce);
    int GetHealingForce();

    char GetMove(WINDOW*& win) override;

    bool Collide(IGameObject&) override;
    bool collideWith(Player&) override;
    bool collideWith(Enemy&) override;
    bool collideWith(Bullet&) override;
    bool collideWith(ShootingEnemy&) override;
    bool collideWith(FirstAidKit&) override;

protected:

private:
    int healingForce;
};

