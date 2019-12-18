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

#include <thread>
#include <chrono>

class GameSystem
{
public:
    GameSystem(const std::string& levelFileName, const std::string& EnemiesFileName);

    void Start();

protected:
    void makeMove(const std::pair<int, int> direction, ICharacter& character);
    std::pair<int, int> getDirection(char move, bool& isShoot);
    bool Attack(ICharacter& attacker, ICharacter& prey);
    void death();
    void shoot(std::pair<int, int> direction);

private:
    std::vector<std::shared_ptr<ICharacter>> enemies;
    std::map<char, Enemy> enemiesTypes;
    //map with items
    std::vector<Bullet> bullets;
    
    Player player;
    Level level;
    WINDOW* levelWin;
};
