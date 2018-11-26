#include"combatwindow.h"
#include "ui_gamewindow.h"
#include <string>
using std::string;

CombatGameWindow::CombatGameWindow(int PlayerHealth, int EnemyMonsterHealth[5], int PetMonsterID[5], int EnemyMonsterID[5],QWidget *parent):
    QWidget(parent),
    select(nullptr),
    PlayerHealth(PlayerHealth),
    ui(new Ui::CombatGameWindow)
{
    for (int i=0;i<5;i++){
        this->PetMonsterID[i] = PetMonsterID[i];
        this->EnemyMonsterID[i] = EnemyMonsterID[i];
        this->EnemyMonsterHealth[i] = EnemyMonsterHealth[i];
    }
    ui->setupUi(this);
    emit PetMonsterIndexToID(PetMonsterID);
    emit EnemyMonsterIndexToID(EnemyMonsterID);
}

void CombatGameWindow::Attack(int PetMonster, int PetMonsterAttack, int EnemyMonster){
    EnemyMonsterHealth[EnemyMonster] -= PetMonsterAttack;
    if (EnemyMonsterHealth[EnemyMonster]<=0){
        EnemyMonsterHealth[EnemyMonster]=0;
    }
    emit PetAttackEnemy(PetMonster,EnemyMonster,EnemyMonsterHealth[EnemyMonster]);

    if (EnemyMonsterHealth[EnemyMonster]==0){
        EnemyDeath(EnemyMonster);
    }
}

void CombatGameWindow::SkillReady(int PetMonsterIndex){
    emit PetSkillReady(PetMonsterIndex);
}

void CombatGameWindow::SpecialAbilityOne(int PetMonsterIndex, int PetMonsterAttack){
    for (int i=0;i<5;i++){
        Attack(PetMonsterIndex,PetMonsterAttack,i);
    }
}

void CombatGameWindow::SpecialAbilityTwo(int NewHealth){
    PlayerHealth = NewHealth;
    emit PlayerHealthChange(PlayerHealth);
}

void CombatGameWindow::Hurt(int EnemyAttack){
    PlayerHealth = PlayerHealth - EnemyAttack;
    if (PlayerHealth<=0){
        PlayerHealth = 0;
    }
    emit PlayerHealthChange(PlayerHealth);
    if (PlayerHealth==0){
        GameOver();
    }
}

void CombatGameWindow::EnemySkillOne(int NewMonsterHealth, int EnemyMonsterIndex){
    EnemyMonsterHealth[EnemyMonsterIndex] = NewMonsterHealth;
    emit EnemyHealthChange(EnemyMonsterIndex, NewMonsterHealth);
}

void CombatGameWindow::EnemyDeath(int EnemyMonsterIndex){
    EnemyMonsterID[EnemyMonsterIndex]=-1;
    EnemyMonsterHealth[EnemyMonsterIndex]=0;
    emit EnemyDie(EnemyMonsterIndex);
}

void CombatGameWindow::GameOver(){
    emit PlayerDie();
}
