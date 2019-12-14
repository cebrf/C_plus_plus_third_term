#pragma once
#include <string>
#include <vector>
#include <map>
#include "pdcurses/curses.h"

#include "GameObjects/ICharacter.h"
#include "GameObjects/Player.h"
#include "GameObjects/Level.h"

class GameSystem
{
public:
    GameSystem(const std::string& levelFileName, const std::string& EnemiesFileName);

    void Start();

protected:
    void makeMove(int directionX, int directionY);

private:
    std::vector<std::string> levelMap;
    std::map<std::pair<int, int>, ICharacter*> enemies;
    std::map<char, ICharacter*> enemiesTypes;
    Player player;
    WINDOW* levelWin;
};
