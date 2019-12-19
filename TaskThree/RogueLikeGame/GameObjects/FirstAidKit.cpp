#include "FirstAidKit.h"

FirstAidKit::FirstAidKit(Point pos, char sym, int healingForce) :
    IGameObject(pos, sym), healingForce(healingForce) { }

FirstAidKit::~FirstAidKit() = default;

void FirstAidKit::SetHealingForce(int healingForce)
{
    this->healingForce = healingForce;
}

int FirstAidKit::GetHealingForce()
{
    return healingForce;
}