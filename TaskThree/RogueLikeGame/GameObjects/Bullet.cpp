#include "Bullet.h"


Bullet::Bullet(Point pos, Point direction) :
    IGameObject(pos, ' '), direction(direction) 
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

char Bullet::GetMove(WINDOW*& win)
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

bool Bullet::Collide(IGameObject& other)
{
    return other.collideWith(*this);
}

bool Bullet::collideWith(Player& player)
{
    return 0;
}

bool Bullet::collideWith(Enemy& enemy)
{
    return 0;
}

bool Bullet::collideWith(Bullet& bullet)
{
    return 0;
}