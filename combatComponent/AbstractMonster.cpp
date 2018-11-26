#include "AbstractMonster.h"

AbstractMonster::AbstractMonster(int position, int ID) :
    ID(ID),
    /*
    TYPE(records[ID][1]),
    POSITION(position),
    ATTACK(records[ID][3]),
    HEALTH(records[ID][4]),
    DEFENSE(records[ID][5]),
    COOLDOWN(records[ID][6])
  */
    TYPE(FIRE),
    POSITION(position),
    ATTACK(100),
    HEALTH(100),
    DEFENSE(100),
    COOLDOWN(3)
{
    turnsCooldown = COOLDOWN;
}

int AbstractMonster::get_attack() const {
    return ATTACK;
}

int AbstractMonster::get_health() const {
    return HEALTH;
}

int AbstractMonster::get_defense() const {
    return DEFENSE;
}
