#pragma once
#include "ICharacter.h"

class IShootingChatacter :
    public ICharacter
{
public:
    void SetShootingDamage(int shootingDamage);
    int GetShootingDamage();
    
protected:
    IShootingChatacter(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage);
    ~IShootingChatacter();

    //bool/void shoot(direction)

private:
    int shootingDamage;
};