#include "EnemyMonster.h"

EnemyMonster::EnemyMonster(int position, int ID) :
    AbstractMonster(position, ID)
{
    currentHealth = HEALTH;
}

void EnemyMonster::attack() {
    if(turnsCooldown == 0) {
        if(rand()%100 < 20) special_ability();
        emit damage_player(ATTACK);
    }
    else --turnsCooldown;
}

void EnemyMonster::special_ability() {
    //special ability depends on ID
}

void EnemyMonster::die() {
    //do something
}

void EnemyMonster::animation() {
    //some UI code
}

void EnemyMonster::recieve_damage(int position, int damage) {
    if(POSITION == position) currentHealth -= damage * (100.0 / (100.0 + DEFENSE));
    if(currentHealth <= 0) die();
}
