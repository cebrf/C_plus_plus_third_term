#include "GameSystem.h"

GameSystem::GameSystem(const std::string& levelFileName, const std::string& EnemiesFileName) :
    player(Point(-1, -1), ' ', -1, -1, -1, -1)
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
            
            char move = player.GetMove(levelWin);
            if (move == 'j' || move == 'l' || move == 'i' || move == 'k')
            {
                shoot(move);
            }
            else
            {
                std::pair<int, int> direction = getDirection(move);
                if (direction.first != 0 || direction.second != 0)
                    makeMove(direction, player);
            }
        }

        { // move of enemies
            for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
            {
                if ((*enemy)->GetHp() > 0)
                {
                    char move = (*enemy)->GetMove(levelWin);
                    std::pair<int, int> direction = getDirection(move);
                    makeMove(direction, *(*enemy));
                }
            }
            for (int i = 0; i < enemies.size();)
            {
                if (enemies[i]->GetHp() <= 0)
                {
                    enemies.erase(next(enemies.begin(), i));
                }
                else 
                {
                    i++;
                }
            }
        }

        { //move of arrows
            for (int i = 0; i < bullets.size(); i++)
            {
                mvwaddch(levelWin, bullets[i].GetPos().x, bullets[i].GetPos().y, ' ');
                levelMap[bullets[i].GetPos().x - 1][bullets[i].GetPos().y - 1] = ' ';
                
                Point newPos = Point(bullets[i].GetPos().x + bullets[i].GetDirection().x, bullets[i].GetPos().y + bullets[i].GetDirection().y);
                if (levelMap[newPos.x - 1][newPos.y - 1] != ' ')
                {
                    // wall or character -> if wall erase. If character setDamage and erase
                }
                else
                {
                    bullets[i].SetPos(newPos);
                    mvwaddch(levelWin, bullets[i].GetPos().x, bullets[i].GetPos().y, bullets[i].GetSym());
                    levelMap[bullets[i].GetPos().x - 1][bullets[i].GetPos().y - 1] = bullets[i].GetSym();
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void GameSystem::makeMove(const std::pair<int, int> direction, ICharacter& character)
{
    Point newPos(character.GetPos().x + direction.first, character.GetPos().y + direction.second);
    if (newPos.x - 1 < levelMap.size()
        && newPos.y - 1 < levelMap[0].size()
        && levelMap[newPos.x - 1][newPos.y - 1] != '#')
    {
        if (levelMap[newPos.x - 1][newPos.y - 1] != ' ' && levelMap[newPos.x - 1][newPos.y - 1] != ' ')
        {
            if (levelMap[newPos.x - 1][newPos.y - 1] == '|' || levelMap[newPos.x - 1][newPos.y - 1] == '^' || levelMap[newPos.x - 1][newPos.y - 1] == '>' || levelMap[newPos.x - 1][newPos.y - 1] == '<')
            {
                //you catch arrow
            }
            else if (levelMap[newPos.x - 1][newPos.y - 1] == player.GetSym())
            {
                bool killed = Attack(character, player);
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
                    if (enemies[i]->GetPos().x == newPos.x && enemies[i]->GetPos().y == newPos.y)
                        break;
                }
                bool killed = Attack(character, *enemies[i]);
                if (killed)
                {
                    levelMap[newPos.x - 1][newPos.y - 1] = ' ';
                    mvwaddch(levelWin, newPos.x, newPos.y, ' ');
                }
            }
        }
        else
        {
            mvwaddch(levelWin, character.GetPos().x, character.GetPos().y, ' ');
            levelMap[character.GetPos().x - 1][character.GetPos().y - 1] = ' ';
            character.SetPos(newPos);
            mvwaddch(levelWin, character.GetPos().x, character.GetPos().y, character.GetSym());
            levelMap[character.GetPos().x - 1][character.GetPos().y - 1] = character.GetSym();
        }
    }
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

bool GameSystem::Attack(ICharacter& attacker, ICharacter& prey)
{
    prey.SetHp(std::max(0, prey.GetHp() - attacker.GetDamage()));
    if (prey.GetHp() == 0)
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

void GameSystem::shoot(char move)
{
    Point direction(0, 0);
    if (move == 'i')
        direction.x = -1;
    else if (move == 'k')
        direction.x = 1;
    else if (move == 'j')
            direction.y = -1;
        else if (move == 'l')
            direction.y = 1;


    bullets.push_back(Bullet(Point(player.GetPos().x + direction.x, player.GetPos().y + direction.y), direction));
    mvwaddch(levelWin, bullets.rbegin()->GetPos().x, bullets.rbegin()->GetPos().y, bullets.rbegin()->GetSym());
    levelMap[bullets.rbegin()->GetPos().x - 1][bullets.rbegin()->GetPos().y - 1] = bullets.rbegin()->GetSym();
}