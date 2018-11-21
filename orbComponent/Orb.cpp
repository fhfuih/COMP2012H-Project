#include "Orb.h"
    
Orb::Orb(int row, int col, Type type, Orb* (*orbBoard)[5][6]) :
    TYPE(type),
    row(row),
    col(col),
    is_highlighted(false),
    orbBoard(orbBoard)
{
    //connect(someClass, someSignal, this, SLOT(on_drag))
}

int Orb::get_row() const {
    return row;
}
int Orb::get_col() const {
    return col;
}

Type Orb::get_type() const {
    return TYPE;
}

int Orb::set_row(int row) {
    this->row = row;
}

int Orb::set_col(int col) {
    this->col = col;
}

int Orb::set_highlighted(bool highlight) {
    is_highlighted = highlight;
}
