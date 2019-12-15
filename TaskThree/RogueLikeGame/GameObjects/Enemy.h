#pragma once
#include "ICharacter.h"

class Enemy :
    public ICharacter
{
public:
    Enemy(Point pos, char sym, int hp, int damage, int maxHp);
    ~Enemy();

protected:

private:
};

