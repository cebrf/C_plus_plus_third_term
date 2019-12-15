#pragma once
#include "IGameObject.h"

class ICharacter :
    public IGameObject
{
public:
    int GetHp();
    int GetMaxHp();
    int GetDamage();

    void SetHp(int hp);
    void SetMaxHp(int maxHp);
    void SetDamage(int damage);

    //virtual bool Attack(ICharacter* other) = 0;

protected:
    ICharacter(Point pos, char sym, int hp, int damage, int maxHp);
    ~ICharacter();

private:
    int hp;
    int maxHp;
    int damage;
};
