#include "GameSystem.h"

GameSystem::GameSystem() { }

void GameSystem::Start(int levelNumber, int hp, int xp)
{
    if (hp > 0)
    {
        level.player->SetHp(hp);
        level.player->SetXp(xp);
    }
    level.levelNumber = levelNumber - 1;
    level.NextLevel();
    Play();
}

void GameSystem::Play()
{
    while (true)
    {
        level.PrintLevel();

        switch (level.levelStatus)
        {
        case 1:
        case 3:
            return;
        case 2:
            std::string nextLevelPath = "level" + std::to_string(level.levelNumber + 1) + ".txt";
            if (_access(nextLevelPath.c_str(), 0) == 0)
                level.NextLevel();
            else
                return;
            break;
        }

        {
            for (auto bullet = level.bulletsContainer.begin(); bullet != level.bulletsContainer.end(); bullet++)
                if (level.bullets.find((*bullet)->GetPos()) != level.bullets.end())
                    (*bullet)->Update(level);

            /*level.bulletsContainer.clear();
            for (auto bullet = level.bullets.begin(); bullet != level.bullets.end(); bullet++)
                level.bulletsContainer.push_back(bullet->second);*/

            for (int i = 0; i < level.bulletsContainer.size(); i++)
            {
                if (level.bullets.find(level.bulletsContainer[i]->GetPos()) == level.bullets.end())
                    level.bulletsContainer.erase(next(level.bulletsContainer.begin(), i));
            }
        }

        for (int e = 0; e < 5; e++)
        {
            level.PrintPLayerStatus();
            level.player->Update(level);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        {
            for (auto enemy = level.enemiesContainer.begin(); enemy != level.enemiesContainer.end(); enemy++)
                if (level.enemies.find((*enemy)->GetPos()) != level.enemies.end())
                    (*enemy)->Update(level);

            level.enemiesContainer.clear();
            for (auto enemy = level.enemies.begin(); enemy != level.enemies.end(); enemy++)
                level.enemiesContainer.push_back(enemy->second);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int GameSystem::GetGameStatus()
{
    return level.levelStatus;
}
int GameSystem::GetLevelNum()
{
    return level.levelNumber;
}