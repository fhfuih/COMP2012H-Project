#include "EnemyMonster.h"

EnemyMonster::EnemyMonster(int position, int ID, AbstractMonster* (*enemyArray)[5]) :
    AbstractMonster(position, ID, enemyArray),
{
    currentHealth = HEALTH;
    turnsAttack = 0;
}

void EnemyMonster::attack() {
    //when turnsAttak%TURNS == 0, attack player health
}

void EnemyMonster::special_ability() {
    //when turnsAbility == 0, attack with ability (or by RNG)
    //special ability depends on ID
}

int EnemyMonster::calculate_damage() {
    //formula: enemyAttack
    //player defense: trueDamage = enemyAttack * [100 / (100 + playerDefense)]
}

void EnemyMonster::animation() {
    //some UI code
}
