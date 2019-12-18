#pragma once
#include "ICharacter.h"
#include <vector>

class Enemy :
    public ICharacter
{
public:
    Enemy(Point pos, char sym, int hp, int damage, int maxHp);
    ~Enemy();

    char GetMove(WINDOW* win) override;
protected:

private:
};

