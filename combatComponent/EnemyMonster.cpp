#include "EnemyMonster.h"

EnemyMonster::EnemyMonster(int position, int ID) :
    AbstractMonster(position, ID)
{
    currentHealth = HEALTH;
}

int EnemyMonster::attack() {
    if(turnsCooldown == 0) {
        turnsCooldown = COOLDOWN;
        if(rand()%100 < 20) return special_ability();
        return ATTACK;
    }
    else {
        --turnsCooldown;
        return 0;
    }
}

int EnemyMonster::special_ability() {
    switch(ID%3) {
    case 0:
        return ATTACK*3;
    case 1:
        currentHealth += DEFENSE*3;
        if(currentHealth > HEALTH) currentHealth = HEALTH;
        return 0;
    case 2:
        currentHealth += DEFENSE*5;
        if(currentHealth > HEALTH) currentHealth = HEALTH;
        return ATTACK*5;
    }
}

int EnemyMonster::recieve_damage(int damage) {
    int trueDamage = damage * (100.0 / (100.0 + DEFENSE));
    currentHealth -= trueDamage;
    return trueDamage;
}
