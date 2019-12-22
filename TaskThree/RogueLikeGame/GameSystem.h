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
    GameSystem(const std::string& levelFileName, const std::string& EnemiesFileName);
    void Start();

protected:
    void death();  //TODO move to PLayer

private:
    std::function<bool(Point, ICharacter&)> shoot;
    std::function<bool(const std::pair<int, int>, IGameObject&)> makeMove;

    Level level;
};
