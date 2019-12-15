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