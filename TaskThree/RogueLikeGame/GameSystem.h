#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>
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
    bool Attack(ICharacter* attacker, ICharacter* prey);

private:
    std::vector<std::string> levelMap;
    std::map<std::pair<int, int>, Enemy> enemies;
    std::map<char, Enemy> enemiesTypes;
    //map with items
    //map with arrows
    Player player;
    WINDOW* levelWin;
};
