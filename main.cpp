#include "SelectionWindow.h"
#include "gameinstance.h"
#include "AboutWindow.h"
#include "StartWindow.h"
#include <QFontDatabase>
#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/resource/Long_Shot.ttf");
#ifdef RUN_MAIN_WINDOW
   MainWindow m;
    m.show();
#endif

#ifdef RUN_START_WINDOW
    StartWindow start;
    start.show();
#endif

    return a.exec();
}
