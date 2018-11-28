#include "SelectionWindow.h"
#include "ui_SelectionWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->AttackBar->setMaximum(50);
    ui->DefenseBar->setMaximum(50);
    ui->HealthBar->setMaximum(300);
    ui->CooldownBar->setMaximum(5);
    for (int i = 0; i < PET_TYPES; i++) {
        int id = indexToId(i);
        petButtons[i] = new PetBox(id, this);
        connect(petButtons[i], &PetBox::mouse_entered, this, &MainWindow::entering_pet_box);
        connect(petButtons[i], &PetBox::mouse_clicked, this, &MainWindow::clicking_pet_box);

        QLabel* tag = findChild<QLabel*>(QString("Tag_%1").arg(i));
        tag->hide();
    }
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < PET_TYPES; i++) {
        delete petButtons[i];
    }
    delete ui;
}

void MainWindow::showThumbnail(int id)
{
    QString image_file = QString(":/resource/%1.png").arg(id);
    ui->PetThumb->setPixmap(image_file);
    ui->AttackBar->setValue(fileLoader().getAttack(id));
    ui->DefenseBar->setValue(fileLoader().getDefense(id));
    ui->HealthBar->setValue(fileLoader().getHealth(id));
    ui->CooldownBar->setValue(fileLoader().getCooldown(id));
    ui->PetName->setText(fileLoader().getName(id));
}

void MainWindow::refreshLevelDisplay() {
    /* !!!refrech level image.
     * the image shall show {level} + 1 */
    ui->LevelHint->setText(QString("Level %1").arg(level+1));
}

void MainWindow::on_Start_clicked()
{
    /* get selecte pets */
    int index = 0;
    for (int i = 0; i < PET_TYPES; i++) {
        if (petButtons[i]->get_selected() && index < PET_TEAM_SIZE) {
            pets[index++] = petButtons[i]->get_id();
        }
    }
    /* !!!construct a GameInstance */
    /* hide this window */
    hide();
}

void MainWindow::on_LevelSub_clicked()
{
    if (level <= 0) {
        return;
    }
    level--;
    refreshLevelDisplay();
}

void MainWindow::on_LevelAdd_clicked()
{
    if (level >= LEVEL_COUNT - 1) {
        return;
    }
    level++;
    refreshLevelDisplay();
}

void MainWindow::entering_pet_box(int id)
{
    showThumbnail(id);
}

void MainWindow::clicking_pet_box(int id)
{
    PetBox* thisPet = petButtons[idToIndex(id)];
//    QLabel* thisTag = findChild<QLabel*>(QString("Tag_%1").arg(idToIndex(id)));
//    thisTag->raise();
    if (thisPet->get_selected()) {
        thisPet->set_selected(false);
        selectedCount--;
//        thisTag->hide();
    }
    else if (selectedCount < PET_TEAM_SIZE) {
        thisPet->set_selected(true);
        selectedCount++;
//        thisTag->show();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit closed();
    event->accept();
}
