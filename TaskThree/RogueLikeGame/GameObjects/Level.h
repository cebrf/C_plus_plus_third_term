#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

#include "ICharacter.h"
#include "Player.h"
#include "FirstAidKit.h"
#include "ShootingEnemy.h"
#include "Enemy.h"
#include "../pdcurses/curses.h"
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

class Level
{
public:
    Level(const std::string& fileName);

    void GetCharactersTypes(const std::string& EnemiesFileName, std::map<char, std::shared_ptr<ICharacter>>& enemiesTypes, Player& player);

    void FindGameObjects(std::vector<std::shared_ptr<ICharacter>>& enemies,
        const std::map<char, std::shared_ptr<ICharacter>>& enemiesTypes,
        Player& player, std::vector<FirstAidKit>& firstAidKits);

    void PrintLevel(WINDOW *& win);
    void CreateWindow(WINDOW*& win, size_t widthOfMap, size_t heightOfMap);
    void CreateWPlayerStatus(WINDOW*& win);
    void PrintPLayerStatus(WINDOW*& win, int hp);

    void SetObj(WINDOW*& win, Point pos, char obj);
    char GetObj(Point pos);
    
    int GetWidth();
    int GetHeight();

protected:


private:
    std::vector<std::string> levelMap;
};

