#ifndef PetMonster_h
#define PeMonster_h

#include "AbstractMonster.h"
#include "EnemyMonster.h"

class PetMonster : public AbstractMonster {
public:    
    PetMonster(int position, int ID, PetMonster* (*petArray)[5], EnemyMonster* (*enemyArray)[5]);
    virtual ~PetMonster() override; //some destructor

    virtual void attack() override;
    virtual void special_ability() override;
    
protected:
    PetMonster* (*petArray)[5];
    EnemyMonster* (*enemyArray)[5];
    int outputDamage;
    
    void calculate_damage(vector<vector<int>> combos);
    virtual void animation() override; //some animation?
    
signals:
    void damage_enemy(int position, int outputDamage);

    friend class CombatGame;
};

#endif /* PetMonster_h */
