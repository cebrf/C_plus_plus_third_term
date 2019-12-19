#pragma once
#include "ICharacter.h"
#include <vector>

class IShootingChatacter :
    public ICharacter
{
public:
    void SetShootingDamage(int shootingDamage);
    int GetShootingDamage();

protected:
    IShootingChatacter(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage);
    ~IShootingChatacter();


private:
    int shootingDamage;
};