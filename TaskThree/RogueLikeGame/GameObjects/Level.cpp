#include "Level.h"

Level::Level() :
    levelNumber(0),
    levelStatus(0),
    trophy(std::make_shared<Trophy>(Point(-1, -1), ' ')),
    player(std::make_shared<Player>()),
    firstAidKitType(std::make_shared<FirstAidKit>(Point(-1, -1), ' ', -1)) { }

void Level::ReadMap(int levelNumber)
{
    std::string fileName = "level" + std::to_string(levelNumber) + ".txt";
    std::ifstream MapFile(fileName);
    std::string buf;
    std::getline(MapFile, levelName);
    while (std::getline(MapFile, buf)) {
        levelMap.push_back(buf);
    }
}

void Level::GetCharactersTypes(const int levelNumber)
{
    std::string fileName = "enemiesLevel" + std::to_string(levelNumber) + ".json";
    std::fstream f(fileName);
    json j;
    f >> j;
    
    std::string symP = j["player"]["sym"];
    player->SetSym(symP[0]);
    if (levelNumber == 1)
    {
        player->SetHp(j["player"]["hp"]);
        player->SetXp(0);
    }
    player->SetDamage(j["player"]["damage"]);
    player->SetMaxHp(j["player"]["maxHp"]);
    player->SetShootingDamage(j["player"]["shootingDamage"]);
    colours.emplace(symP[0], j["player"]["colour"]);

    std::string symT = j["trophy"]["sym"];
    colours.emplace(symT[0], j["trophy"]["colour"]);
    trophy->SetSym(symT[0]);

    std::string symF = j["firstAidKit"]["sym"];
    colours.emplace(symF[0], j["firstAidKit"]["colour"]);
    firstAidKitType->SetHealingForce(j["firstAidKit"]["healingForce"]);
    firstAidKitType->SetSym(symF[0]);

    for (auto& enemy : j["enemies"].items())
    {
        std::string symE = enemy.value()["sym"];
        colours.emplace(symE[0], enemy.value()["colour"]);
        if (enemy.value()["shootingDamage"] > 0)
            enemiesTypes.emplace(symE[0], std::make_shared<ShootingEnemy>(Point(-1, -1), symE[0],
                enemy.value()["hp"], enemy.value()["xp"], enemy.value()["damage"], enemy.value()["maxHp"], enemy.value()["shootingDamage"]));
        else
            enemiesTypes.emplace(symE[0], std::make_shared<Enemy>(Point(-1, -1), symE[0],
                enemy.value()["hp"], enemy.value()["xp"], enemy.value()["damage"], enemy.value()["maxHp"]));
    }
}

void Level::FindGameObjects()
{
    for (int i = 0; i < levelMap.size(); i++)
    {
        for (int j = 0; j < levelMap[i].size(); j++)
        {
            if (levelMap[i][j] == player->GetSym())
                player->SetPos(Point(i + 1, j + 1));
            else if (levelMap[i][j] == trophy->GetSym())
                trophy->SetPos(Point(i + 1, j + 1));
            else if (levelMap[i][j] == firstAidKitType->GetSym())
                firstAidKits.emplace(Point(i + 1, j + 1), std::make_shared<FirstAidKit>(Point(i + 1, j + 1),
                    firstAidKitType->GetSym(), firstAidKitType->GetHealingForce()));
            else if (enemiesTypes.find(levelMap[i][j]) != enemiesTypes.end())
            {
                std::shared_ptr<ICharacter> enemy = enemiesTypes.find(levelMap[i][j])->second;
                if (enemy->GetShootingDamage() > 0)
                    enemiesContainer.push_back(std::make_shared<ShootingEnemy>(Point(i + 1, j + 1),
                        levelMap[i][j], enemy->GetHp(), enemy->GetXp(), enemy->GetDamage(), enemy->GetMaxHp(), enemy->GetShootingDamage()));
                else
                    enemiesContainer.push_back(std::make_shared<Enemy>(Point(i + 1, j + 1),
                        levelMap[i][j], enemy->GetHp(), enemy->GetXp(), enemy->GetDamage(), enemy->GetMaxHp()));
            }
        }
    }
    for (int i = 0; i < enemiesContainer.size(); i++)
    {
        enemies.emplace(enemiesContainer[i]->GetPos(), enemiesContainer[i]);
    }
}

void Level::PrintLevel()
{
    for (int i = 0; i < levelMap.size(); i++)
    {
        wmove(&*levelWin, i + 1, 1);
        for (int j = 0; j < levelMap[i].size(); j++)
        {
            if (std::abs(player->GetPos().x - i - 1) <= 5 && std::abs(player->GetPos().y - j - 1) <= 10)
            {
                switch (levelMap[i][j])
                {
                case '<':
                case '>':
                case 'v':
                case '^':
                    waddch(&*levelWin, levelMap[i][j]);
                    break;
                case '#':
                    wattron(&*levelWin, COLOR_PAIR(5));
                    waddch(&*levelWin, levelMap[i][j]);
                    wattroff(&*levelWin, COLOR_PAIR(5));
                    break;
                default:
                    wattron(&*levelWin, COLOR_PAIR(colours[levelMap[i][j]]));
                    waddch(&*levelWin, levelMap[i][j]);
                    wattroff(&*levelWin, COLOR_PAIR(colours[levelMap[i][j]]));
                }
            }
            else
            {
                wattron(&*levelWin, COLOR_PAIR(4));
                waddch(&*levelWin, '?');
                wattroff(&*levelWin, COLOR_PAIR(4));
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
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);

    int height = heightOfMap + 2,
        width = widthOfMap + 2,
        startX = 3,
        startY = 6;
    levelWin = std::shared_ptr<WINDOW>(newwin(height, width, startX, startY));

    nodelay(&*levelWin, true);
    keypad(&*levelWin, true);
    cbreak();

    box(&*levelWin, 0, 0);
    wmove(&*levelWin, 1, 1);

    getmaxyx(&*levelWin, height, width);
    mvwprintw(&*levelWin, 0, 5, levelName.c_str());
    mvwprintw(&*levelWin, height - 1, 5, " WASD-Move  IJKL-Shoot ARROWS-Shoot ");
    mvwprintw(&*levelWin, height - 1, width - 28, " ESC to open Pause Menu ");

    wrefresh(&*levelWin);
}

void Level::CreateWPlayerStatus()
{
    playerStatus = std::shared_ptr<WINDOW>(newwin(20, 20, 10, 134));
    nodelay(&*playerStatus, true);
    box(&*playerStatus, 0, 0);
    wrefresh(&*playerStatus);
}

void Level::PrintPLayerStatus()
{
    wclear(&*playerStatus);
    box(&*playerStatus, 0, 0);
    int height, width;
    getmaxyx(&*playerStatus, height, width);
    mvwprintw(&*playerStatus, 0, width / 2 - 3, "[Info]");
    mvwprintw(&*playerStatus, 4, 4, "%s%d", "Hp: ", player->GetHp());
    mvwprintw(&*playerStatus, 7, 4, "%s%d", "Xp: ", player->GetXp());
    mvwprintw(&*playerStatus, 10, 4, "%s%d", "Damage: ", player->GetDamage());
    mvwprintw(&*playerStatus, 13, 4, "Shooting");
    mvwprintw(&*playerStatus, 14, 6, "%s%d", "Damage: ", player->GetShootingDamage());
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
    mvwprintw(&*playerStatus, 0, width / 2 - 6, "[Pause Menu]");
    std::vector<std::string> choices = { "Resume", "Reset", "Exit" };
    int choice = 0, chosenKey = -1;

    while (1)
    {
        for (int i = 0; i < choices.size(); i++)
        {
            if (i == choice)
                mvwprintw(&*playerStatus, i * 3 + 6, width / 2 - 4, ("> " + choices[i]).c_str());
            else
                mvwprintw(&*playerStatus, i * 3 + 6, width / 2 - 4, ("  " + choices[i]).c_str());
        }

        chosenKey = wgetch(&*playerStatus);
        if (chosenKey == 259)
            choice = std::max(0, choice - 1);
        else if (chosenKey == 258)
            choice = std::min(static_cast<int>(choices.size()) - 1, choice + 1);
        else if (chosenKey == 10 || chosenKey == 27)
            break;
    }
    if (choices[choice] == "Resume" || chosenKey == 27)
    {
        wclear(&*playerStatus);
        PrintPLayerStatus();
        box(&*playerStatus, 0, 0);
        wrefresh(&*playerStatus);
        return;
    }
    if (choices[choice] == "Reset")
    {
        std::fstream saveFile("save.json");
        json save;
        saveFile >> save;
        if (save["levelNum"] > 0)
            player->SetHp(save["hp"]);
        levelNumber = save["levelNum"] - 1;
        NextLevel();
        return;
    }
    if (choices[choice] == "Exit")
    {
        levelStatus = 3;
        return;
    }
}

void Level::NextLevel()
{
    levelNumber++;
    levelStatus = 0;

    levelMap.clear();
    enemiesTypes.clear();
    enemies.clear();
    enemiesContainer.clear();
    firstAidKits.clear();
    bullets.clear();
    bulletsContainer.clear();
    colours.clear();

    ReadMap(levelNumber);
    GetCharactersTypes(levelNumber);
    FindGameObjects();
    CreateWindow(GetWidth(), GetHeight());
    PrintLevel();
    CreateWPlayerStatus();
    PrintPLayerStatus();

    
    json save;
    save["levelNum"] = levelNumber;
    save["hp"] = player->GetHp();
    save["xp"] = player->GetXp();
    std::ofstream saveFile("save.json");
    saveFile << save;
}