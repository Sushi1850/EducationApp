#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include <QGraphicsView>
//#include <QtWidgets>
#include <QWidget>
#include <QDebug>

/**
* @brief The GameCanvas class is main screen of the education game and it is used
* to display the information from the model
*/
class GameCanvas : public QGraphicsView
{
   Q_OBJECT
public:
   /**
    * @brief GameCanvas is the constructor of the class
    * @param parent the Parent widget of this object
    */
   GameCanvas(QWidget *parent = 0);
protected:
   /**
    * @brief mousePressEvent is called when a mouse has been pressed
    * @param event is the QMouseEvent that comes with to know which button is clicked
    */
   void mousePressEvent(QMouseEvent *event);
signals:
   /**
    * @brief mousePressed is a signal that alerts a slot in the model
    * @param e the QMouseEvent that was trigger when mousePressEvent was activated
    */
   void mousePressed(QMouseEvent *e);
};

#endif // GAMECANVAS_H

