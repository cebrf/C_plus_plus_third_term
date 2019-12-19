#pragma once
#include "IGameObject.h"
class FirstAidKit :
    public IGameObject
{
public:
    FirstAidKit(Point pos, char sym, int healingForce);
    ~FirstAidKit();
    
    void SetHealingForce(int healingForce);
    int GetHealingForce();


protected:

private:
    int healingForce;
};

