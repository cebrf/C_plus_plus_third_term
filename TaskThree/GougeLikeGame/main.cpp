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

    GameSystem game("level1.txt", "123");
    game.Start();

    return 0;
}