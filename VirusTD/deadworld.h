#ifndef DEADWORLD_H
#define DEADWORLD_H

#include "Box2D/Box2D.h"
#include "deadenemy.h"
#include <vector>

using namespace std;
class DeadWorld
{
public:
   /**
   * @brief DeadWorld is a world created with box2D that represents a deadWorld filled with
   * deadEnemies when they are killed
   */
  DeadWorld();

  /**
   * @brief CreateDeadVirus Creates a new deadVirus to spawn in the deadWorld
   * @param imageString the image of the virus that was killed
   */
  void CreateDeadVirus(QImage imageString);

  /**
   * @brief getWorld gets the deadWorld
   * @return return the deadWorld
   */
  b2World* getWorld() {return world;}

  /**
   * @brief getAllDeadEnemies returns a vector of all of the dead viruses.
   * @return a vector of deadEnemy
   */
  vector<DeadEnemy> getAllDeadEnemies();

private:
  b2World* world;
  vector<DeadEnemy> deadEnemies;
};

#endif // DEADWORLD_H

