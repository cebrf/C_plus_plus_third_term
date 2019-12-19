#include "FirstAidKit.h"

FirstAidKit::FirstAidKit(Point pos, char sym, int healingForce) :
    IGameObject(pos, sym), healingForce(healingForce) { }

FirstAidKit::~FirstAidKit() = default;

char FirstAidKit::GetMove(WINDOW*& win)
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

bool FirstAidKit::Collide(IGameObject& other)
{
    return other.collideWith(*this);
}

bool FirstAidKit::collideWith(Player& player)
{
    this->SetSym(' ');
    player.SetHp(std::min(player.GetMaxHp(), player.GetHp() + this->GetHealingForce()));
    return 0;
}

bool FirstAidKit::collideWith(Enemy& enemy)
{
    return 0;
}

bool FirstAidKit::collideWith(Bullet& bullet)
{
    return 0;
}

bool FirstAidKit::collideWith(ShootingEnemy& shootingEnemy)
{
    return 0;
}

bool FirstAidKit::collideWith(FirstAidKit& firstAidKit)
{
    return 0;
}