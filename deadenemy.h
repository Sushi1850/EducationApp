#ifndef DEADENEMY_H
#define DEADENEMY_H

#include "Box2D/Box2D.h"
#include <QMainWindow>

class DeadEnemy
{
public:
   /**
   * @brief DeadEnemy is an object that is used as one enemy in the deadWorld
   */
  DeadEnemy();

  /**
   * @brief getBody gets the body of the deadEnemy
   * @return returns the body of the deadEnemy
   */
  b2Body* getBody() {return body;}

  /**
   * @brief getFixture gets the fixture of the deadEnemy
   * @return returns the fixture of the deadEnemy
   */
  b2Fixture* getFixture() {return fixture;}

  /**
   * @brief init initalize the object in the world
   * @param world is the deadWorld where the object is gonna spawn
   * @param x the x position of the body
   * @param y the y position of the body
   * @param dimX is the body x dimension
   * @param dimY is the body y dimension
   * @param imageString the image the deadEnemy that was killed
   */
  void init(b2World* world, float32 x, float32 y, float32 dimX, float32 dimY, QImage imageString);

  /**
   * @brief getImage get the image the deadEnemy
   * @return return the deadEnemy image
   */
  QImage getImage();

private:
  b2BodyDef bodyDef;
  b2Body *body = nullptr;
  b2Fixture *fixture = nullptr;
  QImage image;
};

#endif // DEADENEMY_H

