#include "IShootingCharacter.h"

IShootingCharacter::IShootingCharacter(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage) :
    ICharacter(pos, sym, hp, damage, maxHp, shootingDamage) { };

IShootingCharacter::~IShootingCharacter() = default;