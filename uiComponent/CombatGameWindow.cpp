#include"CombatGameWindow.h"
#include "ui_combatgamewindow.h"
#include <string>
using std::string;

CombatGameWindow::CombatGameWindow(int PlayerHealth, int EnemyMonsterHealth[5], int PetMonsterID[5], int EnemyMonsterID[5],QWidget *parent):
    QWidget(parent),
    select(nullptr),
    PlayerHealth(PlayerHealth),
    ui(new Ui::CombatGameWindow)
{
    /* Initialization */
    for (int i=0;i<5;i++){
        this->PetMonsterID[i] = PetMonsterID[i];
        this->EnemyMonsterID[i] = EnemyMonsterID[i];
        this->EnemyMonsterHealth[i] = EnemyMonsterHealth[i];
    }

    /* Fiddling with UI */
    ui->setupUi(this);
    for (int i = 0; i < MAXIMAL_ENEMY_TEAM_SIZE; i++) {
        /* enemy image */
        QLabel* image = ui->EnemyView->findChild<QLabel*>(QString("EnemyImage_%1").arg(i));
        enemyImageArray[i] = image;
        // set image scale-to-fit
        image->setScaledContents(true);

        /* enemy hbar */
        QProgressBar* hbar = ui->EnemyView->findChild<QProgressBar*>(QString("EnemyHealth_%1").arg(i));
        enemyHealthBarArray[i] = hbar;

        /* enemy view */
        QWidget* view = hbar->parentWidget();
        // set holding the place when hiding
        auto sp = view->sizePolicy();
        sp.setRetainSizeWhenHidden(true);
        view->setSizePolicy(sp);

        /* Actual content */
        int id = EnemyMonsterID[i];
        if (id == -1) {
            view->hide();
        } else {
            hbar->setMaximum(EnemyMonsterHealth[i]);
            hbar->setValue(EnemyMonsterHealth[i]);
            QString image_name = QString(":/resource/%1.png").arg(id);
            image->setPixmap(QPixmap(image_name));
        }
    }
    for (int i = 0; i < PET_TEAM_SIZE; i++) {
        /* pet image */
        QLabel* image = ui->PetView->findChild<QLabel*>(QString("PetImage_%1").arg(i));
        petImageArray[i] = image;
        // set image scale-to-fit
        image->setScaledContents(true);
        // set holding the place when hiding
        auto sp = image->sizePolicy();
        sp.setRetainSizeWhenHidden(true);
        image->setSizePolicy(sp);
        // set image content
        int id = PetMonsterID[i];
        QString image_name = QString(":/resource/%1.png").arg(id);
        image->setPixmap(QPixmap(image_name));
    }
    /* player hbar */
    ui->PlayerHealth->setMaximum(PlayerHealth);
    ui->PlayerHealth->setValue(PlayerHealth);


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
