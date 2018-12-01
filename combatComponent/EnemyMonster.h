#ifndef EnemyMonster_h
#define EnemyMonster_h

#include "AbstractMonster.h"

class EnemyMonster : public AbstractMonster {
public:
    EnemyMonster(int position, int ID);
    
    virtual int attack() override;
    virtual int special_ability() override;
    
    int get_current_health() const;
protected:
    int currentHealth;
    bool healed;
    int trueDamage;
    int recieve_damage(int damage);

    friend class CombatGame;
};

#endif /* EnemyMonster_h */
