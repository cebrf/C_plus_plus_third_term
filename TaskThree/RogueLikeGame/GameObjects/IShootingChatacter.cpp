#include "IShootingChatacter.h"

IShootingChatacter::IShootingChatacter(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage) :
    ICharacter(pos, sym, hp, damage, maxHp), shootingDamage(shootingDamage) { };

IShootingChatacter::~IShootingChatacter() = default;

void IShootingChatacter::SetShootingDamage(int shootingDamage)
{
    this->shootingDamage = shootingDamage;
}

int IShootingChatacter::GetShootingDamage()
{
    return this->shootingDamage;
}