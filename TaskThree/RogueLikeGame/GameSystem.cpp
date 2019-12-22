#include "GameSystem.h"

GameSystem::GameSystem(const std::string& levelFileName, const std::string& EnemiesFileName) :
    level(levelFileName)
{
    level.GetCharactersTypes(EnemiesFileName);
    level.FindGameObjects();
    level.CreateWindow(level.GetWidth(), level.GetHeight());
    level.PrintLevel();
    level.CreateWPlayerStatus();
    level.PrintPLayerStatus();
}

void GameSystem::Start()
{
    shoot = [&](Point direction, ICharacter& character)
    {
        Point pos(character.GetPos().x + direction.x, character.GetPos().y + direction.y);

        if (pos.x <= 0 || pos.y <= 0 || pos.x - 1 >= level.GetHeight() || pos.y >= level.GetWidth())
            return 0;
        if (level.GetSym(pos) == '#')
            return 0;
        level.bulletsContainer.push_back(std::shared_ptr<Bullet>(new Bullet(pos, Point(direction.x, direction.y), character.GetShootingDamage())));
        if (level.GetSym(pos) == ' ')
        {
            level.SetObj((*level.bulletsContainer.rbegin())->GetPos(), (*level.bulletsContainer.rbegin())->GetSym());
            return 0;
        }
        return 1; // need collide
    };
    level.player->shoot = this->shoot;

    makeMove = [&](const std::pair<int, int> direction, IGameObject& character)
    {
        /*Point newPos(character.GetPos().x + direction.first, character.GetPos().y + direction.second);

        if (newPos.x <= 0 || newPos.y <= 0 || newPos.x - 1 >= level.GetHeight())
            return 1;
        if (newPos.y >= level.GetWidth() || level.GetSym(newPos) == '#')
            return 1;

        if (level.GetSym(newPos) == ' ' && level.GetSym(newPos) == ' ')
        {
            level.SetObj(levelWin, character.GetPos(), ' ');
            character.SetPos(newPos);
            level.SetObj(levelWin, character.GetPos(), character.GetSym());
            return 0;
        }

        std::shared_ptr<IGameObject> obj = level.GetObj(newPos);
        character.Collide(*obj);


        if (level.GetSym(newPos) == '+')
        {
            ///
            int  i = 0;
            for (; i < level.firstAidKits.size(); i++)
            {
                if (level.firstAidKitsContainer[i]->GetPos().x == newPos.x && level.firstAidKitsContainer[i]->GetPos().y == newPos.y)
                    break;
            }
            ///

            if (level.firstAidKits.size() > i)
            {
                character.Collide(*level.firstAidKitsContainer[i]);

                level.SetObj(levelWin, character.GetPos(), ' ');
                character.SetPos(newPos);
                level.SetObj(levelWin, character.GetPos(), character.GetSym());
            }
            return 0;
        }

        if (level.GetSym(newPos) == 'v' || level.GetSym(newPos) == '^' || level.GetSym(newPos) == '>' || level.GetSym(newPos) == '<')
        {
            ///
            int i = 0;
            for (; i < level.bullets.size(); i++)
            {
                if (level.bulletsContainer[i]->GetPos().x == newPos.x && level.bulletsContainer[i]->GetPos().y == newPos.y)
                    break;
            }
            ///

            level.SetObj(levelWin, level.bulletsContainer[i]->GetPos(), ' ');
            bool killed = level.bulletsContainer[i]->Collide(character);
            if (killed)
            {
                level.SetObj(levelWin, character.GetPos(), ' ');
            }
            return 0;
        }

        if (level.GetSym(newPos) == level.player->GetSym())
        {
            bool killed = level.player->Collide(character);
            if (killed)
            {
                death(); // TODO show menu
            }
            return 0;
        }


        {
            int i = 0;
            for (; i < level.enemiesContainer.size(); i++)
                if (level.enemiesContainer[i]->GetPos().x == newPos.x && level.enemiesContainer[i]->GetPos().y == newPos.y)
                    break;


            if (i == level.enemiesContainer.size())
            {
                int aa = 20;
            }
            bool killed = level.bulletsContainer[i]->Collide(character);
            if (killed)
                level.SetObj(levelWin, newPos, ' ');
            return 0;
        }*/
        return 0;
    };
    level.player->makeMove = this->makeMove;

    ///////////////////////////////////////////////////
    while (true)
    {
        for (int e = 0; e < 5; e++)
        { // move of player
            level.PrintPLayerStatus();
            if (level.player->GetHp() <= 0)
            {
                death();
            }
            else
            {
                level.player->Update(level);
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

        {
            for (auto enemy = level.enemiesContainer.begin(); enemy != level.enemiesContainer.end(); enemy++)
            {
                if (level.enemies.find((*enemy)->GetPos()) != level.enemies.end())
                {
                    (*enemy)->Update(level);
                }
            }

            level.enemiesContainer.clear();
            for (auto enemy = level.enemies.begin(); enemy != level.enemies.end(); enemy++)
            {
                level.enemiesContainer.push_back(enemy->second);
            }
        }

        /*{ // move of enemies
            for (auto enemy = level.enemiesContainer.begin(); enemy != level.enemiesContainer.end(); enemy++)
            {
                if ((*enemy)->GetHp() > 0)
                {
                    char move = (*enemy)->GetAction(levelWin);
                    bool isShoot = 0;
                    Point direction = (*enemy)->getDirection(move, isShoot);
                    if (isShoot)
                    {
                        bool needCollide = shoot(direction, *(*enemy));
                        if (needCollide)
                        {
                            makeMove({ 0, 0 }, **level.bulletsContainer.rbegin());
                        }
                    }
                    else
                        makeMove({ direction.x, direction.y }, *(*enemy));
                }
            }
            for (int i = 0; i < level.enemies.size();)
            {
                if (level.enemiesContainer[i]->GetHp() <= 0)
                    level.enemies.erase(next(level.enemies.begin(), i));
                else
                    i++;
            }
        }*/

        /*{ //move of arrows
            for (int i = 0; i < level.bulletsContainer.size(); i++)
            {
                if (level.bulletsContainer[i]->GetSym() != ' ')
                {
                    level.SetObj(levelWin, level.bulletsContainer[i]->GetPos(), ' ');
                    bool isWall = makeMove({ level.bulletsContainer[i]->GetDirection().x, level.bulletsContainer[i]->GetDirection().y }, *level.bulletsContainer[i]);
                    if (isWall)
                        level.bulletsContainer[i]->SetSym(' ');
                }
            }
            for (int i = 0; i < level.bullets.size();)
            {
                if (level.bulletsContainer[i]->GetSym() == ' ')
                    level.bullets.erase(next(level.bullets.begin(), i));
                else
                    i++;
            }
        }*/
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void GameSystem::death()
{
    level.PrintPLayerStatus();
    wclear(level.levelWin);
    mvwprintw(level.levelWin, 10, 10, "YOU ARE DEAD!");
    wrefresh(level.levelWin);
}