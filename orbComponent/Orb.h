#ifndef Orb_h
#define Orb_h

#include "Type.h"

class Orb{
public:
    const Type TYPE;
    
    Orb(int row, int col, Type type, Orb* (*orbBoard)[5][6]);
    ~Orb(); //some destructor
    
    int get_row();
    int get_col();
    Type get_type();
protected:
    int row;
    int col;
    
    Orb* (*orbBoard)[5][6]; //pointer to orb game board
};

#endif /* Orb_h */
