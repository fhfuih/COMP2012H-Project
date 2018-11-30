#ifndef COMBATWINDOW_H
#define COMBATWINDOW_H

#include <QRegularExpression>
#include <QPushButton>
#include <QWidget>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QProgressBar>
#include <QThread>
using std::vector;

#include "Utils.h"
#include "fileloader.h"


namespace Ui {
class CombatGameWindow;
}

class CombatGameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CombatGameWindow(int level, int PetMonsterID[5], QWidget *parent = nullptr);
    ~CombatGameWindow() override;

private:
    QPushButton* petImageArray[PET_TEAM_SIZE];
    QLabel* enemyImageArray[MAXIMAL_ENEMY_TEAM_SIZE];
    QProgressBar* enemyHealthBarArray[MAXIMAL_ENEMY_TEAM_SIZE];
    QLabel* enemyClawArray[MAXIMAL_ENEMY_TEAM_SIZE];
    QLabel* enemyActionArray[MAXIMAL_ENEMY_TEAM_SIZE];
    QLabel* petActionArray[MAXIMAL_ENEMY_TEAM_SIZE];

    int PetMonsterID[PET_TEAM_SIZE];
    int EnemyMonsterID[MAXIMAL_ENEMY_TEAM_SIZE];
    int EnemyMonsterHealth[5];
    int PlayerHealth;
    bool SkillReady[PET_TEAM_SIZE];
    int level;
    bool animationStatus;
    bool gameOver;

    Ui::CombatGameWindow *ui;

    /* signals and slots */
public slots:
    void PetAttackEnemy(int PetMonsterIndex, int EnemyMonsterIndex, int NewEnemyHealth, bool CriticalHit);
    void EnemyAttackPlayer(int EnemyMonsterIndex, int EnemyAttackCooldown, int NewPlayerHealth);
    void PlayerHealthChange(int PetMonsterIndex, int NewPlayerHealth);
    void EnemyHealthChange(int EnemyMonsterIndex, int EnemyAttackCooldown, int NewEnemyHealth);
    void PetSkillReady(int PetMonsterIndex);
    void EnemyDie(int EnemyMonsterIndex);
    void PlayerDie();
    void LevelCleared();
    void UpdateAnimationStatus(bool animationStatus);

private slots:
    void onPetButtonClicked();
    void on_BackButton_clicked();

signals:
    void SelectedPetMonster(int PetMonster);
    void gameFinished();
};


#endif // COMBATWINDOW_H
