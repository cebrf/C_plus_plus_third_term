#include "Level.h"

void Level::GetLevelMap(const std::string& fileName, std::vector<std::string>& levelMap)
{
    std::ifstream MapFile(fileName);
    std::string buf;
    while (std::getline(MapFile, buf)) {
        levelMap.push_back(buf);
    }
}

void Level::GetEnemiesTypes(const std::string& EnemiesFileName, std::map<char, Enemy>& enemiesTypes)
{
    // TODO read info about player from that file
    std::fstream f(EnemiesFileName);
    json j;
    f >> j;
    for (auto& enemy : j["enemies"].items())
    {
        std::string sym = enemy.value()["sym"];
        enemiesTypes.emplace(sym[0],
            Enemy(Point(-1, -1), sym[0], enemy.value()["hp"], enemy.value()["damage"], enemy.value()["maxHp"]));
    }
}

void Level::FindGameObjects(const std::vector<std::string>& levelMap,
    std::map<std::pair<int, int>, Enemy>& enemies,
    const std::map<char, Enemy>& enemiesTypes,
    Player& player)
{
    //finding objects and pushing them in vectors

    for (int i = 0; i < levelMap.size(); i++)
    {
        for (int j = 0; j < levelMap[i].size(); j++)
        {
            switch (levelMap[i][j])
            {
            case '@':
                //how to set pos, if method if protected?
                player.SetPos(Point(i + 1, j + 1));
                break;
            default:
                if (enemiesTypes.find(levelMap[i][j]) != enemiesTypes.end())
                {
                    auto enemy = enemiesTypes.find(levelMap[i][j]);
                    enemies.insert({ {i, j}, Enemy(Point(i+1, j + 1), 'z', 50, 10, 50) });
                    //enemies[{i, j}] = new Enemy(Point(i, j), levelMap[i][j], enemy->second.GetHp(), enemy->second.GetDamage(), enemy->second.GetMaxHp());
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

void Level::CreateWindow(WINDOW*& levelWin)
{
    initscr();
    curs_set(0);
    noecho();
    int height = 12 + 2,
        width = 30 + 2,
        startX = 10,
        startY = 10;
    levelWin = newwin(height, width, startX, startY);
    box(levelWin, 0, 0);
    wmove(levelWin, 1, 1);
    wrefresh(levelWin);
}