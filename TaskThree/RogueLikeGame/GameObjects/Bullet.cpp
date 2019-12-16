#include "Bullet.h"


Bullet::Bullet(Point pos, Point direction) :
    IGameObject(pos, ' '), direction(direction) 
{
    if (direction.x == 1)
        this->SetSym('|');
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