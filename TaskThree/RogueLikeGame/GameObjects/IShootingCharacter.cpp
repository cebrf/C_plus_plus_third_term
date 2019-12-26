#include "IShootingCharacter.h"

IShootingCharacter::IShootingCharacter(Point pos, char sym, int hp, int xp, int damage, int maxHp, int shootingDamage) :
    ICharacter(pos, sym, hp, xp, damage, maxHp, shootingDamage) { };

IShootingCharacter::~IShootingCharacter() = default;