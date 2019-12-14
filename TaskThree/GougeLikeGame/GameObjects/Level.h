#pragma once
#include <string>
#include <vector>
#include <map>
#include "ICharacter.h"
#include "Player.h"
#include "../pdcurses/curses.h"

class Level
{
public:
    static void GetLevelMap(const std::string& fileName, std::vector<std::string>& levelMap);

    static void GetEnemiesTypes(const std::string& EnemiesFileName, std::map<char, ICharacter*> enemiesTypes);

    static void FindGameObjects(const std::vector<std::string>& levelMap,
        std::map<std::pair<int, int>, ICharacter*>& enemies,
        const std::map<char, ICharacter*>& enemiesTypes,
        Player& player);

    static void PrintLevel(WINDOW *& win, const std::vector<std::string>& levelMap);

    static void CreateWindow(WINDOW*& win);
};

