#ifndef EnemyMonster_h
#define EnemyMonster_h

#include "AbstractMonster.h"

class EnemyMonster : public AbstractMonster {
    /* Class for enemy monsters */
public:
    EnemyMonster(int position, int ID);
    
    /* override AbstractMonster definitions
     * attack() function determines how enemy will attack player
     * special_ability() function executes a special attack if called */
    virtual int attack() override;
    virtual int special_ability() override;
    
    /* function for PetMonster to select enemy with lowest health */
    int get_current_health() const;
protected:
    /* stores enemy current health */
    int currentHealth;
    /* stores whether enemy has healed this turn, for graphic display */
    bool healed;
    /* stores amount of damage enemy has received this turn, for graphic display */
    int trueDamage;

    /* reduces enemy health when attacked by pet */
    int recieve_damage(int damage);

    /* friend class to allow access by combat components */
    friend class CombatGame;
};

#endif /* EnemyMonster_h */
