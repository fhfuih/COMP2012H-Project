#include "Utils.h"

#include <QTime>
#include <QCoreApplication>

void utils_delay(int milliseconds){
    QTime stopTime = QTime::currentTime().addMSecs(milliseconds);
    while (QTime::currentTime()<stopTime){
         QCoreApplication::processEvents(QEventLoop::AllEvents, (milliseconds*2)/3);
     }
    return;
}
