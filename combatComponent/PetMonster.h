#ifndef PetMonster_h
#define PetMonster_h

#include "AbstractMonster.h"
#include "EnemyMonster.h"

class PetMonster : public AbstractMonster {
    /* Class for pet monsters */
public:
    PetMonster(int position, int ID, EnemyMonster* (*enemyArray)[5]);

    /* override AbstractMonster definitions
     * attack() function calculates outputDamage and select target enemy
     * special_ability() function determines type of pet ability */
    virtual int attack() override;
    virtual int special_ability() override;
    
protected:
    /* pointer to enemy monsters to select target */
    EnemyMonster* (*enemyArray)[5];

    /* stores pet output damage after calculation */
    int outputDamage;
    /* booleans to store whether attack is super effective and critical hit */
    bool superEffective;
    bool criticalHit;
    
    /* calculates output damage according to orb combos and type */
    void calculate_damage(vector<Combo> combos);
    /* boolean to indicate whether special attack is ready */
    bool gain_special_attack();

    /* friend class to allow access by combat components */
    friend class CombatGame;
};

#endif /* PetMonster_h */
