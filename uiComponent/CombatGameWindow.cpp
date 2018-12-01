#include"CombatGameWindow.h"
#include "ui_combatgamewindow.h"
#include <string>
using std::string;

CombatGameWindow::CombatGameWindow(int level, int PetMonsterID[5], QWidget *parent):
    QWidget(parent),
    SkillReady(),
    level(level),
    animationStatus(false),
    gameOver(false),
    ui(new Ui::CombatGameWindow)
{
    /* Initialization */
    vector<int> monster {fileLoader().getLevel(level)};
    int EnemyMonsterID[5] {monster[0], monster[1], monster[2], monster[3], monster[4]};

    PlayerHealth = 0;
    for (int i=0;i<5;i++){
        this->PetMonsterID[i] = PetMonsterID[i];
        this->EnemyMonsterID[i] = EnemyMonsterID[i];
        if(EnemyMonsterID[i] != -1) this->EnemyMonsterHealth[i] = fileLoader().getHealth(EnemyMonsterID[i]);
        PlayerHealth += fileLoader().getHealth(PetMonsterID[i]);
    }

    ui->setupUi(this);
    ui->background->setGeometry(0,0,COMBAT_WINDOW_WIDTH,COMBAT_WINDOW_HEIGHT);
    ui->background->setStyleSheet(QString("background-image: url(:/resource/CombatGameBackground%1.jpg);border-image: url(:/resource/CombatBorder.png)").arg(level+1));
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

        /* enemy claw */
        QLabel* claw = findChild<QLabel*>(QString("EnemyClaw_%1").arg(i));
        enemyClawArray[i] = claw;
        claw->hide();

        /* enemy sword */
        QLabel* enemy_action = findChild<QLabel*>(QString("EnemyAction_%1").arg(i));
        enemyActionArray[i] = enemy_action;
        enemy_action->hide();

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

        /* pet sword */
        QLabel* pet_action = findChild<QLabel*>(QString("PetAction_%1").arg(i));
        petActionArray[i] = pet_action;
        pet_action->hide();

        // set image content
        int id = PetMonsterID[i];
        QString image_name = QString(":/resource/%1_icon.png").arg(id);
        image->setIcon(QIcon(image_name));
        image->setIconSize(QSize(90, 90));
        image->setStyleSheet(QString("border-image: url(:/resource/Border pattern3.png); background-color:#000000"));
        connect(image, &QPushButton::clicked, this, &CombatGameWindow::onPetButtonClicked);
    }
    /* player hbar */
    ui->PlayerHealth->setMaximum(PlayerHealth);
    ui->PlayerHealth->setValue(PlayerHealth);
}

CombatGameWindow::~CombatGameWindow() {
    delete ui;
}

void CombatGameWindow::PetAttackEnemy(int PetMonsterIndex, int EnemyMonsterIndex, int NewEnemyHealth, bool CriticalHit) {
    if(CriticalHit) enemyClawArray[EnemyMonsterIndex]->setPixmap(QString(":/resource/clawCritical.png"));
    else enemyClawArray[EnemyMonsterIndex]->setPixmap(QString(":/resource/clawNormal.png"));

    petActionArray[PetMonsterIndex]->setPixmap(QString(":/resource/combatSword.png"));
    petActionArray[PetMonsterIndex]->show();
    enemyClawArray[EnemyMonsterIndex]->show();
    utils_delay(500);
    petActionArray[PetMonsterIndex]->hide();
    enemyClawArray[EnemyMonsterIndex]->hide();

    enemyHealthBarArray[EnemyMonsterIndex]->setValue(NewEnemyHealth);
}

void CombatGameWindow::EnemyAttackPlayer(int EnemyMonsterIndex, int EnemyAttackCooldown, int NewPlayerHealth) {
    //update enemy attack cooldown
    enemyActionArray[EnemyMonsterIndex]->setPixmap(QString(":/resource/combatSword.png"));
    enemyActionArray[EnemyMonsterIndex]->show();
    utils_delay(500);
    enemyActionArray[EnemyMonsterIndex]->hide();

    ui->PlayerHealth->setValue(NewPlayerHealth);
}

void CombatGameWindow::PlayerHealthChange(int PetMonsterIndex, int NewPlayerHealth) {
    petActionArray[PetMonsterIndex]->setPixmap(QString(":/resource/combatHeal.png"));
    petActionArray[PetMonsterIndex]->show();
    utils_delay(500);
    petActionArray[PetMonsterIndex]->hide();

    ui->PlayerHealth->setValue(NewPlayerHealth);
}

void CombatGameWindow::EnemyHealthChange(int EnemyMonsterIndex, int EnemyAttackCooldown, int NewEnemyHealth) {
    //update enemy attack cooldown
    enemyActionArray[EnemyMonsterIndex]->setPixmap(QString(":/resource/combatHeal.png"));
    enemyActionArray[EnemyMonsterIndex]->show();
    utils_delay(500);
    enemyActionArray[EnemyMonsterIndex]->hide();

    enemyHealthBarArray[EnemyMonsterIndex]->setValue(NewEnemyHealth);
}

void CombatGameWindow::PetSkillReady(int PetMonsterIndex){
    //pet monster becomes shiny/highlighted
    SkillReady[PetMonsterIndex] = true;
    petImageArray[PetMonsterIndex]->setCursor(Qt::PointingHandCursor);
    petImageArray[PetMonsterIndex]->setStyleSheet(QString("border-image: url(:/resource/Border pattern3.png); background-image: url(:/resource/SkillReady.png);"));
}

void CombatGameWindow::EnemyDie(int EnemyMonsterIndex){
    enemyHealthBarArray[EnemyMonsterIndex]->setValue(0);
    enemyHealthBarArray[EnemyMonsterIndex]->hide();
    enemyImageArray[EnemyMonsterIndex]->hide();
    //enemy disappears
}

void CombatGameWindow::PlayerDie(){
    gameOver = true;
    ui->PlayerHealth->setValue(0);
    ui->LoseLabel->show();
    ui->BackButton->show();
    //game over sequence
}

void CombatGameWindow::LevelCleared() {
    gameOver = true;
    ui->WinLabel->show();
    ui->BackButton->show();
    //clear level sequence
}

void CombatGameWindow::onPetButtonClicked()
{
    if(animationStatus) return;
    if(gameOver) return;

    QObject* obj = sender();
    int t = obj->objectName().indexOf(QRegularExpression("[0-9]"));
    int index = obj->objectName()[t].toLatin1() - '0';
    if (!SkillReady[index]) {
        return;
    }
    emit SelectedPetMonster(index);
    SkillReady[index] = false;
    petImageArray[index]->setCursor(Qt::ArrowCursor);
    petImageArray[index]->setStyleSheet(QString("border-image: url(:/resource/Border pattern3.png); background-color:#000000"));
}

void CombatGameWindow::UpdateAnimationStatus(bool animationStatus) {
    this->animationStatus = animationStatus;
}

void CombatGameWindow::on_BackButton_clicked()
{
    emit gameFinished();
}
