#include "CombatGame.h"

CombatGame::CombatGame(int level, int petSelection[5]) :
    level(level),
    turnNumber(1),
    playerHealth(0),
    playerDefense(0)
{
    vector<int> enemyID = fileLoader().getLevel(level);

    for(int i = 0; i < 5; ++i) petArray[i] = new PetMonster(i, petSelection[i], &enemyArray);
    for(int i = 0; i < 5; ++i) {
        if(enemyID[static_cast<unsigned long>(i)] != -1) enemyArray[i] = new EnemyMonster(i, enemyID[static_cast<unsigned long>(i)]);
        else enemyArray[i] = nullptr;
    }
    
    for(int i = 0; i < 5; ++i) playerHealth += petArray[i]->get_health();
    for(int i = 0; i < 5; ++i) playerDefense += petArray[i]->get_defense();
}

CombatGame::~CombatGame() {
    for(int i = 0; i < 5; ++i) if(petArray[i] != nullptr) delete petArray[i];
    for(int i = 0; i < 5; ++i) if(enemyArray[i] != nullptr) delete enemyArray[i];
}

void CombatGame::pets_attack(const vector<Combo>& combos) {
    for(int i = 0; i < 5; ++i) {
        petArray[i]->calculate_damage(combos);
        int targetEnemy = petArray[i]->attack();
        if(targetEnemy == -1) continue;
        if(petArray[i]->outputDamage == 0) continue;
        int enemyHealth = enemyArray[targetEnemy]->recieve_damage(petArray[i]->outputDamage);
        emit pet_attack_enemy(i, targetEnemy, enemyHealth, petArray[i]->criticalHit);
        if(enemyHealth == 0) {
            delete enemyArray[targetEnemy];
            enemyArray[targetEnemy] = nullptr;
            emit enemy_die(targetEnemy);

            bool clear = true;
            for(int j = 0; j < 5; ++j) if(enemyArray[j] != nullptr) clear = false;
            if(clear == true) {
                emit level_cleared();
                return;
            }
        }
    }
}

void CombatGame::enemies_attack() {
    for(int i = 0; i < 5; ++i) if(enemyArray[i] != nullptr) {
        int enemyDamage = enemyArray[i]->attack();
        if(enemyDamage != 0) {
            int playerHealth = player_recieve_damage(enemyDamage);
            emit enemy_attack_player(i, enemyArray[i]->turnsCooldown, playerHealth);
            if(playerHealth == 0) {
                emit player_die();
                return;
            }
        }
        else if(enemyArray[i]->healed) emit enemy_update_health(i, enemyArray[i]->turnsCooldown, enemyArray[i]->currentHealth);
    }
}

int CombatGame::player_recieve_damage(int damage) {
    int trueDamage = static_cast<int>(damage * (100.0 / (100.0 + playerDefense)));
    playerHealth -= trueDamage;
    if(playerHealth < 0) playerHealth = 0;
    return playerHealth;
}

void CombatGame::ability_attack_enemy(int petPosition, Type TYPE, int damage) {
    for(int i = 0; i < 5; ++i) if(enemyArray[i] != nullptr) {
        int enemyHealth;
        if(static_cast<int>(enemyArray[i]->TYPE) == static_cast<int>(TYPE)+1) enemyHealth = enemyArray[i]->recieve_damage(damage*2);
        else enemyHealth = enemyArray[i]->recieve_damage(damage);
        emit pet_attack_enemy(petPosition, i, enemyHealth, false);
        if(enemyArray[i]->currentHealth <= 0) {
            delete enemyArray[i];
            enemyArray[i] = nullptr;
            emit enemy_die(i);

            bool clear = true;
            for(int j = 0; j < 5; ++j) if(enemyArray[j] != nullptr) clear = false;
            if(clear == true) {
                emit level_cleared();
                return;
            }
        }
    }
}

void CombatGame::ability_heal_player(int petPosition, int heal) {
    playerHealth += heal;
    emit player_update_health(petPosition, playerHealth);
}

void CombatGame::start_combat(const vector<Combo>& combos) {
    pets_attack(combos);
    enemies_attack();
    ++turnNumber;
    for(int i = 0; i < 5; ++i) if(petArray[i]->gain_special_attack() == true) {
        emit special_attack_ready(i);
    }
    emit animation_end(false);
}

void CombatGame::activate_pet_ability(int petPosition) {
    int ability = petArray[petPosition]->special_ability();
    if(ability == 1) ability_attack_enemy(petPosition, petArray[petPosition]->TYPE, (petArray[petPosition]->ATTACK)*10);
    else ability_heal_player(petPosition, (petArray[petPosition]->DEFENSE)*5);
}
