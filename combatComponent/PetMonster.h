#ifndef PetMonster_h
#define PeMonster_h

#include "AbstractMonster.h"

class PetMonster : public AbstractMonster {
public:    
    PetMonster(int position, int ID, AbstractMonster* (*petArray)[5]);
    ~PetMonster(); //some destructor

    virtual void attack() const override;
    virtual void special_ability() const override;
protected:
    virtual int calculate_damage() override;
    virtual void animation() override; //some animation?
    
friend Player //player class to get health and defense
}

#endif /* PetMonster_h */
