#include "Level.h"

Level::Level(const std::string& fileName)
{
    std::ifstream MapFile(fileName);
    std::string buf;
    while (std::getline(MapFile, buf)) {
        levelMap.push_back(buf);
    }
}

void Level::GetCharactersTypes(const std::string& EnemiesFileName, Player& player)
{
    std::fstream f(EnemiesFileName);
    json j;
    f >> j;
    
    std::string sym = j["player"]["sym"];
    player.SetSym(sym[0]);
    player.SetHp(j["player"]["hp"]);
    player.SetDamage(j["player"]["damage"]);
    player.SetMaxHp(j["player"]["maxHp"]);
    player.SetShootingDamage(j["player"]["shootingDamage"]);

    for (auto& enemy : j["enemies"].items())
    {
        std::string sym = enemy.value()["sym"];
        if (enemy.value()["shootingDamage"] > 0)
            enemiesTypes.emplace(sym[0], std::shared_ptr<ICharacter>(new ShootingEnemy(Point(-1, -1), sym[0],
                enemy.value()["hp"], enemy.value()["damage"], enemy.value()["maxHp"], enemy.value()["shootingDamage"])));
        else
            enemiesTypes.emplace(sym[0], std::shared_ptr<ICharacter>(new Enemy(Point(-1, -1), sym[0],
                enemy.value()["hp"], enemy.value()["damage"], enemy.value()["maxHp"])));
    }
}

void Level::FindGameObjects(Player& player)
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
            case '+':
                firstAidKits.push_back(FirstAidKit(Point(i + 1, j + 1), '+', 5));
            default:
                if (enemiesTypes.find(levelMap[i][j]) != enemiesTypes.end())
                {
                    std::shared_ptr<ICharacter> enemy = enemiesTypes.find(levelMap[i][j])->second;
                    if (enemy->GetShootingDamage() > 0)
                        enemies.push_back(std::shared_ptr<ICharacter>(new ShootingEnemy(Point(i + 1, j + 1),
                            levelMap[i][j], enemy->GetHp(), enemy->GetDamage(), enemy->GetMaxHp(), enemy->GetShootingDamage())));
                    else
                        enemies.push_back(std::shared_ptr<ICharacter>(new Enemy(Point(i + 1, j + 1),
                            levelMap[i][j], enemy->GetHp(), enemy->GetDamage(), enemy->GetMaxHp())));
                }
                break;
            }
        }
    }
}

void Level::PrintLevel(WINDOW*& win)
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

    nodelay(levelWin, true);
    //noqiflush(); //raw();  //cbreak();

    box(levelWin, 0, 0);
    wmove(levelWin, 1, 1);
    wrefresh(levelWin);
}

void Level::CreateWPlayerStatus(WINDOW*& win)
{
    win = newwin(20, 20, 10, 130);
    nodelay(win, true);
    box(win, 0, 0);
    wrefresh(win);
}

void Level::PrintPLayerStatus(WINDOW*& win, int hp)
{
    mvwprintw(win, 2, 5, "%s%d", "Hp:  ", hp);
    wrefresh(win);
}

void Level::SetObj(WINDOW*& win, Point pos, char obj)
{
    levelMap[pos.x - 1][pos.y - 1] = obj;
    mvwaddch(win, pos.x, pos.y, obj);
}

char Level::GetObj(Point pos)
{
    return levelMap[pos.x - 1][pos.y - 1];
}

int Level::GetWidth()
{
    return levelMap[0].size();
}

int Level::GetHeight()
{
    return levelMap.size();
}