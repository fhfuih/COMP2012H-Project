#include "AbstractMonster.h"

AbstractMonster::AbstractMonster(int position, int ID) :
    ID(ID),
    TYPE(fileLoader.getType(ID)),
    POSITION(position),
    ATTACK(fileLoader.getAttack(ID)),
    HEALTH(fileLoader.getHealth(ID)),
    DEFENSE(fileLoader.getDefense(ID)),
    COOLDOWN(fileLoader.getCooldown(ID))
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
