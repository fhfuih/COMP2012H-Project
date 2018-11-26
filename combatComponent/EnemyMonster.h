#ifndef EnemyMonster_h
#define EnemyMonster_h

#include "AbstractMonster.h"

class EnemyMonster : public AbstractMonster {
    Q_OBJECT
public:
    EnemyMonster(int position, int ID);
    
    virtual void attack() override;
    virtual void special_ability() override;
    
    int get_current_health() const;
protected:
    int currentHealth;
    
    void die();
    
private slots:
    void recieve_damage(int position, int damage);

signals:
    void damage_player(int damage);

    friend class CombatGame;
};

#endif /* EnemyMonster_h */
