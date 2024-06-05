#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <QWidget>
#include "deadworld.h"
#include "gc.h"
#include "mainwindow.h"

namespace Ui {
class EndScreen;
}

class EndScreen : public QWidget
{
   Q_OBJECT

public:
   /**
    * @brief EndScreen is the constructor of EndScreen class which creates a widget for visual
    * representation of the player result
    * @param result whether they won or not
    * @param parent is assign to a nullptr
    */
   explicit EndScreen(int result, bool ifWin, QMainWindow* oldWindow, QWidget *parent = nullptr);

   /**
    * @brief Destroys the EndScreen object
    */
   ~EndScreen();

private slots:
   /**
    * @brief on_yesButton_pressed trigger when the yes button is clicked
    */
   void on_yesButton_pressed();

   /**
    * @brief on_noButton_pressed trigger when the no button is clicked
    */
   void on_noButton_pressed();

private:
   Ui::EndScreen *ui;
   QMainWindow* oldWindow;
   int round;
   bool result;

};

#endif // ENDSCREEN_H
