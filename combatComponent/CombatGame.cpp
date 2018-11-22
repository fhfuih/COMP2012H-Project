#include "Orb.h"
#include "CombatGame.h"

CombatGame::CombatGame() :
    turnNumber(1),
    playerHealth(0),
    playerDefense(0)
{
    game_window = new GameWindow() //same window as OrbGame?
    
    for(int i = 0; i < 5; ++i) petArray[i] = new PetMonster(i, 1, &petArray, &enemyArray);
    for(int i = 0; i < 5; ++i) enemyArray[i] = new EnemyMonster(i, 1);
    
    for(int i = 0; i < 5; ++i) playerHealth += petArray[i]->get_health();
    for(int i = 0; i < 5; ++i) playerDefense += petArray[i]->get_defense();
    
    connect(OrbGame, &OrbGame::spin_finish, this, &CombatGame::start_combat); //link to OrbGame through game_window
    for(int i = 0; i < 5; ++i) connect(enemyArray[i], &EnemyMonster::damage_player, this, &CombatGame::player_recieve_damage);
    for(int i = 0; i < 5; ++i) for(int j = 0; j < 5; ++j) connect(petArray[i], &PetMonster::damage_enemy, enemyArray[j], &EnemyMonster::recieve_damage);
}

CombatGame::~CombatGame() {
    for(int i = 0; i < 5; ++i) delete petArray[i];
    for(int i = 0; i < 5; ++i) delete enemyArray[i];
}

void CombatGame::startGraphicUI() {
    game_window->show(); //should be same window as OrbGame?
}

GameWindow* CombatGame::get_game_window() const {
    return game_window;
}

int CombatGame::get_player_health() const {
    return playerHealth;
}

int CombatGame::get_player_defense() const {
    return playerDefense;
}

void CombatGame::pets_attack(vector<vector<int>> combos) {
    for(int i = 0; i < 5; ++i) {
        petArray[i]->calculate_damage(combos);
        petArray[i]->attack(); //wait a bit between each pet attack?
    }
}

void CombatGame::enemies_attack() {
    for(int i = 0; i < 5; ++i) enemyArray[i]->attack();
}

void CombatGame::game_over() {
    //do something
}

void CombatGame::start_combat(vector<vector<int>> combos) {
    pets_attack(combos); //wait for animation?
    enemies_attack(); //wait for animation?
    ++turnNumber;
}

void CombatGame::player_recieve_damage(int damage) {
    playerHealth -= damage * (100.0 / (100.0 + playerDefense));
    if(playerHealth <= 0) game_over();
}
