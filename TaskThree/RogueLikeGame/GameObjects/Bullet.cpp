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

char Bullet::GetAction(WINDOW& win)
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
    enemy.collideWith(*this, level);
}

void Bullet::collideWith(Player& player, Level& level)
{
    player.collideWith(*this, level);
}

void Bullet::collideWith(Bullet& bullet, Level& level)
{
    level.SetObj(bullet.GetPos(), ' ');
    level.bullets.erase(bullet.GetPos());
    level.SetObj(this->GetPos(), ' ');
    level.bullets.erase(this->GetPos());
}

void Bullet::collideWith(ShootingEnemy& shootingEnemy, Level& level)
{
    shootingEnemy.collideWith(*this, level);
}

void Bullet::collideWith(FirstAidKit& firstAidKit, Level& level)
{
    level.SetObj(this->GetPos(), ' ');
    level.bullets.erase(this->GetPos());
}

void Bullet::collideWith(Trophy& trophy, Level& level)
{
    level.SetObj(this->GetPos(), ' ');
    level.bullets.erase(this->GetPos());
}

void Bullet::Update(Level& level)
{
    Point newPos(this->GetPos().x + direction.x, this->GetPos().y + direction.y);

    if (newPos.x <= 0 || newPos.y <= 0 || newPos.x - 1 >= level.GetHeight() ||
        newPos.y >= level.GetWidth() || level.GetSym(newPos) == '#')
    {
        level.SetObj(this->GetPos(), ' ');
        level.bullets.erase(this->GetPos());
        return;
    }

    if (level.GetSym(newPos) == ' ' && level.GetSym(newPos) == ' ')
    {
        level.bullets.emplace(newPos, level.bullets.find(this->GetPos())->second);
        level.SetObj(this->GetPos(), ' ');
        level.bullets.erase(this->GetPos());
        this->SetPos(newPos);
        level.SetObj(this->GetPos(), this->GetSym());
    }
    else
    {
        std::shared_ptr<IGameObject> obj = level.GetObj(newPos);
        obj->Collide(*this, level);
    }
}