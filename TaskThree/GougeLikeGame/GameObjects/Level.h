#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include "ICharacter.h"
#include "Player.h"
#include "Enemy.h"
#include "../pdcurses/curses.h"

class Level
{
public:
    static void GetLevelMap(const std::string& fileName, std::vector<std::string>& levelMap);

    static void GetEnemiesTypes(const std::string& EnemiesFileName, std::map<char, Enemy>& enemiesTypes);

    static void FindGameObjects(const std::vector<std::string>& levelMap,
        std::map<std::pair<int, int>, Enemy>& enemies,
        const std::map<char, Enemy>& enemiesTypes,
        Player& player);

    static void PrintLevel(WINDOW *& win, const std::vector<std::string>& levelMap);

    static void CreateWindow(WINDOW*& win);
};

