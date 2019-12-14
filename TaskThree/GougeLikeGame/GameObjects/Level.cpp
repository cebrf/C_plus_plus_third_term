#include "Level.h"

void Level::GetLevelMap(const std::string& fileName, std::vector<std::string>& levelMap)
{
    //read from json
    //work with json file
    levelMap = {
        "##########",
        "#@        ",
        "#     #   ",
        "# #      #",
        "#         ",
        "##########"
    };

    //каким-то обрзом мы должны показывать только часть карты!
    //следовательно и считывать не всю а только видимую часть
}

void Level::GetEnemiesTypes(const std::string& EnemiesFileName, std::map<char, ICharacter*> enemiesTypes)
{
    ///
}

void Level::FindGameObjects(const std::vector<std::string>& levelMap,
    std::map<std::pair<int, int>, ICharacter*>& enemies,
    const std::map<char, ICharacter*>& enemiesTypes,
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
    int height = 6 + 2,
        width = 10 + 2,
        startX = 10,
        startY = 10;
    levelWin = newwin(height, width, startX, startY);
    box(levelWin, 0, 0);
    wmove(levelWin, 1, 1);
    wrefresh(levelWin);
}