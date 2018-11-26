#include "PetMonster.h"

PetMonster::PetMonster(int position, int ID, PetMonster* (*petArray)[5], EnemyMonster* (*enemyArray)[5]) :
    AbstractMonster(position, ID),
    petArray(petArray),
    enemyArray(enemyArray),
    abilityReady(false)
{}

void PetMonster::attack() {
    vector<int> targetType;
    for(int i = 0; i < 5; ++i) if((*enemyArray)[i] != nullptr) {
        if(static_cast<int>((*enemyArray)[i]->TYPE) == static_cast<int>(TYPE)+1) {
            targetType.push_back(i);
        }
    }

    int target = 0;
    if(targetType.size() != 0) {
        target = targetType[0];
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
    
    if(rand()%100 < 5) outputDamage *= 4;
    
    emit damage_enemy(target, outputDamage);
    //chooses enemy to reduce health
    //priority: highest potential damage > lowest hp
}

void PetMonster::special_ability() {
    //when turnsAbility == 0, show activate

    if(abilityReady == true) {
        switch(ID%2) {
            case 0:
                emit attack_all_enemy(TYPE, ATTACK*2);
                break;
            case 1:
                emit heal_player(DEFENSE*5);
                break;
        }
        abilityReady = false;
    }
}

void PetMonster::calculate_damage(vector<Combo> combos) {
    size_t combo_count = combos.size();
    int typeOrbs = 0;
    for(size_t i = 0; i < combo_count; ++i) {
        if(combos[i].type == TYPE) typeOrbs += combos[i].orbCount;
    }
    int comboDamage = static_cast<int>((1 + 0.25*(combo_count - 1)) * (1 + 0.1*(typeOrbs - 3)) * ATTACK);
    if(combo_count > 5) comboDamage *= 5;
    
    outputDamage = comboDamage;
    
    //formula: [1 + 0.25*(combos-1)] * [1 + 0.1*(typeOrbs-3)] * petAttack
    //if more than 5 combos: bonusDamage = formulaDamage * 5
    //type super-effective: outputDamage = 2 * bonusDamage
}

void PetMonster::animation() {
    //some UI code
}
