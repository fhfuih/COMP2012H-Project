#ifndef COMBATWINDOW_H
#define COMBATWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QProgressBar>
#include <QThread>

#include "Utils.h"
#include "fileloader.h"


namespace Ui {
class CombatGameWindow;
}

class CombatGameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CombatGameWindow(int PetMonsterID[5], int EnemyMonsterID[5], QWidget *parent = nullptr);
    ~CombatGameWindow() override;

private:
    QLabel* petImageArray[PET_TEAM_SIZE];
    QLabel* enemyImageArray[MAXIMAL_ENEMY_TEAM_SIZE];
    QProgressBar* enemyHealthBarArray[MAXIMAL_ENEMY_TEAM_SIZE];

    int PetMonsterID[PET_TEAM_SIZE];
    int EnemyMonsterID[MAXIMAL_ENEMY_TEAM_SIZE];
    int EnemyMonsterHealth[5];
    int PlayerHealth;

    Ui::CombatGameWindow *ui;

    /* functions */
    void GameOver();

    /* signals and slots */
public slots:
    void PetAttackEnemy(int PetMonsterIndex, int EnemyMonsterIndex, int NewEnemyHealth);
    void EnemyAttackPlayer(int EnemyAttackCooldown, int NewPlayerHealth);
    void PlayerHealthChange(int NewPlayerHealth);
    void EnemyHealthChange(int EnemyMonsterIndex, int NewEnemyHealth);
    void PetSkillReady(int PetMonsterIndex);
    void EnemyDie(int EnemyMonsterIndex);
    void PlayerDie();

signals:
    void PetMonsterIndexToID(int ID[5]);
    void EnemyMonsterIndexToID(int ID[5]);
    void SelectedPetMonster(int PetMonster);
};


#endif // COMBATWINDOW_H
