#include "PetMonster.h"

PetMonster::PetMonster(int position, int ID, AbstractMonster* (*petArray)[5], EnemyMonster* (*enemyArray)[5]) :
    AbstractMonster(position, ID, petArray),
    enemyArray(enemyArray)
{}

void PetMonster::attack() {
    vector<int> targetType;
    for(int i = 0; i < 5; ++i) if((*enemyArray)[i] != nullptr) {
        if(static_cast<int>((*enemyArray)[i]->PRIMARY_TYPE) == static_cast<int>(PRIMARY_TYPE)+1) {
            targetType.push_back(i);
        }
    }
    
    int target = targetType[0];
    if(targetType.size() != 0) {
        for(size_t i = 0; i < targetType.size(); ++i) {
            if((*enemyArray)[targetType[i]]->get_current_health() < (*enemyArray)[target]->get_current_health()) {
                target = targetType[i];
            }
        }
        outputDamage *= 2;
    }
    else for(int i = 0; i < 5; ++i) {
        if((*enemyArray)[i]->get_current_health() < (*enemyArray)[target]->get_current_health()) {
            target = i;
        }
    }
    
    if(rand()*100 < 5) outputDamage *= 4;
    
    emit damage_enemy(target, outputDamage);
    //choose enemy to reduce health
    //priority: highest potential damage > lowest hp
}

void PetMonster::special_ability() const {
    //when turnsAbility == 0, show activate
    //special ability depends on ID
}

void PetMonster::calculate_damage(vector<vector<int>> combos) {
    size_t combo_count = combos.size();
    int typeOrbs = 0;
    for(size_t i = 0; i < combo_count; ++i) {
        if(combos[i][0] == static_cast<int>(PRIMARY_TYPE)) typeOrbs += combos[i][1];
    }
    int comboDamage = (1 + 0.25*(combo_count - 1)) * (1 + 0.1*(typeOrbs - 3)) * ATTACK;
    if(combo_count > 5) comboDamage *= 5;
    
    outputDamage = comboDamage;
    
    //formula: [1 + 0.25*(combos-1)] * [1 + 0.1*(typeOrbs-3)] * petAttack
    //if four or more colors: bonusDamage = formulaDamage * 5
    //type super-effective: outputDamage = 1.5 * bonusDamage
}

void PetMonster::animation() {
    //some UI code
}
