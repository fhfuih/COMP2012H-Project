#include "Utils.h"

#include <QTime>
#include <QCoreApplication>

void keepItsFuckingSize(QWidget* widget) {
   auto sp = widget->sizePolicy();
   sp.setRetainSizeWhenHidden(true);
   widget->setSizePolicy(sp);
}

void utils_delay(int milliseconds){
    QTime stopTime = QTime::currentTime().addMSecs(milliseconds);
    while (QTime::currentTime()<stopTime){
         QCoreApplication::processEvents(QEventLoop::AllEvents, (milliseconds*2)/3);
     }
    return;
}
