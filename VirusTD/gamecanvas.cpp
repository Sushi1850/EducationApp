#include "gamecanvas.h"

#include <QMouseEvent>

GameCanvas::GameCanvas(QWidget *parent) : QGraphicsView(parent)
{

}

void GameCanvas::mousePressEvent(QMouseEvent *event)
{
    emit mousePressed(event);
}

