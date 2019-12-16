#include <iostream>

using namespace std;

#include "GameSystem.h"

int main()
{
    GameSystem game("level1.txt", "enemiesLevel1.json");
    game.Start();

    return 0;
}