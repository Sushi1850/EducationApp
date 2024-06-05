#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gc.h"
#include "gamecanvas.h"
#include <QLayout>
#include <QPainter>

MainWindow::MainWindow(GC* gamePtr, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , game(gamePtr)
{
    ui->setupUi(this);
    gameScene = new QGraphicsScene();
    gameScene->addPixmap(QPixmap(":/textures/Images/immune-tower-defense-01.png"));
    ui->gameCanvas->setScene(gameScene);
    ui->gameCanvas->fitInView(QRectF(0,0, 38, 38),Qt::KeepAspectRatio);

    //ui->infoButton->setStyleSheet("QPushButton { background-color: transparent }");
    ui->heartImageButton->setStyleSheet("QPushButton { background-color: transparent }");
    ui->boneImageButton->setStyleSheet("QPushButton { background-color: transparent }");
    naturalKillerCursor = QCursor(QPixmap(":/textures/Images/TD_NaturalKillerTower.png").scaledToHeight(50));
    memoryBCursor = QCursor(QPixmap(":/textures/Images/TD_MemoryBTower.png").scaledToHeight(50));

    deadScene = new QGraphicsScene(this);

    allSprites.push_back(QImage(":/textures/Images/blackVirus.png"));
    qDebug() << allSprites[0];
    connect(game,
            &GC::updateWorld,
            this,
            &MainWindow::updateFrame);
    connect(ui->gameCanvas,
            &GameCanvas::mousePressed,
            game,
            &GC::mouseEvent);
    // updating the progress
    connect(game,
                &GC::waveEnemies,
                this,
                &MainWindow::waveEnemies);
    connect(game,
            &GC::loseLives,
            ui->livesCountLabel,
            &QLabel::setText);
    connect(game,
            &GC::updateDeadVirus,
            this,
            &MainWindow::updateDeadWorld);
    connect(this,
            &MainWindow::uiButtonPressed,
            game,
            &GC::uiButtonPressed);
    connect(game,
            &GC::displayEndScreen,
            this,
            &MainWindow::displayEndScreen);
    connect(game,
            &GC::updateRound,
            this,
            &MainWindow::updateRound);
    connect(game,
            &GC::setMaxRoundLabel,
            ui->totalLevelsLabel,
            &QLabel::setText);

    enemiesProgress = new QVBoxLayout(ui->VirusProgress);
    enemiesProgress->setAlignment(Qt::AlignHCenter);
    v1Type = new QLabel();
    v1Amount = new QLabel();
    v1Amount->setAlignment(Qt::AlignHCenter);
    v1Type->setFixedSize(50,50);
    v1Type->setPixmap(
                QPixmap::fromImage(QImage(":/textures/Images/blackVirus.png")).scaled(v1Type->height(),
                                                                               v1Type->width(),
                                                                               Qt::KeepAspectRatio));
    enemiesProgress->addWidget(v1Type);
    enemiesProgress->addWidget(v1Amount);

    v2Type = new QLabel();
    v2Amount = new QLabel();
    v2Amount->setAlignment(Qt::AlignHCenter);
    v2Type->setFixedSize(50,50);
    v2Type->setPixmap(
                QPixmap::fromImage(QImage(":/textures/Images/blackBacteria.png")).scaled(v2Type->height(),
                                                                                  v2Type->width(),
                                                                                  Qt::KeepAspectRatio));

    enemiesProgress->addWidget(v2Type);
    enemiesProgress->addWidget(v2Amount);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::updateFrame(QPixmap frame, int boneBalance)
{
    gameScene->clear();
    gameScene->addPixmap(QPixmap(":/textures/Images/immune-tower-defense-01.png"));
    gameScene->addPixmap(frame);
    ui->boneMarrowCountLabel->setText(QString::number(boneBalance));
    update();
}

//Updates the dead scene and fire a single shot
void MainWindow::updateDeadWorld(double positionX, double positionY, int iteration, int size, QImage textureImage) {
    if(iteration == 0)
    {
        deadScene->clear();
    }

    QGraphicsPixmapItem *pm;

    if(textureImage == QImage(":/textures/Images/coronavirus_0.png"))
        pm = deadScene->addPixmap(QPixmap::fromImage(textureImage).scaled(64,64));
    else
        pm = deadScene->addPixmap(QPixmap::fromImage(textureImage).scaled(32,32));

    pm->setPos(positionX, positionY);

    if(iteration + 1 == size)
    {
        ui->deadWorldCanvas->setScene(deadScene);
    }
}

void MainWindow::waveEnemies(int virusNumber[4]){

    //Type 1

    v1Amount->setText(QString("Viruses Defeated:\n" + QString::number(virusNumber[0])));

    //Type 2
     v2Amount->setText(QString("Bacteria Defeated:\n" + QString::number(virusNumber[1])));


}


void MainWindow::on_naturalKillerTowerButton_clicked()
{
    this->setCursor(naturalKillerCursor);
    emit uiButtonPressed(0);
    QString towerInfo = ":/textures/Images/NKInfo.png";
    ui->label->setPixmap(QPixmap::fromImage(QImage (towerInfo)).scaled(ui->label->size(),Qt::KeepAspectRatio));
}


void MainWindow::on_memoryBTowerButton_clicked()
{
    this->setCursor(memoryBCursor);
    emit uiButtonPressed(1);
    QString towerInfo = ":/textures/Images/BCelInfo.jpg";
    ui->label->setPixmap(QPixmap::fromImage(QImage (towerInfo)).scaled(ui->label->size(),Qt::KeepAspectRatioByExpanding));
}

void MainWindow::displayEndScreen(int result, bool ifWin)
{
    EndScreen* endScreen = new EndScreen(result, ifWin, this);
    endScreen->show();
}

void MainWindow::updateRound(int roundNum)
{
    ui->levelProgressLabel->setText(std::to_string(roundNum).c_str());
}

