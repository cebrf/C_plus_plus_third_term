#include "GameSystem.h"

GameSystem::GameSystem(const std::string& levelFileName, const std::string& EnemiesFileName) :
    player(Point(-1, -1), ' ', -1, -1, -1) //Point pos, char sym, int hp, int damage, int maxHp*/
{
    Level::GetLevelMap(levelFileName, levelMap);
    Level::GetCharactersTypes(EnemiesFileName, enemiesTypes, player);
    Level::FindGameObjects(levelMap, enemies, enemiesTypes, player);
    Level::CreateWindow(levelWin, levelMap[0].size(), levelMap.size());
    Level::PrintLevel(levelWin, levelMap);
}

void GameSystem::Start()
{
    while (true)
    {
        { // move of player
            char move = wgetch(levelWin);
            std::pair<int, int> direction = getDirection(move);
            makeMove(direction, &player);
        }

        { // move of enemies
            for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
            {
                if (enemy->GetHp() > 0)
                {
                    char move = getRandomMove();
                    std::pair<int, int> direction = getDirection(move);
                    makeMove(direction, &(*enemy));
                }
            }
            for (int i = 0; i < enemies.size();)
            {
                if (enemies[i].GetHp() <= 0)
                {
                    enemies.erase(next(enemies.begin(), i));
                }
                else 
                {
                    i++;
                }
            }
        }
    }
}

void GameSystem::makeMove(const std::pair<int, int> direction, ICharacter* character)
{
    Point newPos(character->GetPos().x + direction.first, character->GetPos().y + direction.second);
    if (newPos.x - 1 < levelMap.size()
        && newPos.y - 1 < levelMap[0].size()
        && levelMap[newPos.x - 1][newPos.y - 1] != '#')
    {
        if (levelMap[newPos.x - 1][newPos.y - 1] != ' ' && levelMap[newPos.x - 1][newPos.y - 1] != '.')
        {
            if (levelMap[newPos.x - 1][newPos.y - 1] == player.GetSym())
            {
                bool killed = Attack(character, &player);
                if (killed)
                {
                    death();
                }
            }
            else
            {
                int i = 0;
                for (; i < enemies.size(); i++)
                {
                    if (enemies[i].GetPos().x == newPos.x && enemies[i].GetPos().y == newPos.y)
                        break;
                }
                bool killed = Attack(character, &enemies[i]);
                if (killed)
                {
                    levelMap[newPos.x - 1][newPos.y - 1] = ' ';
                    mvwaddch(levelWin, newPos.x, newPos.y, ' ');
                }
            }
        }
        else
        {
            mvwaddch(levelWin, character->GetPos().x, character->GetPos().y, '.');
            levelMap[character->GetPos().x - 1][character->GetPos().y - 1] = ' ';
            character->SetPos(newPos);
            mvwaddch(levelWin, character->GetPos().x, character->GetPos().y, character->GetSym());
            levelMap[character->GetPos().x - 1][character->GetPos().y - 1] = character->GetSym();
        }
    }
}

char GameSystem::getRandomMove()
{
    std::vector<char> v = { 'w', 'a', 's', 'd' };
    return v[rand() % 4];
}

std::pair<int, int> GameSystem::getDirection(char move)
{
    std::pair<int, int> direction = { 0, 0 };
    if (move == 'w')
        direction.first = -1;
    else if (move == 's')
        direction.first = 1;
    else if (move == 'a')
        direction.second = -1;
    else if (move == 'd')
        direction.second = 1;
    return direction;
}

bool GameSystem::Attack(ICharacter* attacker, ICharacter* prey)
{
    prey->SetHp(std::max(0, prey->GetHp() - attacker->GetDamage()));
    if (prey->GetHp() == 0)
        return 1;
    else
        return 0;
}

void GameSystem::death()
{
    wclear(levelWin);
    mvwprintw(levelWin, 10, 10, "YOU ARE DEAD!");
    wrefresh(levelWin);
}