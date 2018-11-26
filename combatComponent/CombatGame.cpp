#include "CombatGame.h"

CombatGame::CombatGame() :
    turnNumber(1),
    playerHealth(0),
    playerDefense(0)
{
    for(int i = 0; i < 5; ++i) petArray[i] = new PetMonster(i, 1, &enemyArray);
    for(int i = 0; i < 5; ++i) enemyArray[i] = new EnemyMonster(i, 1);
    
    for(int i = 0; i < 5; ++i) playerHealth += petArray[i]->get_health();
    for(int i = 0; i < 5; ++i) playerDefense += petArray[i]->get_defense();
    
    //connect(game_window->get_orb_game(), &OrbGame::combo_finish, this, &CombatGame::start_combat);
}

CombatGame::~CombatGame() {
    for(int i = 0; i < 5; ++i) if(petArray[i] != nullptr) delete petArray[i];
    for(int i = 0; i < 5; ++i) if(enemyArray[i] != nullptr) delete enemyArray[i];
}

void CombatGame::pets_attack(vector<Combo> combos) {
    for(int i = 0; i < 5; ++i) {
        petArray[i]->calculate_damage(combos);
        int targetEnemy = petArray[i]->attack();
        int trueDamage = enemyArray[targetEnemy]->recieve_damage(petArray[i]->outputDamage);
        if(enemyArray[targetEnemy]->currentHealth <= 0) {
            delete enemyArray[targetEnemy];
            enemyArray[targetEnemy] = nullptr;
        }
        emit pet_attack_enemy(targetEnemy, trueDamage);
    }
}

void CombatGame::enemies_attack() {
    for(int i = 0; i < 5; ++i) {
        int enemyDamage = enemyArray[i]->attack();
        if(enemyDamage != 0) {
            int trueDamage = player_recieve_damage(enemyDamage);
            emit enemy_attack_player(enemyArray[i]->turnsCooldown, trueDamage);
        }
        else emit enemy_update_health(i, enemyArray[i]->currentHealth);
    }
}

int CombatGame::player_recieve_damage(int damage) {
    int trueDamage = damage * (100.0 / (100.0 + playerDefense));
    playerHealth -= trueDamage;
    if(playerHealth <= 0) game_over();
    return trueDamage;
}

void CombatGame::ability_attack_enemy(Type TYPE, int damage) {
    for(int i = 0; i < 5; ++i) {
        int abilityDamage;
        if(static_cast<int>(enemyArray[i]->TYPE) == static_cast<int>(TYPE)+1) abilityDamage = enemyArray[i]->recieve_damage(damage*2);
        else abilityDamage = enemyArray[i]->recieve_damage(damage);
        emit pet_attack_enemy(i, abilityDamage);
    }
}

void CombatGame::ability_heal_player(int heal) {
    playerHealth += heal;
    emit player_update_health(playerHealth);
}

void CombatGame::game_over() {
    playerHealth = 0;
    //do something
}

void CombatGame::start_combat(vector<Combo> combos) {
    pets_attack(combos);
    enemies_attack();
    ++turnNumber;
    for(int i = 0; i < 5; ++i) if(petArray[i]->gain_special_attack() == true) {
        emit special_attack_ready(i);
    }
}

void CombatGame::pet_ability(int petPosition) {
    int ability = petArray[petPosition]->special_ability();
    if(ability == 0) ability_attack_enemy(petArray[petPosition]->TYPE, (petArray[petPosition]->ATTACK)*2);
    else ability_heal_player((petArray[petPosition]->DEFENSE)*5);
}
