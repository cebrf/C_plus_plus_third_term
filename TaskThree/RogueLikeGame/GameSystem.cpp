#include "GameSystem.h"

GameSystem::GameSystem(const std::string& levelFileName, const std::string& EnemiesFileName) :
    player(Point(-1, -1), ' ', -1, -1, -1) //Point pos, char sym, int hp, int damage, int maxHp*/
{
    Level::CreateWindow(levelWin);
    Level::GetLevelMap(levelFileName, levelMap);
    Level::GetCharactersTypes(EnemiesFileName, enemiesTypes, player);
    Level::FindGameObjects(levelMap, enemies, enemiesTypes, player);
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

        if(0){ // move of enemies
            for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
            {
                char move = getRandomMove();
                std::pair<int, int> direction = getDirection(move);
                makeMove(direction, &(enemy->second));
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
            if (enemies.find({ newPos.x,newPos.y }) == enemies.end())
            {
                bool killed = Attack(character, &player);
                if (killed)
                {
                    //you are died
                    wclear(levelWin);
                    mvwprintw(levelWin, 10, 10, "YOU ARE DEAD!");
                    wrefresh(levelWin);
                    int i = 1;
                }
            }
            else
            {
                bool killed = Attack(character, &enemies.find({ newPos.x, newPos.y })->second);
                if (killed)
                {
                    enemies.erase({ newPos.x, newPos.y });
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