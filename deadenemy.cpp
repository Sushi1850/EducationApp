#include "deadenemy.h"
#include "Box2D/Box2D.h"

DeadEnemy::DeadEnemy()
{

}

void DeadEnemy::init(b2World* world, float32 x, float32 y, float32 dimX, float32 dimY, QImage deadImage)
{
   image = deadImage;
   bodyDef.type = b2_dynamicBody;
   bodyDef.position.Set(x,y);
   body = world->CreateBody(&bodyDef);
   b2PolygonShape boxShape;
   boxShape.SetAsBox(dimX, dimY);
   b2FixtureDef fixtureDef;
   fixtureDef.shape = &boxShape;
   fixtureDef.density = 1.0f;
   fixtureDef.friction = 0.0f;
   fixtureDef.restitution = 0.1f;
   fixture = body->CreateFixture(&fixtureDef);
}

QImage DeadEnemy::getImage()
{
   return image;
}
