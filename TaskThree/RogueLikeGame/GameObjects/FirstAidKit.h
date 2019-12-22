#pragma once
#include "IGameObject.h"
#include "ICharacter.h"
#include "Player.h"
#include "Bullet.h"
#include "FirstAidKit.h"
#include "ShootingEnemy.h"
#include "Level.h"

class FirstAidKit :
    public IGameObject
{
public:
    FirstAidKit(Point pos, char sym, int healingForce);
    ~FirstAidKit();
    
    void SetHealingForce(int healingForce);
    int GetHealingForce();

    char GetAction(WINDOW*& win) override;

    void Collide(IGameObject&, Level&) override;
    void collideWith(Player&, Level&) override;
    void collideWith(Enemy&, Level&) override;
    void collideWith(Bullet&, Level&) override;
    void collideWith(ShootingEnemy&, Level&) override;
    void collideWith(FirstAidKit&, Level&) override;

    void Update(Level& level) override;

protected:

private:
    int healingForce;
};

