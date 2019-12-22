#include "Enemy.h"

Enemy::Enemy(Point pos, char sym, int hp, int damage, int maxHp) :
    ICharacter(pos, sym, hp, damage, maxHp) { };

Enemy::~Enemy() = default;

char Enemy::GetAction(WINDOW*& win)
{
    std::vector<char> v = { 'w', 'a', 's', 'd' };
    return v[rand() % v.size()];
}

void Enemy::Collide(IGameObject& other, Level& level)
{
    other.collideWith(*this, level);
}

void Enemy::collideWith(Enemy& enemy, Level& level)
{
    enemy.SetHp(std::max(0, enemy.GetHp() - this->GetDamage()));
    /*if (enemy.GetHp() == 0)
        return 1;
    else
        return 0;*/
}

void Enemy::collideWith(Player& player, Level& level)
{
    player.SetHp(std::max(0, player.GetHp() - this->GetDamage()));
    /*if (player.GetHp() == 0)
        return 1;       //TODO end of game. Need flag for that!
    else
        return 0;*/
}

void Enemy::collideWith(Bullet& bullet, Level& level)
{
    bullet.SetSym(' ');
    this->SetHp(std::max(0, this->GetHp() - bullet.GetDamage()));
    /*if (this->GetHp() == 0)
        return 1;
    else
        return 0;*/
}

void Enemy::collideWith(ShootingEnemy& shootingEnemy, Level& level)
{
    shootingEnemy.SetHp(std::max(0, shootingEnemy.GetHp() - this->GetDamage()));
    /*if (shootingEnemy.GetHp() == 0)
        return 1;
    else
        return 0;*/
}

void Enemy::collideWith(FirstAidKit& firstAidKit, Level& level)
{
    firstAidKit.SetSym(' ');
    this->SetHp(std::min(this->GetMaxHp(), this->GetHp() + firstAidKit.GetHealingForce()));
}

void Enemy::Update(Level& level)
{

}