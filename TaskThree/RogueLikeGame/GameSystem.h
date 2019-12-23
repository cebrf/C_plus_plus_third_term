#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include "pdcurses/curses.h"

#include "GameObjects/ICharacter.h"
#include "GameObjects/Player.h"
#include "GameObjects/Level.h"
#include "GameObjects/Bullet.h"
#include "GameObjects/FirstAidKit.h"

#include <thread>
#include <chrono>

class GameSystem
{
public:
    GameSystem(const int);
    void Start();
    bool GameStatus = 0;

protected:

private:
    Level level;
};
