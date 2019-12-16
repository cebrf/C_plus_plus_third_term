#include "Level.h"

void Level::GetLevelMap(const std::string& fileName, std::vector<std::string>& levelMap)
{
    std::ifstream MapFile(fileName);
    std::string buf;
    while (std::getline(MapFile, buf)) {
        levelMap.push_back(buf);
    }
}

void Level::GetCharactersTypes(const std::string& EnemiesFileName, std::map<char, Enemy>& enemiesTypes, Player& player)
{
    std::fstream f(EnemiesFileName);
    json j;
    f >> j;
    
    std::string sym = j["player"]["sym"];
    player.SetSym(sym[0]);
    player.SetHp(j["player"]["hp"]);
    player.SetDamage(j["player"]["damage"]);
    player.SetMaxHp(j["player"]["maxHp"]);

    for (auto& enemy : j["enemies"].items())
    {
        std::string sym = enemy.value()["sym"];
        enemiesTypes.emplace(sym[0],
            Enemy(Point(-1, -1), sym[0], enemy.value()["hp"], enemy.value()["damage"], enemy.value()["maxHp"]));
    }
}

void Level::FindGameObjects(const std::vector<std::string>& levelMap,
    std::vector<std::shared_ptr<ICharacter>>& enemies,
    const std::map<char, Enemy>& enemiesTypes,
    Player& player)
{
    for (int i = 0; i < levelMap.size(); i++)
    {
        for (int j = 0; j < levelMap[i].size(); j++)
        {
            switch (levelMap[i][j])
            {
            case '@':
                player.SetPos(Point(i + 1, j + 1));
                break;
            default:
                if (enemiesTypes.find(levelMap[i][j]) != enemiesTypes.end())
                {
                    Enemy enemy = enemiesTypes.find(levelMap[i][j])->second;
                    enemies.push_back(std::shared_ptr<ICharacter>(new Enemy(Point(i + 1, j + 1),
                        levelMap[i][j], enemy.GetHp(), enemy.GetDamage(), enemy.GetMaxHp())));
                }
                break;
            }
        }
    }
}

void Level::PrintLevel(WINDOW*& win, const std::vector<std::string>& levelMap)
{
    for (int i = 0; i < levelMap.size(); i++)
    {
        wmove(win, i + 1, 1);
        for (int j = 0; j < levelMap[i].size(); j++)
        {
            waddch(win, levelMap[i][j]);
        }
    }
    wrefresh(win);
}

void Level::CreateWindow(WINDOW*& levelWin, size_t widthOfMap, size_t heightOfMap)
{
    initscr();
    curs_set(0);
    noecho();
    int height = heightOfMap + 2,
        width = widthOfMap + 2,
        startX = 10,
        startY = 10;
    levelWin = newwin(height, width, startX, startY);
    box(levelWin, 0, 0);
    wmove(levelWin, 1, 1);
    wrefresh(levelWin);
}