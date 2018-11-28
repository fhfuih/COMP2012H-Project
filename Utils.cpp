#include "Utils.h"

void keepItsFuckingSize(QWidget* widget) {
   auto sp = widget->sizePolicy();
   sp.setRetainSizeWhenHidden(true);
   widget->setSizePolicy(sp);
}
