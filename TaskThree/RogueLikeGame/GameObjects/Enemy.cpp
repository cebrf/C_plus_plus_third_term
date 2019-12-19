#include "Enemy.h"

Enemy::Enemy(Point pos, char sym, int hp, int damage, int maxHp) :
    ICharacter(pos, sym, hp, damage, maxHp) { };

Enemy::~Enemy() = default;

char Enemy::GetMove(WINDOW*& win)
{
    std::vector<char> v = { 'w', 'a', 's', 'd' };
    return v[rand() % 4];
}

bool Enemy::Collide(IGameObject& other)
{
    return other.collideWith(*this);
}

bool Enemy::collideWith(Enemy& enemy)
{
    enemy.SetHp(std::max(0, enemy.GetHp() - this->GetDamage()));
    if (enemy.GetHp() == 0)
        return 1;
    else
        return 0;
}

bool Enemy::collideWith(Player& player)
{
    player.SetHp(std::max(0, player.GetHp() - this->GetDamage()));
    if (player.GetHp() == 0)
        return 1;       //TODO end of game. Need flag for that!
    else
        return 0;
}

bool Enemy::collideWith(Bullet& bullet)
{
    bullet.SetSym(' ');
    this->SetHp(std::max(0, this->GetHp() - bullet.GetDamage()));
    if (this->GetHp() == 0)
        return 1;
    else
        return 0;
}