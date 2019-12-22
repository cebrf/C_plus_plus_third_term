#include <iostream>
#include "pdcurses/curses.h"
#include "GameSystem.h"

using namespace std;

void play()
{
    while (1)
    {
        GameSystem game("level1.txt", "enemiesLevel1.json");
        game.Start();

        clear();
        std::shared_ptr<WINDOW> menuWin = std::shared_ptr<WINDOW>(newwin(40, 80, 10, 35));
        box(&*menuWin, 0, 0);
        refresh();
        wrefresh(&*menuWin);

        keypad(&*menuWin, true);
        vector<string> choices;
        if (game.GameOver)
        {
            mvwprintw(&*menuWin, 5, 15, "Game over");
            choices = { "Play again", "Exit" };
        }
        else
        {
            choices = { "Play", "Exit" };
        }
        int choice;
        int highlight = 0;

        while (1)
        {
            for (int i = 0; i < 2; i++)
            {
                if (i == highlight)
                    wattron(&*menuWin, A_REVERSE);
                mvwprintw(&*menuWin, i * 2 + 12, 15, choices[i].c_str());
                wattroff(&*menuWin, A_REVERSE);
            }
            choice = wgetch(&*menuWin);
            switch (choice)
            {
            case KEY_UP:
                highlight = max(0, highlight - 1);
                break;
            case KEY_DOWN:
                highlight = min(2, highlight + 1);
                break;
            }
            if (choice == 10)
                break;
        }
        if (highlight == 0)
        {
            clear();
            refresh();
            continue;
        }
        if (highlight == 1)
            return;
    }
}

int main()
{
    initscr();
    curs_set(0);
    noecho();
    cbreak();

    int width, height;  // 80, 200
    getmaxyx(stdscr, height, width);
    std::shared_ptr<WINDOW> menuWin = std::shared_ptr<WINDOW>(newwin(40, 100, height - 60, width - 150));
    box(&*menuWin, 0, 0);
    refresh();
    wrefresh(&*menuWin);

    keypad(&*menuWin, true);
    vector<string> choices = { "Play", "Load", "Exit" };
    int choice;
    int highlight = 0;

    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == highlight)
                wattron(&*menuWin, A_REVERSE);
            mvwprintw(&*menuWin, i * 2 + 10, 15, choices[i].c_str());
            wattroff(&*menuWin, A_REVERSE);
        }
        choice = wgetch(&*menuWin);
        switch (choice)
        {
        case KEY_UP:
            highlight = max(0, highlight - 1);
            break;
        case KEY_DOWN:
            highlight = min(2, highlight + 1);
            break;
        }
        if (choice == 10)
            break;
    }
    if (highlight == 0)
    {
        clear();
        refresh();
        play();
    }
    if (highlight == 2)
        return 0;
}