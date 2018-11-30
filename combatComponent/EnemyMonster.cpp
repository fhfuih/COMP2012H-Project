#include "EnemyMonster.h"

EnemyMonster::EnemyMonster(int position, int ID) :
    AbstractMonster(position, ID)
{
    currentHealth = HEALTH;
}

int EnemyMonster::attack() {
    healed = false;
    if(turnsCooldown == 0) {
        turnsCooldown = COOLDOWN;
        if(rand()%100 < 50) return special_ability();
        return ATTACK;
    }
    else {
        --turnsCooldown;
        return 0;
    }
}

int EnemyMonster::special_ability() {
    switch((ID-200)%5 + 1) {
    case 1: case 2:
        return ATTACK*3;
    case 3: case 4:
        if(currentHealth == HEALTH) return ATTACK;
        currentHealth += DEFENSE*3;
        if(currentHealth > HEALTH) currentHealth = HEALTH;
        healed = true;
        return 0;
    case 0:
        currentHealth += DEFENSE*6;
        if(currentHealth > HEALTH) currentHealth = HEALTH;
        return ATTACK*6;
    default:
        return ATTACK;
    }
}

int EnemyMonster::get_current_health() const {
    return currentHealth;
}

int EnemyMonster::recieve_damage(int damage) {
    int trueDamage = static_cast<int>(damage * (100.0 / (100.0 + DEFENSE)));
    currentHealth -= trueDamage;
    if(currentHealth < 0) currentHealth = 0;
    return currentHealth;
}
