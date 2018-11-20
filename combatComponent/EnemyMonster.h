#ifndef EnemyMonster_h
#define EnemyMonster_h

#include "AbstractMonster.h"

class EnemyMonster : public AbstractMonster {
public:
    EnemyMonster(int position, int ID, AbstractMonster* (*enemyArray)[5]);
    ~EnemyMonster(); //some destructor
    
    virtual void attack() override;
    virtual void special_ability() override;
    
    int get_current_health() const;
protected:
    int currentHealth;
    int turnsAttack;
    
    virtual int calculate_damage() override;
    virtual void animation() override; //some animation?
}

#endif /* EnemyMonster_h */
