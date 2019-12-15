#include "Player.h"

Player::Player(Point pos, char sym, int hp, int damage, int maxHp) :
    IShootingChatacter(pos, sym, hp, damage, maxHp) { };

Player::~Player() = default;

