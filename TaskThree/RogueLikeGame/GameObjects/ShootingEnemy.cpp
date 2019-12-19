#include "ShootingEnemy.h"

ShootingEnemy::ShootingEnemy(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage) :
    IShootingCharacter(pos, sym, hp, damage, maxHp, shootingDamage) { };

ShootingEnemy::~ShootingEnemy() = default;


char ShootingEnemy::GetMove(WINDOW * &win)
{
    std::vector<char> v = { 'w', 'a', 's', 'd', 'i', 'j', 'k', 'l', 'w', 'a', 's', 'd', 'w', 'a', 's', 'd', 'w', 'a', 's', 'd' };
    return v[rand() % v.size()];
}

bool ShootingEnemy::Collide(IGameObject & other)
{
    return other.collideWith(*this);
}

bool ShootingEnemy::collideWith(Enemy & enemy)
{
    enemy.SetHp(std::max(0, enemy.GetHp() - this->GetDamage()));
    if (enemy.GetHp() == 0)
        return 1;
    else
        return 0;
}

bool ShootingEnemy::collideWith(Player & player)
{
    player.SetHp(std::max(0, player.GetHp() - this->GetDamage()));
    if (player.GetHp() == 0)
        return 1;       //TODO end of game. Need flag for that!
    else
        return 0;
}

bool ShootingEnemy::collideWith(Bullet & bullet)
{
    bullet.SetSym(' ');
    this->SetHp(std::max(0, this->GetHp() - bullet.GetDamage()));
    if (this->GetHp() == 0)
        return 1;
    else
        return 0;
}

bool ShootingEnemy::collideWith(ShootingEnemy& shootingEnemy)
{
    shootingEnemy.SetHp(std::max(0, shootingEnemy.GetHp() - this->GetDamage()));
    if (shootingEnemy.GetHp() == 0)
        return 1;
    else
        return 0;
}