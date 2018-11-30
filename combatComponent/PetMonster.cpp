#include "PetMonster.h"

PetMonster::PetMonster(int position, int ID, EnemyMonster* (*enemyArray)[5]) :
    AbstractMonster(position, ID),
    enemyArray(enemyArray)
{}

int PetMonster::attack() {
    vector<int> targetType;
    for(int i = 0; i < 5; ++i) if((*enemyArray)[i] != nullptr) {
        if(static_cast<int>((*enemyArray)[i]->TYPE) == static_cast<int>(TYPE)+1) {
            targetType.push_back(i);
        }
    }

    int target = -1;
    for(int i = 4; i >= 0; --i) if((*enemyArray)[i] != nullptr) target = i;

    if(targetType.size() != 0) {
        target = targetType[0];
        for(size_t i = 0; i < targetType.size(); ++i) {
            if((*enemyArray)[targetType[i]]->get_current_health() < (*enemyArray)[target]->get_current_health()) {
                target = targetType[i];
            }
        }
        outputDamage *= 2;
    }
    else for(int i = 0; i < 5; ++i) if((*enemyArray)[i] != nullptr) {
        if((*enemyArray)[i]->get_current_health() < (*enemyArray)[target]->get_current_health()) {
            target = i;
        }
    }
    
    criticalHit = false;
    if(rand()%100 < 30) {
        outputDamage *= 4;
        criticalHit = true;
    }
    
    return target;
    //chooses enemy to reduce health
    //priority: highest potential damage > lowest hp
}

int PetMonster::special_ability() {
    turnsCooldown = COOLDOWN;
    return ID%2;
}

void PetMonster::calculate_damage(vector<Combo> combos) {
    size_t combo_count = combos.size();
    int typeOrbs = 0;
    for(size_t i = 0; i < combo_count; ++i) {
        if(combos[i].type == TYPE) typeOrbs += combos[i].orbCount;
    }
    int comboDamage = static_cast<int>((1 + 0.25*(combo_count - 1)) * (1 + 0.1*(typeOrbs - 3)) * ATTACK);
    if(combo_count > 5) comboDamage *= 5;
    
    if(typeOrbs == 0) comboDamage = 0;
    outputDamage = comboDamage;
    
    //formula: [1 + 0.25*(combos-1)] * [1 + 0.1*(typeOrbs-3)] * petAttack
    //if more than 5 combos: bonusDamage = formulaDamage * 5
    //type super-effective: outputDamage = 2 * bonusDamage
}

bool PetMonster::gain_special_attack() {
    if(turnsCooldown != 0) {
        --turnsCooldown;
        if(turnsCooldown == 0) return true;
    }
    return false;
}
