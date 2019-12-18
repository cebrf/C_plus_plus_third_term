#pragma once
#include "../pdcurses/curses.h"
#include "IShootingChatacter.h"

class Player :
    public IShootingChatacter
{
public:
    Player();
    Player(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage);
    ~Player();

    char GetMove(WINDOW* win) override;

protected:

private:
};

