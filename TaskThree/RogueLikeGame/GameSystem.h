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
    void makeMove(const std::pair<int, int> direction, ICharacter* character);
    char getRandomMove();
    std::pair<int, int> getDirection(char move);

private:
    std::vector<std::string> levelMap;
    std::map<std::pair<int, int>, Enemy> enemies;
    std::map<char, Enemy> enemiesTypes;
    Player player;
    WINDOW* levelWin;
};
