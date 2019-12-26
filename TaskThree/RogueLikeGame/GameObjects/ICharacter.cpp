#include "ICharacter.h"

ICharacter::ICharacter(Point pos, char sym, int hp, int xp, int damage, int maxHp, int shootingDamage) :
    IGameObject(pos, sym), hp(hp), xp(xp), damage(damage), maxHp(maxHp), shootingDamage(shootingDamage) { };

ICharacter::~ICharacter() = default;

int ICharacter::GetHp()
{
    return hp;
}

int ICharacter::GetXp()
{
    return xp;
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

void ICharacter::SetXp(int xp)
{
    this->xp = xp;
}

void ICharacter::SetMaxHp(int maxHp)
{
    this->maxHp = maxHp;
}

void ICharacter::SetDamage(int damage)
{
    this->damage = damage;
}

void ICharacter::SetShootingDamage(int shootingDamage)
{
    this->shootingDamage = shootingDamage;
}

int ICharacter::GetShootingDamage()
{
    return this->shootingDamage;
}