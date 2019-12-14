//#pragma once
#include "ICharacter.h"

class IShootingChatacter :
    public ICharacter
{
public:
    
protected:
    IShootingChatacter(Point pos, char sym, int hp, int damage, int maxHp);
    ~IShootingChatacter();

    //shoot
    //Get/SetShootingDamage
private:
    //ShootingDamage
};