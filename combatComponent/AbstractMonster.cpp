#include "AbstractMonster.h"

AbstractMonster::AbstractMonster(int position, int ID, AbstractMonster* (*monsterArray)[5]) :
    POSITION(position),
    ID(ID),
    PRIMARY_TYPE(records[ID][1]),
    SECONDARY_TYPE(records[ID][2]),
    ATTACK(records[ID][3]),
    HEALTH(records[ID][4]),
    DEFENSE(records[ID][5]),
    ABILITY_COOLDOWN(records[ID][6]),
    monsterArray(monsterArray)
{
    turnsAbility = ABILITY_COOLDOWN;
}
