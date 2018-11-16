#ifndef AbstractMonster_h
#define AbstractMonster_h

#include <QObject>

#include "Type.h"

class AbstractMonster {
public:
    const int ID; //predefined pet/enemy id in records
    const Type PRIMARY_TYPE;
    const Type SECONDARY_TYPE;
    const int POSITION;
    
    AbstractMonster(int position, int ID, AbstractMonster* (*monsterArray)[5]);
    virtual ~AbstractMonster() = default;
    
    virtual void attack() const = 0;
    virtual void special_ability() const = 0;
protected:
    const int ATTACK;
    const int HEALTH;
    const int DEFENSE;
    
    const int ABILITY_COOLDOWN;
    int turnsAbility;
    
    AbstractMonster* (*monsterArray)[5]; //pointer to either enemy/pet array
    
    virtual int calculate_damage() = 0;
    virtual void animation() = 0; //some animation?
}

#endif /* AbstractMonster_h */
