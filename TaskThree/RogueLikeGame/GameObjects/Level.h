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
#include "Trophy.h"
#include "../pdcurses/curses.h"
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

class Level
{
public:
    Level();

    void GetCharactersTypes(const int);
    void ReadMap(const int);
    void FindGameObjects();
    void PrintLevel();
    void CreateWindow(size_t, size_t);
    void CreateWPlayerStatus();
    void PrintPLayerStatus();
    void NextLevel();

    void SetObj(Point, char);
    std::shared_ptr<IGameObject> GetObj(Point);
    char GetSym(Point);
    
    int GetWidth();
    int GetHeight();

    std::vector<std::string> levelMap;
    std::shared_ptr<WINDOW> levelWin;
    std::shared_ptr<WINDOW> playerStatus;
    
    std::shared_ptr<Player> player;
    std::shared_ptr<Trophy> trophy;
    std::shared_ptr<FirstAidKit> firstAidKitType;

    std::map<char, std::shared_ptr<ICharacter>> enemiesTypes;
    std::map<Point, std::shared_ptr<ICharacter>> enemies;
    std::vector<std::shared_ptr<ICharacter>> enemiesContainer;

    std::map<Point, std::shared_ptr<FirstAidKit>> firstAidKits;

    std::map<Point, std::shared_ptr<Bullet>> bullets;
    std::vector<std::shared_ptr<Bullet>> bulletsContainer;

    std::map<char, int> colours;

    void EscMenu();

    int levelNumber;
    int levelStatus;

private:
    std::string levelName;
};

