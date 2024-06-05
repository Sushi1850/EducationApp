#ifndef TOWER_H
#define TOWER_H

#include <QImage>
#include <set>
#include "enemy.h"

class Tower
{
public:
    /**
     * @brief Tower Create a new tower object to track all attributes
     */
    Tower();

    /**
     * @brief Tower Create a new tower with the given attributes
     * @param id the tower id
     * @param d the amount of damage the tower will do to a virus
     * @param r the radius of the tower
     * @param t the image of the tower
     * @param l the location of the tower
     * @param pType the projectile type of the tower
     * @param p the cost of the tower
     */
    Tower(int id, int d, int r, QImage t, QPoint l, int pType, int p);

    /**
     * @brief getTowerDamage Get the tower damage
     * @return return the amount of damage the tower will do to a virus
     */
    int getTowerDamage();

    /**
     * @brief setTowerDamage Set a new damage for the tower
     * @param newDamage the new damage to be updated
     */
    void setTowerDamage(int newDamage);

    /**
     * @brief getTowerRange Get the tower range
     * @return return the range of the tower
     */
    int getTowerRange();

    /**
     * @brief setTowerRange Set a new range for the tower
     * @param newRange the new range to be updated
     */
    void setTowerRange(int newRange);

    /**
     * @brief setTowerImage Set a new image for the tower
     * @param newImage the new image to be updated
     */
    void setTowerImage(QImage newImage);

    /**
     * @brief getTowerImage Get the tower image
     * @return return the image of the tower
     */
    QImage getTowerImage();

    /**
     * @brief getLocation Get the tower location
     * @return return the location of the tower
     */
    QPoint getLocation();

    /**
     * @brief update Check if the projectile delay is done before
     * shooting another projectile
     */
    void update();

    /**
     * @brief canShoot Checks whether or not the tower can shoot or
     * not
     * @return return true/false if the tower is able to shoot
     */
    bool canShoot();

    /**
     * @brief shoot Set a delay until the next projectile can be fired
     */
    void shoot();

    /**
     * @brief getTimeSinceShot Get the tower delay time
     * @return return the delay time of the tower
     */
    int getTimeSinceShot() const;

    /**
     * @brief setTimeSinceShot Set a new delay time for the tower
     * @param newTimeSinceShot the new delay time to be updated
     */
    void setTimeSinceShot(int newTimeSinceShot);

    /**
     * @brief getProjectileType Get the tower type
     * @return return the type of the tower
     */
    int getProjectileType() const;

    /**
     * @brief setProjectileType Set a new type for the tower
     * @param newProjectileType the new type to be updated
     */
    void setProjectileType(int newProjectileType);

    /**
     * @brief getPrice Get the tower price
     * @return return the price of the tower
     */
    int getPrice() const;

private:
    int damage;
    int range;
    QImage image;
    QPoint location;
    int id;
    int shotDelay = 100;
    int timeSinceShot =0;
    std::set<Enemy*> enemiesInRange;
    int projectileType;
    int price;
};

#endif // TOWER_H
