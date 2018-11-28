#include "mainwindow.h"
#include "gameinstance.h"
#include "AboutWindow.h"
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

#ifdef RUN_ORB_GAME_WINDOW
    OrbGameWindow g;
    g.show();
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

    return a.exec();
}
