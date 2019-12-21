#pragma once
#include "ICharacter.h"
#include <vector>

class IShootingCharacter :
    public ICharacter
{
public:
    // labmda Shoot

protected:
    IShootingCharacter(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage);
    ~IShootingCharacter();


private:
};