#include "IShootingChatacter.h"

IShootingChatacter::IShootingChatacter(Point pos, char sym, int hp, int damage, int maxHp) :
    ICharacter(pos, sym, hp, damage, maxHp) { };

IShootingChatacter::~IShootingChatacter() = default;