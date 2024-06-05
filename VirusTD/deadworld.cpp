#include "deadworld.h"

//Create the container for the dead viruses
DeadWorld::DeadWorld()
{
   world = new b2World(b2Vec2(0.0f, 10.0f));

   //Creates the floor
   b2BodyDef groundBodyDef;
   groundBodyDef.position.Set(0.0f, 4.5f);
   b2Body* groundBody = world->CreateBody(&groundBodyDef);
   b2PolygonShape groundBox;
   groundBox.SetAsBox(50.0f, 1.0f);
   groundBody->CreateFixture(&groundBox, 0.0f);

   //Create the left wall
   b2BodyDef wallBodyDef;
   wallBodyDef.position.Set(2.5f, 7.0f);
   b2Body* wallBody = world->CreateBody(&wallBodyDef);
   b2PolygonShape wallBox;
   wallBox.SetAsBox(0.01f, 8.0f);
   wallBody->CreateFixture(&wallBox, 0.0f);

   //Create the right wall
   b2BodyDef wallBodyDef2;
   wallBodyDef2.position.Set(3.5f, 7.0f);
   b2Body* wallBody2 = world->CreateBody(&wallBodyDef2);
   b2PolygonShape wallBox2;
   wallBox2.SetAsBox(0.01f, 8.0f);
   wallBody2->CreateFixture(&wallBox2, 0.0f);
}

//Create a single dead virus
void DeadWorld::CreateDeadVirus(QImage deadImage)
{
   DeadEnemy deadVirus;
   float randFloat = 2.6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(3.4-2.6)));
   deadVirus.init(world, randFloat, 1.0f, 0.10f, 0.10f, deadImage);
   deadEnemies.push_back(deadVirus);
}

vector<DeadEnemy> DeadWorld::getAllDeadEnemies()
{
   return deadEnemies;
}
