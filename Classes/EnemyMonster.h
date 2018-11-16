#ifndef EnemyMonster_h
#define EnemyMonster_h

#include "AbstractMonster.h"

class EnemyMonster : public AbstractMonster {
public:
    const static char IMAGE = '?'; //some image
    
    EnemyMonster(); //some constructor
    ~EnemyMonster(); //some destructor
    
    virtual char getImage() const;
    
    virtual void animation(); //some animation?
    
    virtual int calculate_attack(); //calculate here or in derived class?
    virtual void attack(); //attack here or in derived class?
    
    virtual void special_attack(); //special attack here or in derived class?
protected:
    int health;
    int defense;
}

#endif /* EnemyMonster_h */
