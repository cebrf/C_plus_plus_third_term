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

bool Player::collideWith(Enemy& enemy)
{
    enemy.SetHp(std::max(0, enemy.GetHp() - this->GetDamage()));
    if (enemy.GetHp() == 0)
        return 1;
    else
        return 0;
}

bool Player::collideWith(Player& player)
{
    // no multiplayer
    return 0;
}

bool Player::collideWith(Bullet& bullet)
{
    bullet.SetSym(' ');

    this->SetHp(std::max(0, this->GetHp() - 10));
    if (this->GetHp() == 0)
        return 1;
    else
        return 0;
}