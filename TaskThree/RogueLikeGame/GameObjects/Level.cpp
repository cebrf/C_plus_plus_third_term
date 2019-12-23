#include "Level.h"

Level::Level(const std::string& fileName)
{
    std::ifstream MapFile(fileName);
    std::string buf;
    while (std::getline(MapFile, buf)) {
        levelMap.push_back(buf);
    }
}

void Level::GetCharactersTypes(const std::string& EnemiesFileName)
{
    std::fstream f(EnemiesFileName);
    json j;
    f >> j;
    
    std::string symP = j["player"]["sym"];
    player = std::shared_ptr<Player>(new Player());
    player->SetSym(symP[0]);
    player->SetHp(j["player"]["hp"]);
    player->SetDamage(j["player"]["damage"]);
    player->SetMaxHp(j["player"]["maxHp"]);
    player->SetShootingDamage(j["player"]["shootingDamage"]);

    std::string symT = j["trophy"]["sym"];
    trophy = std::shared_ptr<Trophy>(new Trophy(Point(-1, -1), symT[0]));

    std::string symF = j["firstAidKit"]["sym"];
    firstAidKitType = std::shared_ptr<FirstAidKit>(new FirstAidKit(Point(-1, -1), symF[0], j["firstAidKit"]["healingForce"]));

    for (auto& enemy : j["enemies"].items())
    {
        std::string symE = enemy.value()["sym"];
        if (enemy.value()["shootingDamage"] > 0)
            enemiesTypes.emplace(symE[0], std::shared_ptr<ICharacter>(new ShootingEnemy(Point(-1, -1), symE[0],
                enemy.value()["hp"], enemy.value()["damage"], enemy.value()["maxHp"], enemy.value()["shootingDamage"])));
        else
            enemiesTypes.emplace(symE[0], std::shared_ptr<ICharacter>(new Enemy(Point(-1, -1), symE[0],
                enemy.value()["hp"], enemy.value()["damage"], enemy.value()["maxHp"])));
    }
}

void Level::FindGameObjects()
{
    for (int i = 0; i < levelMap.size(); i++)
    {
        for (int j = 0; j < levelMap[i].size(); j++)
        {
            if (levelMap[i][j] == player->GetSym())
            {
                player->SetPos(Point(i + 1, j + 1));
                continue;
            }
            if (levelMap[i][j] == trophy->GetSym())
            {
                trophy->SetPos(Point(i + 1, j + 1));
                continue;
            }
            if (levelMap[i][j] == firstAidKitType->GetSym())
            {
                firstAidKits.emplace(Point(i + 1, j + 1), std::shared_ptr<FirstAidKit>(new FirstAidKit(Point(i + 1, j + 1),
                    firstAidKitType->GetSym(), firstAidKitType->GetHealingForce())));
                continue;
            }
            if (enemiesTypes.find(levelMap[i][j]) != enemiesTypes.end())
            {
                std::shared_ptr<ICharacter> enemy = enemiesTypes.find(levelMap[i][j])->second;
                if (enemy->GetShootingDamage() > 0)
                    enemiesContainer.push_back(std::shared_ptr<ICharacter>(new ShootingEnemy(Point(i + 1, j + 1),
                        levelMap[i][j], enemy->GetHp(), enemy->GetDamage(), enemy->GetMaxHp(), enemy->GetShootingDamage())));
                else
                    enemiesContainer.push_back(std::shared_ptr<ICharacter>(new Enemy(Point(i + 1, j + 1),
                        levelMap[i][j], enemy->GetHp(), enemy->GetDamage(), enemy->GetMaxHp())));
            }
        }
    }

    for (int i = 0; i < enemiesContainer.size(); i++)
    {
        enemies.emplace(enemiesContainer[i]->GetPos(), enemiesContainer[i]);
    }
    /*for (int i = 0; i < firstAidKitsContainer.size(); i++)
    {
        firstAidKits.emplace(firstAidKitsContainer[i]->GetPos(), firstAidKitsContainer[i]);
    }*/
}

void Level::PrintLevel()
{
    for (int i = 0; i < levelMap.size(); i++)
    {
        wmove(&*levelWin, i + 1, 1);
        for (int j = 0; j < levelMap[i].size(); j++)
        {
            if (std::abs(player->GetPos().x - i - 1) <= 4 && std::abs(player->GetPos().y - j - 1) <= 8)
            {
                switch (levelMap[i][j])
                {
                case '+':
                    wattron(&*levelWin, COLOR_PAIR(3));
                    waddch(&*levelWin, levelMap[i][j]);
                    wattroff(&*levelWin, COLOR_PAIR(3));
                    break;
                case '#':
                    wattron(&*levelWin, COLOR_PAIR(5));
                    waddch(&*levelWin, levelMap[i][j]);
                    wattroff(&*levelWin, COLOR_PAIR(5));
                    break;
                case '@':
                    wattron(&*levelWin, COLOR_PAIR(1));
                    waddch(&*levelWin, levelMap[i][j]);
                    wattroff(&*levelWin, COLOR_PAIR(1));
                    break;
                case '<':
                case '>':
                case 'v':
                case '^':
                    waddch(&*levelWin, levelMap[i][j]);
                    break;
                case '$':
                    wattron(&*levelWin, COLOR_PAIR(6));
                    waddch(&*levelWin, levelMap[i][j]);
                    wattroff(&*levelWin, COLOR_PAIR(6));
                    break;
                default:
                    wattron(&*levelWin, COLOR_PAIR(2));
                    waddch(&*levelWin, levelMap[i][j]);
                    wattroff(&*levelWin, COLOR_PAIR(2));
                    break;
                }
            }
            else
            {
                //wattron(&*levelWin, COLOR_PAIR(4));
                waddch(&*levelWin, '?');
                //wattroff(&*levelWin, COLOR_PAIR(4));
            }
        }
    }
    wrefresh(&*levelWin);
}

void Level::CreateWindow(size_t widthOfMap, size_t heightOfMap)
{
    initscr();
    curs_set(0);
    noecho();

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);

    int height = heightOfMap + 2,
        width = widthOfMap + 2,
        startX = 10,
        startY = 10;
    levelWin = std::shared_ptr<WINDOW>(newwin(height, width, startX, startY));

    nodelay(&*levelWin, true);
    cbreak();

    box(&*levelWin, 0, 0);
    wmove(&*levelWin, 1, 1);
    wrefresh(&*levelWin);
}

void Level::CreateWPlayerStatus()
{
    playerStatus = std::shared_ptr<WINDOW>(newwin(20, 20, 10, 130));
    nodelay(&*playerStatus, true);
    box(&*playerStatus, 0, 0);
    wrefresh(&*playerStatus);
}

void Level::PrintPLayerStatus()
{
    mvwprintw(&*playerStatus, 2, 5, "%s%d", "Hp:  ", player->GetHp());
    wrefresh(&*playerStatus);
}

void Level::SetObj(Point pos, char obj)
{
    levelMap[pos.x - 1][pos.y - 1] = obj;
    //mvwaddch(&*levelWin, pos.x, pos.y, obj);
}

std::shared_ptr<IGameObject> Level::GetObj(Point pos)
{
    if (trophy->GetPos().x == pos.x && trophy->GetPos().y == pos.y)
        return trophy;
    if (player->GetPos().x == pos.x && player->GetPos().y == pos.y)
        return player;
    if (enemies.find(pos) != enemies.end())
        return enemies.find(pos)->second;
    if (firstAidKits.find(pos) != firstAidKits.end())
        return firstAidKits.find(pos)->second;
    if (bullets.find(pos) != bullets.end())
        return bullets.find(pos)->second;
}

char Level::GetSym(Point pos)
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

void Level::EscMenu()
{
    wclear(&*playerStatus);
    box(&*playerStatus, 0, 0);
    wrefresh(&*playerStatus);

    int height, width;
    getmaxyx(&*playerStatus, height, width);
    keypad(&*playerStatus, true);
    mvwprintw(&*playerStatus, 3, width / 2 - 3, "Pause");
    std::vector<std::string> choices = { "Resume", "Save", "Load", "Exit" };
    int choice;
    int highlight = 0;

    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (i == highlight)
                wattron(&*playerStatus, A_REVERSE);
            mvwprintw(&*playerStatus, i * 2 + 8, width / 2 - choices[i].size() / 2, choices[i].c_str());
            wattroff(&*playerStatus, A_REVERSE);
        }
        choice = wgetch(&*playerStatus);
        switch (choice)
        {
        case KEY_UP:
            highlight = std::max(0, highlight - 1);
            break;
        case KEY_DOWN:
            highlight = std::min(3, highlight + 1);
            break;
        }
        if (choice == 10)
            break;
    }
    if (highlight == 0)
    {
        wclear(&*playerStatus);
        PrintPLayerStatus();
        box(&*playerStatus, 0, 0);
        wrefresh(&*playerStatus);
        return;
    }
    if (highlight == 3)
    {
        needExit = 1;
        return;
    }
}