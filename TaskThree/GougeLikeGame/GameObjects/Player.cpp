#include "Player.h"

/*Player::Player() :
    IShootingChatacter(Point(-1, -1), '@', 100, 20, 100) { };*/

Player::Player(Point pos, char sym, int hp, int damage, int maxHp) :
    IShootingChatacter(pos, sym, hp, damage, maxHp) { };

Player::~Player() = default;

