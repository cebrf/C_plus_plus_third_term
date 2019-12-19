#include "IShootingCharacter.h"

IShootingCharacter::IShootingCharacter(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage) :
    ICharacter(pos, sym, hp, damage, maxHp), shootingDamage(shootingDamage) { };

IShootingCharacter::~IShootingCharacter() = default;

void IShootingCharacter::SetShootingDamage(int shootingDamage)
{
    this->shootingDamage = shootingDamage;
}

int IShootingCharacter::GetShootingDamage()
{
    return this->shootingDamage;
}