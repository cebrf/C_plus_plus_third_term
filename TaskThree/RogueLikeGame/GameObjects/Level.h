#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

#include "ICharacter.h"
#include "Player.h"
#include "Enemy.h"
#include "../pdcurses/curses.h"
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

class Level
{
public:
    static void GetLevelMap(const std::string& fileName, std::vector<std::string>& levelMap);

    static void GetCharactersTypes(const std::string& EnemiesFileName, std::map<char, Enemy>& enemiesTypes, Player& player);

    static void FindGameObjects(const std::vector<std::string>& levelMap,
        std::vector<std::shared_ptr<ICharacter>>& enemies,
        const std::map<char, Enemy>& enemiesTypes,
        Player& player);

    static void PrintLevel(WINDOW *& win, const std::vector<std::string>& levelMap);

    static void CreateWindow(WINDOW*& win, size_t widthOfMap, size_t heightOfMap);
};

