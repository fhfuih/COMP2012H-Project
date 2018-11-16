#include "PetMonster.h"

PetMonster::PetMonster(int position, int ID, AbstractMonster* (*petArray)[5]) :
    AbstractMonster(position, ID, petArray),
{}

void PetMonster::attack() {
    //choose enemy to reduce health
    //priority: highest potential damage > lowest hp > lowest defense > lowest attack
}

void PetMonster::special_ability() {
    //when turnsAbility == 0, show activate
    //special ability depends on ID
}

int PetMonster::calculate_damage() {
    //formula: [1 + 0.25*(combos-1)] * [1 + 0.1*(typeOrbs-3)] * petAttack
    //if four or more colors: bonusDamage = formulaDamage * 5
    //type super-effective: outputDamage = 1.5 * bonusDamage
    //enemy defense: trueDamage = outputDamage * [100 / (100 + enemyDefense)]
}

void PetMonster::animation() {
    //some UI code
}
