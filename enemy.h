#ifndef ENEMY_H
#define ENEMY_H

#include <QPoint>
#include <QImage>

class Enemy
{
private:
   QImage* baseImage;
   QPointF position;
   double health;
   double speed;
   int id;
   int virusType;

public:
   /**
    * @brief Enemy default constructor for Enemy class which is used to create
    * an enemy
    */
   Enemy();

   /**
    * @brief Enemy Create a single enemy
    * @param ID a specfic ID for the enemy object
    * @param texture the image the enemy uses
    * @param pos the position of the enemy
    * @param health the vitality of the enemy
    * @param speed the amount of speed the enemy is moving
    * @param initVirusType the type of the enemy
    */
   Enemy(int ID, QImage* texture, QPointF pos, double health, double speed, int initVirusType);

   /**
    * @brief takeDamage Decrease the health of the enemy
    * @param damage the amount of damage inflicted to the enemy
    * @return returs a false/true on whether if the enemy health is lower than 0
    */
   bool takeDamage(float damage);

   /**
    * @brief getBaseImage get the enemy image
    * @return return the image of the enemy
    */
   QImage* getBaseImage();

   /**
    * @brief getPosition get the position of the enemy
    * @return return the position of the enemy
    */
   QPointF getPosition();

   /**
    * @brief gethealth get the health of the enemy
    * @return return the enemy health
    */
   double gethealth();

   /**
    * @brief getID get the id of the enemy
    * @return return the enemy id
    */
   int getID();

   /**
    * @brief get virus type
    * @return return the virus type
    */
   int getVirusType();

   /**
    * @brief advanceTowordsPoint makes the enemy advance to the next point on the map
    * @param targetPos the specific position for the enemy to head towards
    */
   void advanceTowordsPoint(QPointF targetPos);
};

#endif // ENEMY_H

