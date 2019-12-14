//#pragma once

#include "IShootingChatacter.h"

class Player :
    public IShootingChatacter
{
public:
    Player();
    Player(Point pos, char sym, int hp, int damage, int maxHp);
    ~Player();

protected:

private:
};

