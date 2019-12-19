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
    bool makeMove(const std::pair<int, int> direction, IGameObject& character);
    std::pair<int, int> getDirection(char move, bool& isShoot);
    void death();
    bool shoot(std::pair<int, int> direction, ICharacter& chatacter);

private:
    std::vector<std::shared_ptr<ICharacter>> enemies;
    std::map<char, std::shared_ptr<ICharacter>> enemiesTypes;
    std::vector<FirstAidKit> firstAidKits;
    std::vector<Bullet> bullets;
    
    Player player;
    Level level;
    WINDOW* levelWin;
    WINDOW* playerStatus;
};
