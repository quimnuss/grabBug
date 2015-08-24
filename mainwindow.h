#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>

#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0) :
                        QMainWindow(parent),
                        ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        crosstrackScene = new QGraphicsScene(this);

        QPixmap bullseyeimage( ":/bullseye2.png" );
        crosstrackScene->addPixmap( bullseyeimage);

        crosstrackPointMarker = crosstrackScene->addEllipse(0,0,10,10,QPen(Qt::red),QBrush(Qt::red));
        ui->graphicsView->ensureVisible(crosstrackScene->sceneRect());
        ui->graphicsView->fitInView( crosstrackScene->sceneRect(), Qt::KeepAspectRatio);

        ui->graphicsView->setScene(crosstrackScene);

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(100);
    }

    ~MainWindow()
    {
        delete ui;
    }

public slots:
    void update()
    {
        QPointF pos = crosstrackScene->sceneRect().center()/4;
        pos.setX(pos.x() + 50*((double)qrand())/RAND_MAX);
        pos.setY(pos.y() + 50*((double)qrand())/RAND_MAX);
        crosstrackPointMarker->setPos(pos);
        this->grab(ui->dockWidget->geometry());
        //Turning this on solves the problem since we force a 'repaint' or something.
        //ui->graphicsView->fitInView( crosstrackScene->sceneRect(), Qt::KeepAspectRatio);
    }

private:
    Ui::MainWindow *ui;
    QGraphicsScene *crosstrackScene;
    QGraphicsEllipseItem* crosstrackPointMarker;

    QTimer* timer;

};

#endif // MAINWINDOW_H
