#include"CombatGameWindow.h"
#include "ui_combatgamewindow.h"
#include <string>
using std::string;

CombatGameWindow::CombatGameWindow(int PetMonsterID[5], int EnemyMonsterID[5], QWidget *parent):
    QWidget(parent),
    ui(new Ui::CombatGameWindow)
{
    /* Initialization */
    int PlayerHealth = 0;
    for (int i=0;i<5;i++){
        this->PetMonsterID[i] = PetMonsterID[i];
        this->EnemyMonsterID[i] = EnemyMonsterID[i];
        if(EnemyMonsterID[i] != -1) this->EnemyMonsterHealth[i] = fileLoader().getHealth(EnemyMonsterID[i]);
        PlayerHealth += fileLoader().getHealth(PetMonsterID[i]);
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

CombatGameWindow::~CombatGameWindow() {
    delete ui;
}

void CombatGameWindow::GameOver() {
    //game over sequence
}

void CombatGameWindow::PetAttackEnemy(int PetMonsterIndex, int EnemyMonsterIndex, int NewEnemyHealth) {
    //pet jumps up
    //enemy glows red
    enemyHealthBarArray[EnemyMonsterIndex]->setValue(NewEnemyHealth);
}

void CombatGameWindow::EnemyAttackPlayer(int EnemyAttackCooldown, int NewPlayerHealth) {
    //update enemy attack cooldown
    ui->PlayerHealth->setValue(NewPlayerHealth);
}

void CombatGameWindow::PlayerHealthChange(int NewPlayerHealth) {
    ui->PlayerHealth->setValue(NewPlayerHealth);
}

void CombatGameWindow::EnemyHealthChange(int EnemyMonsterIndex, int NewEnemyHealth) {
    enemyHealthBarArray[EnemyMonsterIndex]->setValue(NewEnemyHealth);
}

void CombatGameWindow::PetSkillReady(int PetMonsterIndex){
    //pet monster becomes shiny/highlighted
}

void CombatGameWindow::EnemyDie(int EnemyMonsterIndex){
    enemyHealthBarArray[EnemyMonsterIndex]->setValue(0);
    enemyImageArray[EnemyMonsterIndex]->hide();
    //enemy disappears
}

void CombatGameWindow::PlayerDie(){
    ui->PlayerHealth->setValue(0);
    GameOver();
    //update player graphic?
}
