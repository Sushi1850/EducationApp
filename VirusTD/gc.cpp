#include "gc.h"

#include <math.h>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <string>

#include "projectile.h"

GC::GC(QObject *parent, DeadWorld* world)
    : QObject{parent}
    ,startingPoint(150,-32)
    ,virusTexture(QImage(":/textures/Images/blackVirus.png").scaled(128,128))
    ,virus2Texture(QImage(":/textures/Images/blackBacteria.png").scaled(128,128))
    ,towerTexture(QImage(":/textures/Images/TD_NaturalKillerTower.png").scaled(64,64))
    ,tower2Texture(QImage(":/textures/Images/TD_MemoryBTower.png").scaled(64,64))
    ,projectileTexture(QImage(":/textures/Images/TD_NaturalKillerProjectile.png"))
    ,projectileTexture2(QImage(":/textures/Images/TD_AntibodyProjectile.png"))
    ,graphicsViewSize(QPoint(700,700))
    ,deadWorld(world)
{
    emit setMaxRoundLabel(QString::number(maxRound));

    // Add the path points
    pathPoints.push_back(QPointF(142,0));
    pathPoints.push_back(QPointF(142,215));
    pathPoints.push_back(QPointF(935,215));
    pathPoints.push_back(QPointF(935,400));
    pathPoints.push_back(QPointF(142,400));
    pathPoints.push_back(QPointF(142,700));
    pathPoints.push_back(QPointF(935,700));
    pathPoints.push_back(QPointF(935,935));
    pathPoints.push_back(QPointF(142,935));
    pathPoints.push_back(QPointF(142,1080));

    for(int col = 0; col < 16; col++)
        for(int row = 0; row < 16; row++)
            tiles[std::make_pair(col*16, row *72)] = false;

    setAllUnavailableTiles();


    Enemy e(nextVirusID, &virusTexture,startingPoint,20,5,2);
    viruses.emplace(nextVirusID,e);
    nextVirusID++;
    virusesNearestPoint.emplace(0,0);
    QTimer::singleShot(1000, this, &GC::gameTick);
    QTimer::singleShot(1500, this, &GC::spawnEnemy);
}

void GC::gameTick()
{
    checkHealth();
    //checkRound();
    updateViruses();
    updateTowers();
    updateProjectiles();
    buildFrame();
    buildDeadWorld();
    //emit updateWorld(viruses[0].getPosition().toPoint());

    QTimer::singleShot(10, this, &GC::gameTick);
}

void GC::checkHealth()
{
   if(bodyHealth == 0 && !isDead)
   {
       isDead = true;
       emit displayEndScreen(roundNumber, false);
   }
}

void GC::checkRound()
{
    if(roundNumber >= maxRound)
    {
        if(viruses.empty())
        {
            emit displayEndScreen(roundNumber, true);
            return;
        }
        QTimer::singleShot(100, this, &GC::checkRound);
        return;
    }
    roundNumber++;
    enemiesSpawned = 0;
    emit updateRound(roundNumber);
    QTimer::singleShot(spawnDelay, this, &GC::spawnEnemy);
}


void GC::spawnEnemy()
{
    if(enemiesSpawned < enemyRoundMulit * roundNumber)
    {
        Enemy e;
        if(enemiesSpawned %3)
        {
            e=Enemy(nextVirusID, &virus2Texture,startingPoint,30,7,1);
        }
        else
        {
           e=Enemy(nextVirusID, &virusTexture,startingPoint,20,5,2);
        }
        viruses.emplace(nextVirusID,e);
        virusesNearestPoint.emplace(nextVirusID,0);
        nextVirusID++;
        enemiesSpawned++;
        QTimer::singleShot(spawnDelay, this, &GC::spawnEnemy);
        return;

    }
    //Start Round controler
    QTimer::singleShot(roundDelay, this, &GC::checkRound);
}

void GC::buildFrame()
{
    QImage newFrame(1080,1080,QImage::Format_ARGB32);
    QPainter p;
    p.begin(&newFrame);
    p.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    p.setPen(QPen(Qt::blue));
    //    QSize newSize(50,50);
    auto virusIter = viruses.begin();
    while(virusIter != viruses.end())
    {
        QPoint pos(virusIter->second.getPosition().toPoint());
        int h = virusIter->second.getBaseImage()->size().height();
        pos.setX(pos.x()-h/2);
        pos.setY(pos.y()-h/2);
        p.drawImage(pos, *virusIter->second.getBaseImage());
        //p.drawPoint(viruses[i].getPosition());
        p.fillRect(QRect(QPoint(pos.x()-48,pos.y()-32),QPoint(pos.x() + 10* virusIter->second.gethealth(),pos.y()-16)),
                   Qt::green);
        virusIter++;
    }

    drawTowers(p);
    drawProjectiles(p);

    p.end();
    QPixmap frame = QPixmap::fromImage(newFrame);
//    newFrame.save("./test.png");
    emit updateWorld(frame, boneBalance);
}


QPointF GC::getNextPoint(int virusIndex)
{
    int pathIndex = virusesNearestPoint.at(virusIndex);
    if(calculateDistance(viruses[virusIndex].getPosition(),
                         pathPoints[pathIndex])
            > minDistance)
    {
        //qDebug() << "pathIndex: " << pathIndex;
        return pathPoints[pathIndex];
    }
    if(pathIndex +1 == pathPoints.size())
    {
        int virusType = viruses.at(virusIndex).getVirusType();
        virusesNearestPoint.at(virusIndex) = 0;
               if(virusType == 1)
               {
                   bodyHealth = bodyHealth - 2;
                   if(!isDead)
                    emit loseLives(QString::number(bodyHealth));
                   killVirus2(virusIndex);

               } else
               {
                   bodyHealth = bodyHealth - 1;
                   if(!isDead)
                     emit loseLives(QString::number(bodyHealth));
                   killVirus1(virusIndex);
               }


               return pathPoints[0];
    }else{
       // qDebug() << "pathIndex: " << pathIndex+1;
        virusesNearestPoint.at(virusIndex) = pathIndex+1;
        return pathPoints[pathIndex+1];
    }
}

qreal GC::calculateDistance(QPointF p1, QPointF p2)
{
    return sqrt(std::pow(std::max(p1.x(), p2.x()) - std::min(p1.x(),p2.x()),2)+
                       std::pow(std::max(p1.y(), p2.y()) - std::min(p1.y(),p2.y()), 2));
}

void GC::updateViruses()
{
    auto virusIter = viruses.begin();
    while(virusIter != viruses.end())
    {
       QPointF nextPoint;
       nextPoint = getNextPoint(virusIter->first);
       virusIter->second.advanceTowordsPoint(nextPoint);
       auto towerIter = towers.begin();
       while(towerIter != towers.end())
       {
           qreal dist = calculateDistance(virusIter->second.getPosition(),towerIter->second.getLocation());
           if(dist < towerIter->second.getTowerRange())
           {
               enemiesInRange[towerIter->first].push_back(virusIter->first);
           }
           towerIter++;
       }

        virusIter++;
    }
}


void GC::killVirus1(int vID)
{

    deadWorld->CreateDeadVirus(*viruses.at(vID).getBaseImage());
    viruses.erase(vID);
    enemiesKilled[0]++;
    emit waveEnemies(enemiesKilled);
}

void GC::killVirus2(int vID)
{

    deadWorld->CreateDeadVirus(*viruses.at(vID).getBaseImage());
    viruses.erase(vID);
    enemiesKilled[1]++;
    emit waveEnemies(enemiesKilled);
}



bool GC::spawnTower(QPoint location)
{
    //int tileID = (location.y()/72)*16 + location.x();
    int xPosition = location.x();
    int yPosition = (location.y()/72)*16;
    if(tiles[std::make_pair(yPosition, xPosition)] == true)
    {
        return false;
    }
    if(towerType == 0)
    {
        int price = 50;
        if(boneBalance >= price)
        {
            towers.emplace(nextTowerID,Tower(nextTowerID,1,284,towerTexture, location, 0, price));
            boneBalance -= towers[nextTowerID].getPrice();
        }
        else
        {
            return false;
        }

    }
    else
    {
        int price = 150;
        if(boneBalance >= price)
        {
            towers.emplace(nextTowerID,Tower(nextTowerID,1,284,tower2Texture, location, 1, price));
            boneBalance -= towers[nextTowerID].getPrice();
        }
        else
        {
            return false;
        }
    }
    tiles[std::make_pair(yPosition, xPosition)] = true;
    nextTowerID++;
    return true;
}

void GC::drawTowers(QPainter &p)
{
    auto towerIter = towers.begin();
    while(towerIter != towers.end())
    {

        QPoint grid = towerIter->second.getLocation();
        QPoint loc;
        loc.setX(grid.x());
        loc.setY(grid.y());
        p.drawImage(loc, towerIter->second.getTowerImage());
        towerIter++;
    }
}

void GC::updateTowers()
{
    auto towerIter = towers.begin();

        while(towerIter != towers.end())
        {
            if(enemiesInRange[towerIter->first].size() !=0)
            {
                //find nearest target
                int vID = nearestTarget(towerIter->first);

                if(towerIter->second.canShoot())
                {
                    //Shoot
                    towerIter->second.shoot();
                    //Spawn Projectile with vID as target
                    Tower t = towerIter->second;
                    spawnProjectiles(t.getLocation(), t.getProjectileType(),vID,t.getTowerDamage());
                }
            }
            towerIter->second.update();
            //remove targets out of range
            enemiesInRange[towerIter->first].clear();

            towerIter++;
        }
}

void GC::setAllUnavailableTiles()
{
    std::vector<int> similarRows = {2,3,5,6,9,10,12,13};

       //First row
       for(int rows = 0; rows < 16; rows++) {
           tiles[std::make_pair(0*16, rows *72)] = true;
       }

       // Assign similar rows
       for(int uniqueRow: similarRows)
       {
           for(int rows = 0; rows < 16; rows++) {
               if(rows == 0 || rows == 14)
                   continue;
               else
                   tiles[std::make_pair(1*16*uniqueRow, rows *72)] = true;
           }
       }

       std::vector<int> unavailableTileX = {16,16,64,64,112,112,128,128,176,176,224,224};
       std::vector<int> unavailableTileY = {72,144,864,936,72,144,72,144,864,936,72,144};

       //Assign remaining tiles
       for(unsigned long long i = 0; i < unavailableTileX.size(); i++)
       {
           tiles[std::make_pair(unavailableTileX[i],unavailableTileY[i])] = true;
       }


}

void GC::buildDeadWorld()
{
    double positionX, positionY;
    deadWorld->getWorld()->Step(1.0/60.0, 6, 2);
    vector<DeadEnemy> allEnemies = deadWorld->getAllDeadEnemies();

    for(unsigned long long i = 0; i < allEnemies.size(); i++)
    {
        b2Vec2 position = allEnemies[i].getBody()->GetPosition();
        QImage textureImage = allEnemies[i].getImage();
        positionX = position.x * 100;
        positionY = position.y * 100;
        emit updateDeadVirus(positionX, positionY, i, allEnemies.size(), textureImage);
    }
}

//Projectile Methods
void GC::spawnProjectiles(QPoint pos, int type, int targetID, int damage)
{
    if(type == 0)
    {
        projectiles.emplace(nextProjectileID,
                            Projectile(nextProjectileID, 20,
                                       projectileTexture ,pos,type,
                                       targetID, damage));
        nextProjectileID++;
        return;
    }
    projectiles.emplace(nextProjectileID,
                        Projectile(nextProjectileID, 20,
                                   projectileTexture2,pos,type,
                                   targetID, damage));
    nextProjectileID++;
}
void GC::updateProjectiles()
{
    std::vector<int> projectilesToDestroy;
    auto projIter = projectiles.begin();
    while(projIter != projectiles.end())
    {
        int targetID = projIter->second.getVTargetID();
        if(viruses.count(targetID) == 0)
        {
            projectilesToDestroy.push_back(projIter->first);
        }
        else
        {
            Enemy v =viruses.at(targetID);
            qreal dist = calculateDistance(projIter->second.getPosition(), v.getPosition());
            if(dist <= projIter->second.getProjectileSpeed())
            {
                //Hit
                bool dead = viruses.at(targetID).takeDamage(projIter->second.getDamage());
                qDebug() << v.getVirusType();
                if(dead && v.getVirusType() == 1)
                {
                    qDebug() << "killVirus 1";
                    boneBalance += 10;
                    killVirus2(targetID);
                    projectilesToDestroy.push_back(projIter->first);
                }
                else if (dead && v.getVirusType() == 2)
                {
                    qDebug() << "killVirus 2";
                    boneBalance += 10;
                    killVirus1(targetID);
                    projectilesToDestroy.push_back(projIter->first);
                }
            }
            else
            {
                projIter->second.advanceTowordsPoint(v.getPosition());
            }
        }

        projIter++;

    }
    foreach(int id, projectilesToDestroy)
    {
        destroyProjectiles(id);
    }
}
void GC::drawProjectiles(QPainter &p)
{
    auto projIter = projectiles.begin();
    while(projIter != projectiles.end())
    {

        QPoint pos = projIter->second.getPosition();
        QPoint loc;
        loc.setX(pos.x() - 16);
        loc.setY(pos.y() - 16);
        p.drawImage(loc, projIter->second.getProjectileImage());
        projIter++;
    }
}
void GC::destroyProjectiles(int pID)
{
    projectiles.erase(pID);
}


int GC::nearestTarget(int towerID)
{
    double nearestDistance = 1000000.0;
    int nearestID = enemiesInRange.at(towerID).at(0);
    for(int i =0; i < enemiesInRange[towerID].size(); i++)
    {
        int vID = enemiesInRange.at(towerID)[i];
        if(viruses.count(vID) != 0)
        {
            double dist = calculateDistance(towers[towerID].getLocation(), viruses.at(vID).getPosition());
            if(dist < nearestDistance)
            {
                nearestDistance = dist;
                nearestID = enemiesInRange.at(towerID)[i];
            }
        }
    }
    return nearestID;
}


void GC::mouseEvent(QMouseEvent* e)
{
    int mapX, mapY =0;
    double percentX = e->pos().x()/graphicsViewSize.x();
    double percentY = e->pos().y()/graphicsViewSize.y();
    double imgCordsX = percentX * 1080;
    double imgCordsY = percentY * 1080;
    //Convert to tile cords
    int tileX = imgCordsX/72;
    int tileY = imgCordsY/72;

    //Mult to get tile cornor in pixels
    mapX = (tileX*72);
    mapY = (tileY * 72);
    if(!isDead)
        spawnTower(QPoint(mapX,mapY));
}

void GC::uiButtonPressed(int id)
{
    towerType = id;
}
