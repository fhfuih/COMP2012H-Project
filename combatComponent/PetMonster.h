#ifndef PetMonster_h
#define PetMonster_h

#include "AbstractMonster.h"
#include "EnemyMonster.h"

class PetMonster : public AbstractMonster {
    Q_OBJECT
public:    
    PetMonster(int position, int ID, PetMonster* (*petArray)[5], EnemyMonster* (*enemyArray)[5]);

    virtual void attack() override;
    virtual void special_ability() override;
    
protected:
    PetMonster* (*petArray)[5];
    EnemyMonster* (*enemyArray)[5];
    int outputDamage;
    bool abilityReady;
    
    void calculate_damage(vector<Combo> combos);
    virtual void animation() override; //some animation?

signals:
    void damage_enemy(int position, int outputDamage);
    void attack_all_enemy(Type PRIMARY_TYPE, int damage);
    void heal_player(int heal);

    friend class CombatGame;
};

#endif /* PetMonster_h */
