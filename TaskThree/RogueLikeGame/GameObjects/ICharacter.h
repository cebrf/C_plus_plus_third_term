#pragma once
#include "IGameObject.h"
#include <functional>
#include "../pdcurses/curses.h"
#include <algorithm>

class ICharacter :
    public IGameObject
{
public:
    int GetHp();
    int GetMaxHp();
    int GetDamage();

    void SetHp(int hp);
    void SetMaxHp(int maxHp);
    void SetDamage(int damage);

    void SetShootingDamage(int shootingDamage);
    int GetShootingDamage();
 
protected:
    ICharacter(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage = 0);
    ~ICharacter();

private:
    int hp;
    int maxHp;
    int damage;
    int shootingDamage;

};
