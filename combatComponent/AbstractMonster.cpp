#include "AbstractMonster.h"

AbstractMonster::AbstractMonster(int position, int ID, AbstractMonster* (*monsterArray)[5]) :
    ID(ID),
    PRIMARY_TYPE(records[ID][1]),
    SECONDARY_TYPE(records[ID][2]),
    POSITION(position),
    ATTACK(records[ID][3]),
    HEALTH(records[ID][4]),
    DEFENSE(records[ID][5]),
    COOLDOWN(records[ID][6])
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
