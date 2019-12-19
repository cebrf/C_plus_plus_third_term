#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>
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
    bool makeMove(const std::pair<int, int> direction, IGameObject& character); // move !?somewhere?!
    void death();  //TODO move to PLayer
    bool shoot(Point direction, ICharacter& character);  // move to IShootingCaracter

private:
    
    Player player;
    Level level;
    WINDOW* levelWin;
    WINDOW* playerStatus;
};
