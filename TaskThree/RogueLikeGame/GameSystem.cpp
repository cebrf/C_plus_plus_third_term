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
    while (true)
    {
        if (level.player->GetHp() <= 0)
            death();

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

void GameSystem::death()
{
    level.PrintPLayerStatus();
    wclear(level.levelWin);
    mvwprintw(level.levelWin, 10, 10, "YOU ARE DEAD!");
    wrefresh(level.levelWin);
}