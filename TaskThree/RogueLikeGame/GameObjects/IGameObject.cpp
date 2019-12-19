#include "IGameObject.h"

IGameObject::IGameObject(Point pos, char sym) :
    pos(pos), sym(sym) { }

IGameObject::~IGameObject() = default;

void IGameObject::SetPos(Point p)
{
    this->pos.x = p.x;
    this->pos.y = p.y;
}

Point IGameObject::GetPos()
{
    return pos;
}

void IGameObject::SetSym(char sym)
{
    this->sym = sym;
}

char IGameObject::GetSym()
{
    return sym;
}

Point IGameObject::getDirection(char move, bool& isShoot)
{
    if (move == 'j' || move == 'l' || move == 'i' || move == 'k')
        isShoot = 1;

    Point direction(0, 0);
    if (move == 'w' || move == 'i')
        direction.x = -1;
    else if (move == 's' || move == 'k')
        direction.x = 1;
    else if (move == 'a' || move == 'j')
        direction.y = -1;
    else if (move == 'd' || move == 'l')
        direction.y = 1;
    return direction;
}