#include "enemy.h"

#include <QDebug>

Enemy::Enemy()
{

}

Enemy::Enemy(int ID, QImage* texture, QPointF pos, double health, double speed,int VirusType)
    :baseImage(texture)
    ,position(pos)
    ,health(health)
    ,speed(speed)
    ,id(ID),virusType(VirusType)
{

}

bool Enemy::takeDamage(float damage)
{
    health-=damage;
    return health < 0;
}
QImage* Enemy::getBaseImage()
{
    return baseImage;
}
QPointF Enemy::getPosition()
{
    return position;
}
double Enemy::gethealth()
{
    return health;
}
void Enemy::advanceTowordsPoint(QPointF targetPos)
{
    //Source for this math
//https://docs.unity3d.com/2017.4/Documentation/Manual/DirectionDistanceFromOneObjectToAnother.html
    QPointF heading = targetPos - position;
    qreal distance = heading.manhattanLength();
    QPointF direction = heading/distance;
        position += direction*speed;
}

int Enemy::getID()
{
    return id;
}

int Enemy::getVirusType()
{
    return virusType;
}



