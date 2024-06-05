#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "Box2D/Box2D.h"
#include "deadworld.h"
#include "gc.h"
#include "QTimer"
#include "endscreen.h"
#include "qlabel.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a new MainWindow for playing Virus TD
     * @param game the game controller to communicate with
     * @param parent the Parent widget of this object
     */
    MainWindow(GC* game, QWidget *parent = nullptr);

    /**
     * @brief Destroys the MainWindow object
     */
    ~MainWindow();

public slots:
    /**
     * @brief updateDeadWorld Updates the scene of all the dead virus
     * @param positionX the x position of a dead enemy
     * @param positionY the y position of a dead enemy
     * @param iteration the current position of the vector of all dead enemies
     * @param size the total size of the vector
     * @param textureImage the image of a dead enemy
     */
    void updateDeadWorld(double positionX, double positionY, int iteration, int size, QImage textureImage);

    /**
     * @brief updateFrame Updates the gameCanvas with a new frame and bone balance
     * @param frame the new frame to be updated
     * @param boneBalance the new balance to be updated
     */
    void updateFrame(QPixmap frame, int boneBalance);

    /**
     * @brief waveEnemies Remove all of the dead enemies from the gameCanvas
     * @param virusNumber the amount of the virus dead
     */
    void waveEnemies(int virusNumber[4]);
signals:
    /**
     * @brief uiButtonPressed Signal is trigger when a ui button is pressed
     * @param id the specific id of the button that was pressed
     */
    void uiButtonPressed(int id);

private slots:
    /**
     * @brief on_naturalKillerTowerButton_clicked Slot is activated when
     * the naturalKiller tower button is clicked
     */
    void on_naturalKillerTowerButton_clicked();

    /**
     * @brief on_memoryBTowerButton_clicked Slot is activated when
     * the memoryB tower button is clicked
     */
    void on_memoryBTowerButton_clicked();

    /**
     * @brief displayEndScreen Creates a new end screen and display it
     * @param result the result of the game
     */
    void displayEndScreen(int result, bool ifWin);

    /**
     * @brief updateRound Signal is trigger when a player finishes round
     * @param the new round number.
     */
    void updateRound(int roundNum);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *gameScene;
    QGraphicsScene *deadScene;
    GC* game;
    std::vector<QImage> allSprites;
    QCursor naturalKillerCursor;
    QCursor memoryBCursor;
    QLayout *enemiesProgress;
    QLabel* v1Type;
    QLabel* v1Amount;
    QLabel* v2Type;
    QLabel* v2Amount;

};
#endif // MAINWINDOW_H
