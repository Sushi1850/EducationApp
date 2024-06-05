#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class menu;
}
QT_END_NAMESPACE

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:

    /**
     * @brief on_playButton_clicked Slot is activated when
     * the play button is clicked
     */
    void on_playButton_clicked();

    /**
     * @brief on_exitButton_clicked Slot is activated when
     * the exit button is clicked
     */
    void on_exitButton_clicked();

    /**
     * @brief on_backButton_clicked Slot is activated when
     * the back button is clicked
     */
    void on_backButton_clicked();

    /**
     * @brief on_instructionsButton_clicked Slot is activated when
     * the instruction button is clicked
     */
    void on_instructionsButton_clicked();

    /**
     * @brief on_howButton_clicked Slot is activated when
     * the how button is clicked
     */
    void on_howButton_clicked();

private:
    Ui::menu *ui;
    GC* controller;
    DeadWorld* deadWorld;
    MainWindow* gameWindow;
};

#endif // MENU_H
