#include"CombatGameWindow.h"
#include "ui_combatgamewindow.h"
#include <string>
using std::string;

CombatGameWindow::CombatGameWindow(int PetMonsterID[5], int EnemyMonsterID[5], QWidget *parent):
    QWidget(parent),
    ui(new Ui::CombatGameWindow)
{
    /* Initialization */
    PlayerHealth = 0;
    for (int i=0;i<5;i++){
        this->PetMonsterID[i] = PetMonsterID[i];
        this->EnemyMonsterID[i] = EnemyMonsterID[i];
        if(EnemyMonsterID[i] != -1) this->EnemyMonsterHealth[i] = fileLoader().getHealth(EnemyMonsterID[i]);
        PlayerHealth += fileLoader().getHealth(PetMonsterID[i]);
    }

    ui->setupUi(this);
    /* Fiddling with enemy UI */
    ui->background->setStyleSheet(QString("background-image: url(:/resource/CombatGameBackground%1.jpg);").arg(rand()%6+1));
    for (int i = 0; i < MAXIMAL_ENEMY_TEAM_SIZE; i++) {
        /* enemy image */
        QLabel* image = findChild<QLabel*>(QString("EnemyImage_%1").arg(i));
        enemyImageArray[i] = image;
        // set image scale-to-fit
        image->setScaledContents(true);

        /* enemy hbar */
        QProgressBar* hbar = findChild<QProgressBar*>(QString("EnemyHealth_%1").arg(i));
        enemyHealthBarArray[i] = hbar;

        /* enemy view */
        // set holding the place when hiding
        keepItsFuckingSize(image);
        keepItsFuckingSize(hbar);


        /* Actual content */
        int id = EnemyMonsterID[i];
        if (id == -1) {
            image->hide();
            hbar->hide();
        } else {
            hbar->setMaximum(EnemyMonsterHealth[i]);
            hbar->setValue(EnemyMonsterHealth[i]);
            QString image_name = QString(":/resource/%1.png").arg(id);
            image->setPixmap(QPixmap(image_name));
        }
    }
    /* Fiddling with pet UI */
    for (int i = 0; i < PET_TEAM_SIZE; i++) {
        /* pet image */
        QLabel* image = findChild<QLabel*>(QString("PetImage_%1").arg(i));
        petImageArray[i] = image;
        // set image scale-to-fit
        image->setScaledContents(true);
        // set holding the place when hiding
        keepItsFuckingSize(image);
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
