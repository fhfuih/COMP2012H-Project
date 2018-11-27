#include "mainwindow.h"
#include "gameinstance.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    
    //OrbGameWindow g;
    //g.show();

    int level = 1;
    int PetMonsterID[5] {101, 102, 103, 104,105};
    GameInstance g(level, PetMonsterID);

    return a.exec();
}
