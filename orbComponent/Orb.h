#ifndef Orb_h
#define Orb_h

#include <QObject>

#include "Type.h"

class Orb {
public:
    const Type TYPE;
    
    Orb(int row, int col, Type type, Orb* (*orbBoard)[5][6]);
    ~Orb(); //some destructor
    
    int get_row();
    int get_col();
protected:
    int row;
    int col;
    
    Orb* (*orbBoard)[5][6]; //pointer to orb game board
    
    void move_orb();
    void animate(); //some animation?
private slots:
    void on_drag(int row, int col);
}

#endif /* Orb_h */
