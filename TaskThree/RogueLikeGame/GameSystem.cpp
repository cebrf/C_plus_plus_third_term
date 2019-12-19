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
            bool isShoot = 0;
            std::pair<int, int> direction = getDirection(move, isShoot);

            if (direction.first != 0 || direction.second != 0)
                if (isShoot)
                {
                    bool needCollide = shoot(direction, player);
                    if (needCollide)
                    {
                        makeMove({ 0, 0 }, *bullets.rbegin());
                    }
                }
                else
                    makeMove(direction, player);

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        { // move of enemies
            for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
            {
                if ((*enemy)->GetHp() > 0)
                {
                    char move = (*enemy)->GetMove(levelWin);
                    bool isShoot = 0;
                    std::pair<int, int> direction = getDirection(move, isShoot);
                    if (isShoot)
                        ;///shoot for shootingEnemy
                    else
                        makeMove(direction, *(*enemy));
                }
            }
            for (int i = 0; i < enemies.size();)
            {
                if (enemies[i]->GetHp() <= 0)
                    enemies.erase(next(enemies.begin(), i));
                else
                    i++;
            }
        }

        { //move of arrows
            for (int i = 0; i < bullets.size(); i++)
            {
                if (bullets[i].GetSym() != ' ')
                {
                    level.SetObj(levelWin, bullets[i].GetPos(), ' ');
                    bool isWall = makeMove({ bullets[i].GetDirection().x, bullets[i].GetDirection().y }, bullets[i]);
                    if (isWall)
                        bullets[i].SetSym(' ');
                }
            }
            for (int i = 0; i < bullets.size();)
            {
                if (bullets[i].GetSym() == ' ')
                    bullets.erase(next(bullets.begin(), i));
                else
                    i++;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool GameSystem::makeMove(const std::pair<int, int> direction, IGameObject& character)
{
    Point newPos(character.GetPos().x + direction.first, character.GetPos().y + direction.second);
    if (newPos.x <= 0 || newPos.y <= 0 || newPos.x - 1 >= level.GetHeight() ||
        newPos.y >= level.GetWidth() || level.GetObj(newPos) == '#')
        return 1;

    if (level.GetObj(newPos) == ' ' && level.GetObj(newPos) == ' ')
    {
        level.SetObj(levelWin, character.GetPos(), ' ');
        character.SetPos(newPos);
        level.SetObj(levelWin, character.GetPos(), character.GetSym());
        return 0;
    }

    if (level.GetObj(newPos) == 'v' || level.GetObj(newPos) == '^' || level.GetObj(newPos) == '>' || level.GetObj(newPos) == '<')
    {
        int i = 0;
        for (; i < bullets.size(); i++)
        {
            if (bullets[i].GetPos().x == newPos.x && bullets[i].GetPos().y == newPos.y)
                break;
        }
        if (i == bullets.size())
            int aaa = 12;

        level.SetObj(levelWin, bullets[i].GetPos(), ' ');
        bool killed = bullets[i].Collide(character);
        if (killed)
        {
            level.SetObj(levelWin, character.GetPos(), ' ');
            if (character.GetSym() == '@')
                death();
        }
        return 0;
    }

    if (level.GetObj(newPos) == player.GetSym())
    {
        bool killed = player.Collide(character);
        if (killed)
        {
            death(); // TODO show menu
        }
        return 0;
    }
    
    
    {
        int i = 0;
        for (; i < enemies.size(); i++)
            if (enemies[i]->GetPos().x == newPos.x && enemies[i]->GetPos().y == newPos.y)
                break;

        if (i == enemies.size())
        {
            int aa = 20;
        }
        bool killed = enemies[i]->Collide(character);
        if (killed)
            level.SetObj(levelWin, newPos, ' ');
        return 0;
    }
}

std::pair<int, int> GameSystem::getDirection(char move, bool& isShoot)
{
    if (move == 'j' || move == 'l' || move == 'i' || move == 'k')
        isShoot = 1;

    std::pair<int, int> direction = { 0, 0 };
    if (move == 'w' || move == 'i')
        direction.first = -1;
    else if (move == 's' || move == 'k')
        direction.first = 1;
    else if (move == 'a' || move == 'j')
        direction.second = -1;
    else if (move == 'd' || move == 'l')
        direction.second = 1;
    return direction;
}

void GameSystem::death()
{
    wclear(levelWin);
    mvwprintw(levelWin, 10, 10, "YOU ARE DEAD!");
    wrefresh(levelWin);
}



bool GameSystem::shoot(std::pair<int, int> direction, IShootingChatacter& chatacter)
{
    Point pos(chatacter.GetPos().x + direction.first, chatacter.GetPos().y + direction.second);
    
    if (pos.x <= 0 || pos.y <= 0 || pos.x - 1 >= level.GetHeight() || pos.y >= level.GetWidth())
        return 0;
    if (level.GetObj(pos) == '#')
        return 0;
    bullets.push_back(Bullet(pos, Point(direction.first, direction.second)));
    if (level.GetObj(pos) == ' ')
    {
        level.SetObj(levelWin, bullets.rbegin()->GetPos(), bullets.rbegin()->GetSym());
        return 0;
    }
    return 1; // need collide
}