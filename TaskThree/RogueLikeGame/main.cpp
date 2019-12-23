#include <iostream>
#include "pdcurses/curses.h"
#include "nlohmann/json.hpp"
#include "GameSystem.h"

using namespace std;

void play()
{
    std::fstream saveFile("save.json");
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    int height, width;
    getmaxyx(stdscr, height, width);
    int startX = height / 4, startY = width / 6;
    std::shared_ptr<WINDOW> menuWin = std::shared_ptr<WINDOW>(newwin(height / 2, width / 2, startX, startY));
    GameSystem game;
    
    while (1)
    {
        clear();
        wclear(&*menuWin);
        box(&*menuWin, 0, 0);
        refresh();
        wrefresh(&*menuWin);
        keypad(&*menuWin, true);
        vector<string> choices;

        switch (game.GetGameStatus())
        {
        case 0:
        case 3:
            mvwprintw(&*menuWin, 5, width / 4 - 2, "Menu");
            choices = { "New game", "Load", "Exit" };
            break;
        case 1:
            mvwprintw(&*menuWin, 5, width / 4 - 4, "Game over");
            choices = { "Try again", "Exit" };
            break;
        case 2:
            mvwprintw(&*menuWin, 5, width / 4 - 11, "Congratulations! You win");
            choices = { "New game", "Exit" };
            break;
        }

        int choice = 0;
        while (1)
        {
            for (int i = 0; i < choices.size(); i++)
            {
                if (i == choice)
                    mvwprintw(&*menuWin, i * 2 + 10, width / 4 - 4, ("> " + choices[i]).c_str());
                else
                    mvwprintw(&*menuWin, i * 2 + 10, width / 4 - 4, ("  " + choices[i]).c_str());
            }

            int chosenKey = wgetch(&*menuWin);
            if (chosenKey == 259)
                choice = max(0, choice - 1);
            else if (chosenKey == 258)
                choice = min(static_cast<int>(choices.size()) - 1, choice + 1);
            else if (chosenKey == 10)
                break;
        }

        clear();
        refresh();
        if (choices[choice] == "New game")
        {
            game.Start(1);
            continue;
        }
        if (choices[choice] == "Load")
        {
            std::fstream saveFile("save.json");
            json save;
            saveFile >> save;
            if (save["levelNum"] > 1)
                game.Start(save["levelNum"], save["hp"]);
            continue;
        }
        if (choices[choice] == "Try again")
        {
            std::fstream saveFile("save.json");
            json save;
            saveFile >> save;
            game.Start(save["levelNum"], save["hp"]);
            continue;
        }
        if (choices[choice] == "Exit")
        {
            break;
        }
    }
}

int main()
{
    play();
    return 0;
}