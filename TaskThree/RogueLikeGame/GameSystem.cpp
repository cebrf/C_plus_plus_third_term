#include "GameSystem.h"

GameSystem::GameSystem(const std::string& levelFileName, const std::string& EnemiesFileName) :
    level(levelFileName)
{
    level.GetCharactersTypes(EnemiesFileName, enemiesTypes, player);
    level.FindGameObjects(enemies, enemiesTypes, player);
    level.CreateWindow(levelWin, level.GetWidth(), level.GetHeight());
    level.PrintLevel(levelWin);
}

void GameSystem::Start()
{
    while (true)
    {
        for (int e = 0; e < 5; e++)
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
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        { // move of enemies
            for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
            {
                if ((*enemy)->GetHp() > 0)
                {
                    //
                    char move = (*enemy)->GetMove(levelWin);
                    std::pair<int, int> direction = getDirection(move);
                    //

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
                level.SetObj(levelWin, bullets[i].GetPos(), ' ');
                
                Point newPos = Point(bullets[i].GetPos().x + bullets[i].GetDirection().x, bullets[i].GetPos().y + bullets[i].GetDirection().y);
                if (level.GetObj(newPos) != ' ')
                {
                    // wall or character -> if wall, erase. If character, setDamage and erase
                }
                else
                {
                    bullets[i].SetPos(newPos);
                    level.SetObj(levelWin, bullets[i].GetPos(), bullets[i].GetSym());
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void GameSystem::makeMove(const std::pair<int, int> direction, ICharacter& character)
{
    Point newPos(character.GetPos().x + direction.first, character.GetPos().y + direction.second);
    if (newPos.x <= 0 || newPos.y <= 0 || newPos.x - 1 >= level.GetHeight() || newPos.y >= level.GetWidth() || level.GetObj(newPos) == '#')
        return;

    // character.Collede();
    if (level.GetObj(newPos) == ' ' && level.GetObj(newPos) == ' ')
    {
        level.SetObj(levelWin, character.GetPos(), ' ');
        character.SetPos(newPos);
        level.SetObj(levelWin, character.GetPos(), character.GetSym());
        return;
    }

    if (level.GetObj(newPos) == 'v' || level.GetObj(newPos) == '^' || level.GetObj(newPos) == '>' || level.GetObj(newPos) == '<')
    {
        //you catch arrow. Collide
    }
    else if (level.GetObj(newPos) == player.GetSym())
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
            level.SetObj(levelWin, newPos, ' ');
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
    level.SetObj(levelWin, bullets.rbegin()->GetPos(), bullets.rbegin()->GetSym());
}