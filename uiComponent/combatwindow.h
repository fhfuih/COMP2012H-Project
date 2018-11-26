#ifndef COMBATWINDOW_H
#define COMBATWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QKeyEvent>
//#include <QDebug>

#include "Utils.h"
#include "square.h"

namespace Ui {
class CombatGameWindow;
}

class Square;

class CombatGameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CombatGameWindow(int PlayerHealth, int EnemyMonsterHealth[5], int PetMonsterID[5], int EnemyMonsterID[5],QWidget *parent = nullptr);
    ~CombatGameWindow() override;

private:
    int PetMonsterID[5];
    int EnemyMonsterID[5];

    int* select;

    int PlayerHealth;

    int EnemyMonsterHealth[5];

    Ui::CombatGameWindow *ui;

    /* Functions
     */
    void Attack(int PetMonster, int PetMonsterAttack, int EnemyMonster);//某個寵物對某個敵人造成damage amount的傷害
    void SkillReady(int PetMonsterIndex);
    void SpecialAbilityOne(int PetMonsterIndex, int PetMonsterAttack);//對所有敵人造成attack傷害
    void SpecialAbilityTwo(int NewHealth);//更新血條
    void Hurt(int EnemyAttack);//怪物攻擊
    void EnemySkillOne(int NewMonsterHealth, int EnemyMonsterIndex);

    void EnemyDeath(int EnemyMonsterIndex);
    void GameOver();

    /* signals and slots */
signals:
    void PetMonsterIndexToID(int ID[5]);
    void EnemyMonsterIndexToID(int ID[5]);
    void PetAttackEnemy(int PetMonsterIndex, int EnemyMonsterIndex, int NewEnemyHealth);
    void PetSkillReady(int PetMonsterIndex);
    void PlayerHealthChange(int NewHealth);
    void EnemyHealthChange(int EnemyMonsterIndex, int NewEnemyHealth);




    void SelectedPetMonster(int PetMonster);
};


#endif // COMBATWINDOW_H
