#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QImage>

class Projectile
{
public:
    /**
     * @brief Projectile Create a new projectile object to track all attributes
     * of a projectile
     */
    Projectile();

    /**
     * @brief Projectile Create a new projectile with the given attributes
     * @param pID the ID of the projectile
     * @param speed the speed of the projectile will travel
     * @param texture the image of the projectile
     * @param pos the position of the projectile
     * @param t the type of projectile
     * @param target the virus ID that the projectile is tracking
     * @param towerDamage the amount of damage the projectile will do
     */
    Projectile(int pID, int speed, QImage texture, QPoint pos, int t, int target, int towerDamage);

    /**
     * @brief setProjectileSpeed Set a new projectile speed
     * @param newSpeed the new speed to be updated for this projectile
     */
    void setProjectileSpeed(int newSpeed);

    /**
     * @brief getProjectileSpeed Get the projectile speed
     * @return return the speed of the projectile
     */
    int getProjectileSpeed();

    /**
     * @brief getProjectileImage Get the projectile image
     * @return return the image of the projectile
     */
    QImage getProjectileImage();

    /**
     * @brief setProjectileImage Set a new projectile speed
     * @param newImage the new image to be updated for this projectile
     */
    void setProjectileImage(QImage newImage);

    /**
     * @brief getPosition Get the projectile position
     * @return return the position of the projectile
     */
    QPoint getPosition() const;

    /**
     * @brief setPosition Set a new position for the projectile
     * @param newPosition the new position to be updated for this projectile
     */
    void setPosition(QPoint newPosition);

    /**
     * @brief getType Get the projectile type
     * @return return the type of the projectile
     */
    int getType() const;

    /**
     * @brief setType Set a new type for the projectile
     * @param newType the new type to be updated for this projectile
     */
    void setType(int newType);

    /**
     * @brief advanceTowordsPoint Advance the projectile to the next point that will
     * follow the virus
     * @param targetPos the next position to go to
     */
    void advanceTowordsPoint(QPointF targetPos);

    /**
     * @brief getId Get the projectile ID
     * @return return the ID of the projectile
     */
    int getId() const;

    /**
     * @brief setId Set a new ID for the projectile
     * @param newId the new ID to be updated for this projectile
     */
    void setId(int newId);

    /**
     * @brief getVTargetID Get the projectile given virus ID
     * @return return the virus ID the projectile is tracking
     */
    int getVTargetID() const;

    /**
     * @brief setVTargetID Set a new virus ID for the projectile to track
     * @param newVTargetID the new virus ID that the virus will track
     */
    void setVTargetID(int newVTargetID);

    /**
     * @brief getDamage Get the projectile damage
     * @return return the damage that the projectile will inflict to a virus
     */
    int getDamage() const;

    /**
     * @brief setDamage Set a new projectile damage
     * @param newDamage the new damage to be updated for this projectile
     */
    void setDamage(int newDamage);

private:
    int speed;
    QImage image;
    QPoint position;
    int type;
    int id;
    int vTargetID;
    int damage;
};

#endif // PROJECTILE_H
