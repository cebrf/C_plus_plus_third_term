#include "Player.h"

Player::Player() :
    IShootingChatacter(Point(-1, -1), ' ', -1, -1, -1, -1) { };

Player::Player(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage) :
    IShootingChatacter(pos, sym, hp, damage, maxHp, shootingDamage) { };

Player::~Player() = default;


char Player::GetMove(WINDOW*& win)
{
    return wgetch(win);
    //flushinp(); // does it work?
}

bool Player::Collide(IGameObject& other)
{
    return other.collideWith(*this);
}

bool Player::collideWith(Player& player)
{
    return 0;
}

bool Player::collideWith(Enemy& enemy)
{
    return 0;
}

bool Player::collideWith(Bullet& bullet)
{
    return 0;
}