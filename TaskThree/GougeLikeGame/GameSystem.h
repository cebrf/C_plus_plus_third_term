#include "GameObjects/Player.h"
#include <string>
#include <vector>
#include "pdcurses/curses.h"

class GameSystem
{
public:
    GameSystem() :
        player(Point(-1, -1), '@', 100, 20, 100) //Point pos, char sym, int hp, int damage, int maxHp
    {
        //create windows
        initscr();
        curs_set(0);
        noecho();
        int height = 6 + 2,
            width = 10 + 2,
            startX = 10,
            startY = 10;
        levelWin = newwin(height, width, startX, startY);
        box(levelWin, 0, 0);
        wmove(levelWin, 1, 1);
        wrefresh(levelWin);
    }

    void Start(const string& levelFileName, const string& EnemiesFileName)
    {
        getMap(levelFileName);
        getEnemiesTypes(EnemiesFileName);
        findObjects(); //finding items, enemies, and player
        printLevel();

        wmove(levelWin, player.GetPos().x, player.GetPos().y);
        wrefresh(levelWin);
        while (1)
        {
            char move = wgetch(levelWin);
            int directionX = 0,
                directionY = 0;
            if (move == 'w' || move == 'a' || move == 's' || move == 'd')
            {
                switch (move)
                {
                case 'w':
                    directionX = -1;
                    break;
                case 's':
                    directionX = 1;
                    break;
                case 'a':
                    directionY = -1;
                    break;
                case 'd':
                    directionY = 1;
                    break;
                }
                makeMove(directionX, directionY);
            }
        }
    }

protected:
    void getMap(const string& levelName)
    {
        //work with json file
        levelMap = {
            "##########",
            "#@        ",
            "#     #   ",
            "# #      #",
            "#         ",
            "##########"
        };

        //каким-то обрзом мы должны показывать только часть карты!
        //следовательно и считывать не всю а только видимую часть
    }
    void getEnemiesTypes(const string& fileName)
    {
        /*using json 
           read all types of monsters, create and push them in to the vector of types
        */
    }
    void findObjects()
    {
        //finding objects and pushing them in vectors

        for (int i = 0; i < levelMap.size(); i++)
        {
            for (int j = 0; j < levelMap[i].size(); j++)
            {
                switch (levelMap[i][j])
                {
                case '@':
                    //how to set pos, if method if protected?
                    player.SetPos(Point(i + 1, j + 1));
                    break;
                default:
                    break;
                }
            }
        }
    }

    void printLevel()
    {
        for (int i = 0; i < levelMap.size(); i++)
        {
            wmove(levelWin, i + 1, 1);
            for (int j = 0; j < levelMap[i].size(); j++)
            {
                waddch(levelWin, levelMap[i][j]);
            }
        }
        wrefresh(levelWin);
    }
    void makeMove(int directionX, int directionY)
    {
        Point newPos(player.GetPos().x + directionX, player.GetPos().y + directionY);
        if (newPos.x - 1 < levelMap.size() && newPos.y - 1 < levelMap[0].size() && levelMap[newPos.x - 1][newPos.y - 1] != '#')
        {
            mvwaddch(levelWin, player.GetPos().x, player.GetPos().y, '.');
            player.SetPos(newPos);
            mvwaddch(levelWin, player.GetPos().x, player.GetPos().y, '@');
        }
    }
private:
    std::vector<string> levelMap;
    std::vector<ICharacter*> enemies;
    std::vector<ICharacter*> enemiesTypes;
    Player player;
    WINDOW* levelWin;
};
