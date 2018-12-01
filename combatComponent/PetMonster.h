#ifndef PetMonster_h
#define PetMonster_h

#include "AbstractMonster.h"
#include "EnemyMonster.h"

class PetMonster : public AbstractMonster {
public:    
    PetMonster(int position, int ID, EnemyMonster* (*enemyArray)[5]);

    virtual int attack() override;
    virtual int special_ability() override;
    
protected:
    EnemyMonster* (*enemyArray)[5];
    int outputDamage;
    bool superEffective;
    bool criticalHit;
    
    void calculate_damage(vector<Combo> combos);
    bool gain_special_attack();

    friend class CombatGame;
};

#endif /* PetMonster_h */
