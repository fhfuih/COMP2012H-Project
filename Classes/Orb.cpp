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

void Orb::move_orb() {
    //switch positions with adjacent orb when cross midpoint±delta
    //call animate() function
}
void Orb::animate() {
    //some animation?
}

void Orb::on_drag(int row, int col) {
    //receive signal then move orb to row/col
}

#endif /* Orb_h */
