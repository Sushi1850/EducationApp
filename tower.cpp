#include "tower.h"

#include <math.h>
#include <vector>
#include <QDebug>

Tower::Tower()
{

}

Tower::Tower(int ID, int d, int r, QImage t, QPoint l, int pType, int p)
    :damage(d)
    ,range(r)
    ,image(t)
    ,location(l)
    ,id(ID)
    ,projectileType(pType)
    ,price(p)
{
}

int Tower::getTowerDamage()
{
    return damage;
}

void Tower::setTowerDamage(int newDamage)
{
    damage = newDamage;
}

int Tower::getTowerRange()
{
    return range;
}

void Tower::setTowerRange(int newRange)
{
    range = newRange;
}

void Tower::setTowerImage(QImage newImage)
{
    image = newImage;
}

QImage Tower::getTowerImage()
{
    return image;
}

QPoint Tower::getLocation()
{
    return location;
}

void Tower::update()
{
    if(timeSinceShot <= shotDelay)
    {
        timeSinceShot++;
//        return nullptr;
    }
    return;
}

bool Tower::canShoot()
{
    if(timeSinceShot < shotDelay)
    {
        return false;
    }
    return true;
}

void Tower::shoot()
{
    timeSinceShot = 0;
}


int Tower::getTimeSinceShot() const
{
    return timeSinceShot;
}

void Tower::setTimeSinceShot(int newTimeSinceShot)
{
    timeSinceShot = newTimeSinceShot;
}

int Tower::getProjectileType() const
{
    return projectileType;
}

void Tower::setProjectileType(int newProjectileType)
{
    projectileType = newProjectileType;
}

int Tower::getPrice() const
{
    return price;
}
