#ifndef PetMonster_h
#define PeMonster_h

#include "AbstractMonster.h"

class PetMonster : public AbstractMonster {
public:    
    PetMonster(int position, int ID, PetMonster* (*petArray)[5]);
    ~PetMonster(); //some destructor

    virtual void attack() const override;
    virtual void special_ability() const override;
    
protected:
    EnemyMonster* enemyArray[5];
    int outputDamage;
    
    int calculate_damage(vector<vector<int>> combos) const;
    virtual void animation() override; //some animation?
    
signals:
    void damage_enemy(int position, int outputDamage);
}

#endif /* PetMonster_h */
