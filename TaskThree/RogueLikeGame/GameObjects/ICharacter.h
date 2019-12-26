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
    int GetXp();
    int GetMaxHp();
    int GetDamage();

    void SetHp(int);
    void SetXp(int);
    void SetMaxHp(int);
    void SetDamage(int);

    void SetShootingDamage(int);
    int GetShootingDamage();
 
protected:
    ICharacter(Point, char, int, int, int, int, int = 0);
    ~ICharacter();

private:
    int hp;
    int xp;
    int maxHp;
    int damage;
    int shootingDamage;

};
