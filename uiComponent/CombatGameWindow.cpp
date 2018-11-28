#include"CombatGameWindow.h"
#include "ui_combatgamewindow.h"
#include <string>
using std::string;

CombatGameWindow::CombatGameWindow(int PetMonsterID[5], int EnemyMonsterID[5], int level, QWidget *parent):
    QWidget(parent),
    SkillReady(),
    level(level),
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
    ui->background->setStyleSheet(QString("background-image: url(:/resource/CombatGameBackground%1.jpg);").arg(level+1));
    ui->WinLabel->hide();
    ui->LoseLabel->hide();
    ui->BackButton->hide();
    /* Fiddling with enemy UI */
    for (int i = 0; i < MAXIMAL_ENEMY_TEAM_SIZE; i++) {
        /* enemy image */
        QLabel* image = findChild<QLabel*>(QString("EnemyImage_%1").arg(i));
        enemyImageArray[i] = image;

        /* enemy hbar */
        QProgressBar* hbar = findChild<QProgressBar*>(QString("EnemyHealth_%1").arg(i));
        enemyHealthBarArray[i] = hbar;

        /* enemy view */

        /* Actual content */
        int id = EnemyMonsterID[i];
        if (id == -1) {
            image->hide();
            hbar->hide();
        } else {
            hbar->setMaximum(EnemyMonsterHealth[i]);
            hbar->setValue(EnemyMonsterHealth[i]);
            QString image_name = QString(":/resource/%1.png").arg(id);
            image->setPixmap(image_name);
        }
    }
    /* Fiddling with pet UI */
    for (int i = 0; i < PET_TEAM_SIZE; i++) {
        /* pet image */
        QPushButton* image = findChild<QPushButton*>(QString("PetImage_%1").arg(i));
        petImageArray[i] = image;
        // set image content
        int id = PetMonsterID[i];
        QString image_name = QString(":/resource/%1.png").arg(id);
        image->setIcon(QIcon(image_name));
        image->setIconSize(QSize(150, 150));
        connect(image, &QPushButton::clicked, this, &CombatGameWindow::onPetButtonClicked);
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

void CombatGameWindow::PetAttackEnemy(int PetMonsterIndex, int EnemyMonsterIndex, int NewEnemyHealth) {
    //pet jumps up
    //enemy glows red
    enemyHealthBarArray[EnemyMonsterIndex]->setValue(NewEnemyHealth);
}

void CombatGameWindow::EnemyAttackPlayer(int EnemyMonsterIndex, int EnemyAttackCooldown, int NewPlayerHealth) {
    //enemy jumps up
    //update enemy attack cooldown
    ui->PlayerHealth->setValue(NewPlayerHealth);
}

void CombatGameWindow::PlayerHealthChange(int NewPlayerHealth) {
    ui->PlayerHealth->setValue(NewPlayerHealth);
}

void CombatGameWindow::EnemyHealthChange(int EnemyMonsterIndex, int EnemyAttackCooldown, int NewEnemyHealth) {
    enemyHealthBarArray[EnemyMonsterIndex]->setValue(NewEnemyHealth);
}

void CombatGameWindow::PetSkillReady(int PetMonsterIndex){
    //pet monster becomes shiny/highlighted
    SkillReady[PetMonsterIndex] = true;
    petImageArray[PetMonsterIndex]->setCursor(Qt::PointingHandCursor);
    petImageArray[PetMonsterIndex]->setStyleSheet("background-color:#fff791");
}

void CombatGameWindow::EnemyDie(int EnemyMonsterIndex){
    enemyHealthBarArray[EnemyMonsterIndex]->setValue(0);
    enemyImageArray[EnemyMonsterIndex]->hide();
    //enemy disappears
}

void CombatGameWindow::PlayerDie(){
    ui->PlayerHealth->setValue(0);
    ui->LoseLabel->show();
    ui->BackButton->show();
    //update player graphic?
    //game over sequence
}

void CombatGameWindow::LevelCleared() {
    ui->WinLabel->show();
    ui->BackButton->show();
    //clear level sequence
}

void CombatGameWindow::onPetButtonClicked()
{
    QObject* obj = sender();
    int t = obj->objectName().indexOf(QRegularExpression("[0-9]"));
    int index = obj->objectName()[t].toLatin1() - '0';
    if (!SkillReady[index]) {
        return;
    }
    emit SelectedPetMonster(index);
    SkillReady[index] = false;
    petImageArray[index]->setCursor(Qt::ArrowCursor);
    petImageArray[index]->setStyleSheet("background-color:transparent");
}

void CombatGameWindow::on_BackButton_clicked()
{
    emit gameFinished();
}
