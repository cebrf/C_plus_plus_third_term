#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <io.h>
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
    GameSystem();
    void Start(int, int = 0, int = 0);
    int GetGameStatus();
    int GetLevelNum();

protected:

private:
    void Play();
    Level level;
};
