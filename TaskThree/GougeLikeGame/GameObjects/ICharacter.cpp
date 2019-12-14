#include "ICharacter.h"

ICharacter::ICharacter(Point pos, char sym, int hp, int damage, int maxHp) :
    IGameObject(pos, sym), hp(hp), damage(damage), maxHp(maxHp) { };

ICharacter::~ICharacter() = default;

int ICharacter::GetHp()
{
    return hp;
}

int ICharacter::GetMaxHp()
{
    return maxHp;
}

int ICharacter::GetDamage()
{
    return damage;
}

void ICharacter::SetHp(int hp)
{
    this->hp = hp;
}

void ICharacter::SetMaxHp(int maxHp)
{
    this->maxHp = maxHp;
}

void ICharacter::SetDamage(int damage)
{
    this->damage = damage;
}