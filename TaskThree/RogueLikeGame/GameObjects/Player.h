#pragma once

#include "IShootingChatacter.h"

class Player :
    public IShootingChatacter
{
public:
    Player(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage);
    ~Player();

protected:

private:
};

