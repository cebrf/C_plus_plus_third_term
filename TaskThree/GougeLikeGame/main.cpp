#include <iostream>

using namespace std;

#include "GameSystem.h"

int main()
{
    /*initscr();
    noecho();
    int che = getch();
    printw("%c", che);
    refresh();

    getch();
    endwin();*/

    GameSystem game;
    game.Start("123", "123");

    return 0;
}