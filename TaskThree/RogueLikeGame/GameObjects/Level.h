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

    void GetCharactersTypes(const std::string& EnemiesFileName);

    void FindGameObjects();

    void PrintLevel(WINDOW *& win);
    void CreateWindow(WINDOW*& win, size_t widthOfMap, size_t heightOfMap);
    void CreateWPlayerStatus(WINDOW*& win);
    void PrintPLayerStatus(WINDOW*& win);

    void SetObj(WINDOW*& win, Point pos, char obj);
    std::shared_ptr<IGameObject> GetObj(Point pos);
    char GetSym(Point pos);
    
    int GetWidth();
    int GetHeight();

    
    std::shared_ptr<Player> player;

    std::map<char, std::shared_ptr<ICharacter>> enemiesTypes;
    std::map<Point, std::shared_ptr<ICharacter>> enemies;
    std::vector<std::shared_ptr<ICharacter>> enemiesContainer;

    std::map<Point, std::shared_ptr<FirstAidKit>> firstAidKits;
    std::vector<std::shared_ptr<FirstAidKit>> firstAidKitsContainer;

    std::map<Point, std::shared_ptr<Bullet>> bullets;
    std::vector<std::shared_ptr<Bullet>> bulletsContainer;

private:
    std::vector<std::string> levelMap;
};

