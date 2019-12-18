#include "Enemy.h"

Enemy::Enemy(Point pos, char sym, int hp, int damage, int maxHp) :
    ICharacter(pos, sym, hp, damage, maxHp) { };

Enemy::~Enemy() = default;

char Enemy::GetMove(WINDOW* win)
{
    std::vector<char> v = { 'w', 'a', 's', 'd' };
    return v[rand() % 4];
}