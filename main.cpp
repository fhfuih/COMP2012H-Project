#include "SelectionWindow.h"
#include "gameinstance.h"
#include "AboutWindow.h"
#include "StartWindow.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);

#ifdef RUN_MAIN_WINDOW
   MainWindow m;
    m.show();
#endif

#ifdef RUN_GAME_INSTANCE
    int level = 1;
    int PetMonsterID[5] {101, 102, 103, 104,105};
    GameInstance g(level, PetMonsterID);
#endif

#ifdef RUN_ABOUT_WINDOW
    AboutWindow about;
    about.show();
#endif

#ifdef RUN_START_WINDOW
    StartWindow start;
    start.show();
#endif

#ifdef RUN_COMBAT_GAME_WINDOW
    int PetMonsterID[5] = {101, 102, 103, 104, 105};
    int EnemyMonsterID[5] = {201, 202, 203, 204, 205};
    CombatGameWindow w(PetMonsterID, EnemyMonsterID);
    w.show();
#endif

    return a.exec();
}
