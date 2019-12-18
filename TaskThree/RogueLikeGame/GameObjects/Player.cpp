#include "Player.h"

Player::Player(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage) :
    IShootingChatacter(pos, sym, hp, damage, maxHp, shootingDamage){ };

Player::~Player() = default;


char Player::GetMove(WINDOW* win)
{
    return wgetch(win);
}