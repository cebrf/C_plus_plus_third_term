#include "FirstAidKit.h"

FirstAidKit::FirstAidKit(Point pos, char sym, int healingForce) :
    IGameObject(pos, sym), healingForce(healingForce) { }

FirstAidKit::~FirstAidKit() = default;

char FirstAidKit::GetAction(WINDOW& win)
{
    return ' ';
}

void FirstAidKit::SetHealingForce(int healingForce)
{
    this->healingForce = healingForce;
}

int FirstAidKit::GetHealingForce()
{
    return healingForce;
}

void FirstAidKit::Collide(IGameObject& other, Level& level)
{
    other.collideWith(*this, level);
}

void FirstAidKit::collideWith(Player& player, Level& level)
{
    return player.collideWith(*this, level);
}

void FirstAidKit::collideWith(Enemy& enemy, Level& level)
{
    return enemy.collideWith(*this, level);
}

void FirstAidKit::collideWith(Bullet& bullet, Level& level)
{
    return bullet.collideWith(*this, level);
}

void FirstAidKit::collideWith(ShootingEnemy& shootingEnemy, Level& level)
{
    return shootingEnemy.collideWith(*this, level);
}

void FirstAidKit::collideWith(FirstAidKit& firstAidKit, Level& level)
{
    return firstAidKit.collideWith(*this, level);
}

void FirstAidKit::collideWith(Trophy& trophy, Level& level) { }

void FirstAidKit::Update(Level& level) { }