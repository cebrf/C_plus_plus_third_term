#include "GameSystem.h"

GameSystem::GameSystem(const std::string& levelFileName, const std::string& EnemiesFileName) :
    player(Point(-1, -1), '@', 100, 20, 100) //Point pos, char sym, int hp, int damage, int maxHp
{
    Level::CreateWindow(levelWin);
    Level::GetLevelMap(levelFileName, levelMap);
    Level::GetEnemiesTypes(EnemiesFileName, enemiesTypes);
    Level::FindGameObjects(levelMap, enemies, enemiesTypes, player);
    Level::PrintLevel(levelWin, levelMap);
}

void GameSystem::Start()
{
    while (1)
    {
        char move = wgetch(levelWin);
        int directionX = 0,
            directionY = 0;
        if (move == 'w' || move == 'a' || move == 's' || move == 'd')
        {
            switch (move)
            {
            case 'w':
                directionX = -1;
                break;
            case 's':
                directionX = 1;
                break;
            case 'a':
                directionY = -1;
                break;
            case 'd':
                directionY = 1;
                break;
            }
            makeMove(directionX, directionY);
        }
    }
}

void GameSystem::makeMove(int directionX, int directionY)
{
    Point newPos(player.GetPos().x + directionX, player.GetPos().y + directionY);
    if (newPos.x - 1 < levelMap.size() && newPos.y - 1 < levelMap[0].size() && levelMap[newPos.x - 1][newPos.y - 1] != '#')
    {
        mvwaddch(levelWin, player.GetPos().x, player.GetPos().y, '.');
        player.SetPos(newPos);
        mvwaddch(levelWin, player.GetPos().x, player.GetPos().y, '@');
    }
}

