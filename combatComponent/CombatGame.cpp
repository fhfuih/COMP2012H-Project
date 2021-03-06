#include "CombatGame.h"

CombatGame::CombatGame(int level, int petSelection[5]) :
    level(level),
    turnNumber(1),
    totalHealth(0),
    playerHealth(0),
    playerDefense(0),
    gameOver(false)
{
    vector<int> enemyID = fileLoader().getLevel(level);

    for(int i = 0; i < 5; ++i) petArray[i] = new PetMonster(i, petSelection[i], &enemyArray);
    for(int i = 0; i < 5; ++i) {
        if(enemyID[static_cast<unsigned long>(i)] != -1) enemyArray[i] = new EnemyMonster(i, enemyID[static_cast<unsigned long>(i)]);
        else enemyArray[i] = nullptr;
    }
    
    for(int i = 0; i < 5; ++i) totalHealth += petArray[i]->get_health();
    playerHealth = totalHealth;
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
        emit combat_text(QString(petArray[i]->NAME + " deals " + QString::number(enemyArray[targetEnemy]->trueDamage) + " damage to Enemy " + enemyArray[targetEnemy]->NAME + "."), true);
        if(petArray[i]->superEffective) emit combat_text(QString("It was super effective!"), true);
        if(petArray[i]->criticalHit) emit combat_text(QString("It was a critical hit!"), true);
        emit pet_attack_enemy(i, targetEnemy, enemyHealth, petArray[i]->criticalHit);
        if(enemyHealth == 0) {
            emit combat_text(QString(petArray[i]->NAME + " has defeated Enemy " + enemyArray[targetEnemy]->NAME + "."), true);
            delete enemyArray[targetEnemy];
            enemyArray[targetEnemy] = nullptr;
            emit enemy_die(targetEnemy);

            bool clear = true;
            for(int j = 0; j < 5; ++j) if(enemyArray[j] != nullptr) clear = false;
            if(clear == true) {
                emit combat_text(QString("\n=== You win! ===\n"), true);
                emit level_cleared();
                gameOver = true;
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
            emit combat_text(QString("Enemy " + enemyArray[i]->NAME + " deals " + QString::number(playerTrueDamage) + " damage to player."), false);
            emit enemy_attack_player(i, playerHealth);
            if(playerHealth == 0) {
                emit combat_text(QString("\n=== You have been defeated! ===\n"), false);
                emit player_die();
                gameOver = true;
                return;
            }
        }
        else if(enemyArray[i]->healed) {
            emit combat_text(QString("Enemy " + enemyArray[i]->NAME + " has healed."), false);
            emit enemy_update_health(i, enemyArray[i]->currentHealth);
        }
    }
}

int CombatGame::player_recieve_damage(int damage) {
    playerTrueDamage = static_cast<int>(damage * (100.0 / (100.0 + playerDefense)));
    playerHealth -= playerTrueDamage;
    if(playerHealth < 0) playerHealth = 0;
    return playerHealth;
}

void CombatGame::ability_attack_enemy(int petPosition, Type TYPE, int damage) {
    emit combat_text(QString(petArray[petPosition]->NAME + " activates special attack."), true);
    for(int i = 0; i < 5; ++i) if(enemyArray[i] != nullptr) {
        int enemyHealth;
        if(static_cast<int>(enemyArray[i]->TYPE)%TYPE_COUNT == (static_cast<int>(TYPE)+1)%TYPE_COUNT) enemyHealth = enemyArray[i]->recieve_damage(damage*2);
        else enemyHealth = enemyArray[i]->recieve_damage(damage);
        emit pet_attack_enemy(petPosition, i, enemyHealth, false);
        if(enemyArray[i]->currentHealth <= 0) {
            emit combat_text(QString(petArray[petPosition]->NAME + " has defeated Enemy " + enemyArray[i]->NAME + "."), true);
            delete enemyArray[i];
            enemyArray[i] = nullptr;
            emit enemy_die(i);

            bool clear = true;
            for(int j = 0; j < 5; ++j) if(enemyArray[j] != nullptr) clear = false;
            if(clear == true) {
                emit combat_text(QString("\n=== You win! ===\n"), true);
                emit level_cleared();
                gameOver = true;
                return;
            }
        }
    }
}

void CombatGame::ability_heal_player(int petPosition, int heal) {
    playerHealth += heal;
    if(playerHealth > totalHealth) playerHealth = totalHealth;
    emit combat_text(QString(petArray[petPosition]->NAME + " activates heal ability."), true);
    emit player_update_health(petPosition, playerHealth);
}

void CombatGame::start_combat(const vector<Combo>& combos) {
    pets_attack(combos);
    enemies_attack();
    for(int i = 0; i < 5; ++i) if(petArray[i]->gain_special_attack() == true) {
        emit special_attack_ready(i);
    }
    if(!gameOver) {
        emit combat_text(QString("\n--- Turn " + QString::number(turnNumber) + " end ---"), true);
        emit combat_text(QString("\n--- Turn " + QString::number(turnNumber) + " end ---"), false);
        ++turnNumber;
    }
    emit combat_end();
}

void CombatGame::activate_pet_ability(int petPosition) {
    emit pet_ability_animation(true);
    int ability = petArray[petPosition]->special_ability();
    if(ability == 1) ability_attack_enemy(petPosition, petArray[petPosition]->TYPE, (petArray[petPosition]->ATTACK)*10);
    else ability_heal_player(petPosition, (petArray[petPosition]->DEFENSE)*5);
    emit pet_ability_animation(false);
}
