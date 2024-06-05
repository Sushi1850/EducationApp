#include "projectile.h"

#include <QPoint>

Projectile::Projectile()
{

}

Projectile::Projectile(int pID, int s,
                       QImage texture, QPoint pos,
                       int t, int target,
                       int towerDamage)
    :speed(s)
    ,image(texture)
    ,position(pos)
    ,type(t)
    ,id(pID)
    ,vTargetID(target)
    ,damage(towerDamage)
{

}

void Projectile::setProjectileSpeed(int newSpeed)
{
    speed = newSpeed;
}

int Projectile::getProjectileSpeed()
{
    return speed;
}

QImage Projectile::getProjectileImage()
{
    return image;
}

void Projectile::setProjectileImage(QImage newImage)
{
    image = newImage;
}

QPoint Projectile::getPosition() const
{
    return position;
}

void Projectile::setPosition(QPoint newPosition)
{
    position = newPosition;
}

int Projectile::getType() const
{
    return type;
}

void Projectile::setType(int newType)
{
    type = newType;
}

void Projectile::advanceTowordsPoint(QPointF targetPos)
{
    QPointF heading = targetPos - position;
    qreal distance = heading.manhattanLength();
    QPointF direction = heading/distance;
    position += direction.toPoint()*speed;
}

int Projectile::getId() const
{
    return id;
}

void Projectile::setId(int newId)
{
    id = newId;
}

int Projectile::getVTargetID() const
{
    return vTargetID;
}

void Projectile::setVTargetID(int newVTargetID)
{
    vTargetID = newVTargetID;
}

int Projectile::getDamage() const
{
    return damage;
}

void Projectile::setDamage(int newDamage)
{
    damage = newDamage;
}
