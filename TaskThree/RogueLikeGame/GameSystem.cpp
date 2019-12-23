#include "GameSystem.h"

GameSystem::GameSystem() { }

void GameSystem::Start(int levelNumber, int hp)
{
    if (hp > 0)
        level.player->SetHp(hp);
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
            if (level.levelNumber < 2)
                level.NextLevel();
            else
                return;
            break;
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

        {
            for (auto bullet = level.bulletsContainer.begin(); bullet != level.bulletsContainer.end(); bullet++)
                if (level.bullets.find((*bullet)->GetPos()) != level.bullets.end())
                    (*bullet)->Update(level);

            level.bulletsContainer.clear();
            for (auto bullet = level.bullets.begin(); bullet != level.bullets.end(); bullet++)
                level.bulletsContainer.push_back(bullet->second);
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