#ifndef EnemyMonster_h
#define EnemyMonster_h

#include "AbstractMonster.h"

class EnemyMonster : public AbstractMonster {
public:
    EnemyMonster(int position, int ID, EnemyMonster* (*enemyArray)[5]);
    ~EnemyMonster(); //some destructor
    
    virtual void attack() override;
    virtual void special_ability() override;
    
    int get_current_health() const;
protected:
    int currentHealth;
    
    void die();
    virtual void animation() override; //some animation?
    
private slots:
    void recieve_damage(int position, int damage);
    
signals:
    void damage_player(int damage);
}

#endif /* EnemyMonster_h */
