#include "Orb.h"
    
Orb::Orb(int row, int col, Type type, Orb* (*orbBoard)[5][6]) :
    TYPE(type),
    row(row),
    col(col),
    orbBoard(orbBoard)
{
    //connect(someClass, someSignal, this, SLOT(on_drag))
}

int Orb::get_row() {
    return row;
}
int Orb::get_col() {
    return col;
}

Type Orb::get_type() {
    return TYPE;
}
