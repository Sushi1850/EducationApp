#ifndef GC_H
#define GC_H

#include <QObject>
#include <vector>
#include <QPixmap>
#include <QMouseEvent>
#include "deadworld.h"
#include "enemy.h"
#include "tower.h"
#include "projectile.h"

class GC : public QObject
{
private:
    std::map<int,Enemy> viruses;
    std::vector<QPointF> pathPoints;
    std::map<int,int> virusesNearestPoint;
    std::map<std::pair<int,int>, bool> tiles;
    std::map<int,Tower> towers;
    std::map<int, std::vector<int>> enemiesInRange;
    int nextProjectileID =0;
    std::map<int, Projectile> projectiles;
    int enemiesKilled[4] = {0};
    QPointF startingPoint;
    QImage virusTexture;
    QImage virus2Texture;
    QImage towerTexture;
    QImage tower2Texture;
    QImage projectileTexture;
    QImage projectileTexture2;
    int towerType =0;
    double minDistance = 10;
    int roundNumber =1;
    int maxRound = 4;
    int spawnDelay = 2000;
    int roundDelay = 3000;
    int enemyRoundMulit = 3;
    int enemiesSpawned = 0;
    int boneBalance = 500;
    int bodyHealth = 10;
    bool isDead = false;
    QPointF graphicsViewSize;
    int nextVirusID =0;
    int nextTowerID =0;
    DeadWorld *deadWorld;

    /**
        * @brief gameTick Update all game computations after a certain time
        */
       void gameTick();

       /**
        * @brief spawnEnemy Spawn a single enemy
        */
       void spawnEnemy();

       /**
        * @brief buildFrame Create a new scene with updated position and image
        * to be display on the gameCanvas
        */
       void buildFrame();

       /**
        * @brief buildDeadWorld Create a new scene with all the updated deadEnemy to be
        * display on the deadWorldCanvas
        */
       void buildDeadWorld();

       /**
        * @brief checkHealth Checks the current health of the player and if they are able
        * to continue or not
        */
       void checkHealth();

       /**
        * @brief checkRound Checks the current round and if they beaten the
        * game
        */
       void checkRound();

       /**
        * @brief calculateDistance Calculate the distance of two QPoints position
        * @param p1 the first position
        * @param p2 the second position
        * @return returns the distance between the two points
        */
       qreal calculateDistance(QPointF p1, QPointF p2);

       /**
        * @brief getNextPoint check if where the virus is and decide whether or not
        * to advance them or remove them when they reach the end
        * @param virusIndex a virus id
        * @return returns the QPoint of the their next position
        */
       QPointF getNextPoint(int virusIndex);



    //Virus Methods
     /**
     * @brief updateViruses Update all of the viruses position and condition
     */
    void updateViruses();

    /**
     * @brief killVirus Kill off a specific enemy object with the given ID
     * @param vID the ID of the virus to be killed off
     */
    void killVirus1(int vID);

    /**
     * @brief killVirus Kill off a specific enemy object with the given ID
     * @param vID the ID of the virus to be killed off
     */
    void killVirus2(int vID);

    //Tower Methods
    /**
     * @brief spawnTower Create a tower at a certain position
     * @param location the specific location for tower to be placed
     * @return return whether or not the placement of the tower is successful
     */
    bool spawnTower(QPoint location);

    /**
     * @brief drawTowers A method that initalize the painter method that will
     * be given to the view by signal.
     * @param p a QPainter to be able to draw on
     */
    void drawTowers(QPainter &p);

    /**
     * @brief updateTowers Update all of the tower to see if the enemy are in
     * range of the tower and deciding if it can shoot or not
     */
    void updateTowers();

    //Projectile Methods
    /**
     * @brief spawnProjectiles Create a projectile when an enemy is close to a tower
     * @param pos initalize the position of the projectile where the tower is located
     * @param type the type of the projectile the tower shoot
     * @param targetID the specific virus ID that the virus will track
     * @param damage the amount of damage the projectile will do to the virus
     */
    void spawnProjectiles(QPoint pos, int type, int targetID, int damage);

    /**
     * @brief updateProjectiles Updates the projectile position
     */
    void updateProjectiles();

    /**
     * @brief drawProjectiles Draw the projectile using a QPainter
     * @param p the QPainter that the projectile will be draw on
     */
    void drawProjectiles(QPainter &p);

    /**
     * @brief destroyProjectiles Destroy the projectile and remove it
     * @param pID the projectile ID to destroy
     */
    void destroyProjectiles(int pID);

    //Utils
    /**
     * @brief nearestTarget Find the nearest enemy (in range) of a specific tower
     * @param v the ID of the tower
     * @return return the ID of the virus that is the closest
     */
    int nearestTarget(int v);

    /**
     * @brief setAllUnavailableTiles Set all of the tiles that are not placeable tiles
     */
    void setAllUnavailableTiles();


    Q_OBJECT
public:
    /**
      * @brief GC The constructor of the game controller which handles all the communication between model and the view
      * @param parent is a nullptr
      * @param world The world where the dead enemies will spawn in when killed
      */
     explicit GC(QObject *parent = nullptr, DeadWorld* world = nullptr);

signals:
    /**
     * @brief updateWorld Signal is trigger that will update the gameCanvas in the view
     * @param newFrame the new frame that will be updated
     * @param boneBalance the amount of bone marrow to update
     */
    void updateWorld(QPixmap newFrame, int boneBalance);

    /**
     * @brief waveEnemies Signal is trigger to update the amount of the enemy killed
     * @param virusNumber the amount of virus killed in a single tick
     */
    void waveEnemies(int virusNumber[4]);

    /**
     * @brief loseLives Signal is trigger when health is lowered
     * @param lives the amount of lives lose
     */
    void loseLives(QString lives);

    /**
     * @brief updateDeadVirus Signal is trigger which updates each dead virus killed before
     * @param positionX The x position of the virus to be displayed
     * @param positionY The y position of the virus to be displayed
     * @param iteration The current iteration of the vector position
     * @param size The size of the vector of dead enemy
     * @param texturesImage The image of the dead enemy to be displayed
     */
    void updateDeadVirus(double positionX, double positionY, int iteration, int size, QImage texturesImage);

    /**
     * @brief displayEndScreen Signal is trigger when a player finishes the game or lose the game
     * @param result the result on whether they won or lost
     */
    void displayEndScreen(int roundNumber, bool result);

    /**
     * @brief updateRound Signal is trigger when a player finishes round
     * @param the new round number.
     */
    void updateRound(int roundNum);

    /**
     * @brief setMaxRoundLabel Signal is trigger to set a max round for the game
     * @param maxRound the max round
     */
    void setMaxRoundLabel(QString maxRound);

public slots:
    /**
     * @brief mouseEvent The slot is activated when the user clicks with the mouse
     * @param e The QMouseEvent that the mouseEvent uses
     */
    void mouseEvent(QMouseEvent* e);

    /**
     * @brief uiButtonPressed The slot is activated when the user press a tower and
     * change the cursor to the image of the tower
     * @param id The id of the tower to be displayed on the cursor
     */
    void uiButtonPressed(int id);

};

#endif // GC_H
