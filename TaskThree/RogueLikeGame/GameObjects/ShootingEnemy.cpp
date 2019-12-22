#include "ShootingEnemy.h"

ShootingEnemy::ShootingEnemy(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage) :
    IShootingCharacter(pos, sym, hp, damage, maxHp, shootingDamage) { };

ShootingEnemy::~ShootingEnemy() = default;


char ShootingEnemy::GetAction(WINDOW * &win)
{
    std::vector<char> v = { 'w', 'a', 's', 'd', 'i', 'j', 'k', 'l', 'w', 'a', 's', 'd', 'w', 'a', 's', 'd', 'w', 'a', 's', 'd' };
    return v[rand() % v.size()];
}

void ShootingEnemy::Collide(IGameObject & other, Level& level)
{
    other.collideWith(*this, level);
}

void ShootingEnemy::collideWith(Enemy & enemy, Level& level)
{
    enemy.SetHp(std::max(0, enemy.GetHp() - this->GetDamage()));
    /*if (enemy.GetHp() == 0)
        return 1;
    else
        return 0;*/
}

void ShootingEnemy::collideWith(Player & player, Level& level)
{
    player.SetHp(std::max(0, player.GetHp() - this->GetDamage()));
    /*if (player.GetHp() == 0)
        return 1;       //TODO end of game. Need flag for that!
    else
        return 0;*/
}

void ShootingEnemy::collideWith(Bullet & bullet, Level& level)
{
    bullet.SetSym(' ');
    this->SetHp(std::max(0, this->GetHp() - bullet.GetDamage()));
    /*if (this->GetHp() == 0)
        return 1;
    else
        return 0;*/
}

void ShootingEnemy::collideWith(ShootingEnemy& shootingEnemy, Level& level)
{
    shootingEnemy.SetHp(std::max(0, shootingEnemy.GetHp() - this->GetDamage()));
    /*if (shootingEnemy.GetHp() == 0)
        return 1;
    else
        return 0;*/
}

void ShootingEnemy::collideWith(FirstAidKit& firstAidKit, Level& level)
{
    firstAidKit.SetSym(' ');
    this->SetHp(std::min(this->GetMaxHp(), this->GetHp() + firstAidKit.GetHealingForce()));
    //return 0;
}

void ShootingEnemy::Update(Level& level)
{

}