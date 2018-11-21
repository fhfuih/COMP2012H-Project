#ifndef Orb_h
#define Orb_h

#include "Type.h"

class Orb {
public:
    const Type TYPE;
    
    Orb(int row, int col, Type type, Orb* (*orbBoard)[5][6]);
    ~Orb(); //some destructor
    
    int get_row() const;
    int get_col() const;
    Type get_type() const;
    
    void set_row(int row);
    void set_col(int col);
    void set_highlighted(bool highlight);
    
protected:
    int row;
    int col;
    
    bool is_highlighted;
    
    Orb* (*orbBoard)[5][6]; //pointer to orb game board
