#include "Bullet.h"


Bullet::Bullet(Point pos, Point direction, int damage) :
    IGameObject(pos, ' '), direction(direction), damage(damage)
{
    if (direction.x == 1)
        this->SetSym('v');
    else if (direction.y == 1)
        this->SetSym('>');
    else if (direction.x == -1)
        this->SetSym('^');
    else if (direction.y == -1)
        this->SetSym('<');
}

Bullet::~Bullet() = default;

void Bullet::SetDirection(Point direction)
{
    this->direction = direction;
}

Point Bullet::GetDirection()
{
    return direction;
}

int Bullet::GetDamage()
{
    return damage;
}

char Bullet::GetAction(WINDOW*& win)
{
    if (direction.x == 1)
        return 's';
    if (direction.y == 1)
        return 'd';
    if (direction.x == -1)
        return 'w';
    if (direction.y == -1)
        return 'a';
}

void Bullet::Collide(IGameObject& other, Level& level)
{
    other.collideWith(*this, level);
}

void Bullet::collideWith(Enemy& enemy, Level& level)
{
    this->SetSym(' ');
    enemy.SetHp(std::max(0, enemy.GetHp() - this->GetDamage()));
    /*if (enemy.GetHp() == 0)
        return 1;
    else
        return 0;*/
}

void Bullet::collideWith(Player& player, Level& level)
{
    this->SetSym(' ');
    player.SetHp(std::max(0, player.GetHp() - this->GetDamage()));
    /*if (player.GetHp() == 0)
        return 1;       //TODO end of game
    else
        return 0;*/
}

void Bullet::collideWith(Bullet& bullet, Level& level)
{
    bullet.SetSym(' ');
    this->SetSym(' ');
    /*return 0;*/
}

void Bullet::collideWith(ShootingEnemy& shootingEnemy, Level& level)
{
    this->SetSym(' ');
    shootingEnemy.SetHp(std::max(0, shootingEnemy.GetHp() - this->GetDamage()));
    /*if (shootingEnemy.GetHp() == 0)
        return 1;
    else
        return 0;*/
}

void Bullet::collideWith(FirstAidKit& firstAidKit, Level& level)
{
    this->SetSym(' ');
    //return 0;
}

void Bullet::Update(Level& level)
{

}