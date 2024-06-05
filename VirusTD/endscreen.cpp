#include "endscreen.h"
#include "ui_endscreen.h"

EndScreen::EndScreen(int rounds, bool ifWin, QMainWindow* _oldWindow, QWidget *parent) :
   QWidget(parent),
   ui(new Ui::EndScreen),
   round(rounds),
   result(ifWin),
   oldWindow(_oldWindow)
{
    ui->setupUi(this);
    oldWindow->close();

    if(result == false)
    {
        ui->titleLabel->setText("Game Over");
        ui->resultLabel->setText("You made it to round: " + QString::number(round));
    }
    else
    {
        ui->titleLabel->setText("Congratulations");
        ui->resultLabel->setText("You beat all " + QString::number(round) + " rounds");
    }
 }

 EndScreen::~EndScreen()
 {
    delete ui;
 }

void EndScreen::on_yesButton_pressed()
{
    DeadWorld* deadWorld = new DeadWorld();
    GC* controller = new GC(nullptr, deadWorld);
    MainWindow* newGameWindow = new MainWindow(controller);
    newGameWindow->show();
    this->close();
}


void EndScreen::on_noButton_pressed()
{
    //Exit out the program
    QApplication::quit();
}

