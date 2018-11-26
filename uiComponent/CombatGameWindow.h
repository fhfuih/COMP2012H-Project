#ifndef COMBATWINDOW_H
#define COMBATWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QProgressBar>

#include "Utils.h"
#include "fileloader.h"


namespace Ui {
class CombatGameWindow;
}



class CombatGameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CombatGameWindow(int PlayerHealth, int EnemyMonsterHealth[5], int PetMonsterID[5], int EnemyMonsterID[5],QWidget *parent = nullptr);
    ~CombatGameWindow() override;

private:
    QLabel* petImageArray[PET_TEAM_SIZE];
    QLabel* enemyImageArray[MAXIMAL_ENEMY_TEAM_SIZE];
    QProgressBar* enemyHealthBarArray[MAXIMAL_ENEMY_TEAM_SIZE];

    int PetMonsterID[PET_TEAM_SIZE];
    int EnemyMonsterID[MAXIMAL_ENEMY_TEAM_SIZE];

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

public slots:
    void PetMonsterIndexToID(int ID[5]);
    void EnemyMonsterIndexToID(int ID[5]);
    void PetAttackEnemy(int PetMonsterIndex, int EnemyMonsterIndex, int NewEnemyHealth);
    void PetSkillReady(int PetMonsterIndex);
    void PlayerHealthChange(int NewHealth);
    void EnemyHealthChange(int EnemyMonsterIndex, int NewEnemyHealth);
    void EnemyDie(int EnemyMonsterIndex);
    void PlayerDie();

signals:
    void SelectedPetMonster(int PetMonster);
};


#endif // COMBATWINDOW_H
