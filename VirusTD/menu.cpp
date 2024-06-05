#include "menu.h"
#include "ui_menu.h"
#include "gc.h"
#include "mainwindow.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    ui->backButton->hide();
    ui->instructions->hide();
    ui->howItWorksLabel->hide();
    ui->naturalKillerPicture->setVisible(false);
    ui->memoryBPicture->setVisible(false);
    ui->boneMarrowPicture->setVisible(false);
    ui->naturalKillerPicture->setStyleSheet("QPushButton { background-color: transparent }");
    ui->memoryBPicture->setStyleSheet("QPushButton { background-color: transparent }");
    ui->boneMarrowPicture->setStyleSheet("QPushButton { background-color: white }");
}

Menu::~Menu()
{
    delete ui;
    delete gameWindow;
}

void Menu::on_playButton_clicked()
{
    deadWorld = new DeadWorld();
    controller = new GC(nullptr, deadWorld); //MainWindow is responsible for deleting this
    gameWindow = new MainWindow(controller);
    gameWindow->show();
    this->hide();
}


void Menu::on_exitButton_clicked() //Hack: This crashes instead of quitting for some reason
{
    this->hide();
    this->close();
}


void Menu::on_backButton_clicked()
{
    ui->naturalKillerPicture->setVisible(false);
    ui->memoryBPicture->setVisible(false);
    ui->boneMarrowPicture->setVisible(false);
    ui->instructions->hide();
    ui->howItWorksLabel->hide();
    ui->backButton->hide();

    ui->playButton->show();
    ui->instructionsButton->show();
    ui->howButton->show();
    ui->exitButton->show();
    ui->titleLabel->show();
}


void Menu::on_instructionsButton_clicked()
{
    ui->naturalKillerPicture->setVisible(true);
    ui->memoryBPicture->setVisible(true);
    ui->boneMarrowPicture->setVisible(true);
    ui->instructions->show();
    ui->backButton->show();

    ui->playButton->hide();
    ui->instructionsButton->hide();
    ui->howButton->hide();
    ui->exitButton->hide();
    ui->titleLabel->hide();
}


void Menu::on_howButton_clicked()
{
    ui->howItWorksLabel->show();
    ui->backButton->show();

    ui->playButton->hide();
    ui->instructionsButton->hide();
    ui->howButton->hide();
    ui->exitButton->hide();
    ui->titleLabel->hide();
}

