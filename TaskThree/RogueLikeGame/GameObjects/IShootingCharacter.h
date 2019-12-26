#pragma once
#include "ICharacter.h"
#include <vector>

class IShootingCharacter :
    public ICharacter
{
public:

protected:
    IShootingCharacter(Point, char, int, int, int, int, int);
    ~IShootingCharacter();


private:
};