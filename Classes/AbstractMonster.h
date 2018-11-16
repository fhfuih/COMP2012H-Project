#ifndef AbstractMonster_h
#define AbstractMonster_h

#include <QObject>

#include "Type.h"

class AbstractMonster {
public:
    const Type type;
    AbstractMonster(); //some constructor
    virtual ~AbstractMonster();
    
    virtual char getImage() const = 0;
    int getPosition() const;
    
    virtual void animation() = 0; //some animation?
    
    virtual int calculate_attack() = 0; //calculate here or in derived class?
    virtual void attack() = 0; //attack here or in derived class?
    
    virtual void special_attack(); //special attack here or in derived class?
protected:
    int position;
    
    int damage; //member here or in derived class?
    AbstractMonster* (*gameBoard)[5]; //pointer to either enemy/pet board
}

#endif /* AbstractMonster_h */
