#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pictHeight = 370;
    pictWidth = 540;
    step = 0.1;
    leftX = -100; rightX = 100;
    leftY = -100; rightY = 100;
    drawGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::f(double x)
{
    return log(x)*(-1);
}

void MainWindow::recountPixels()
{
    onePixelX = 540.0/(rightX-leftX);
    onePixelY = 370.0/(rightY-leftY);
    Ox = fabs(leftX); Oy = rightY;
}

void MainWindow::getData()
{
    leftX = ui->inputLeftX->text().toDouble();
    rightX = ui->inputRightX->text().toDouble();
    leftY = ui->inputLeftY->text().toDouble();
    rightY = ui->inputRightY->text().toDouble();
    step = 1.0/ui->inputAccuracy->text().toDouble();
}

void MainWindow::drawGraph(bool notEmpty)
{
    QPixmap graph(540,370);
    QPainter paint;
    paint.begin(&graph);
    paint.eraseRect(0,0,540,370);
    paint.drawLine(Ox*onePixelX,0,Ox*onePixelX,pictHeight);
    paint.drawLine(0,Oy*onePixelY,pictWidth,Oy*onePixelY);

    paint.setPen(QPen(Qt::black,3));
    for(double i = leftX;i<=rightX;i+=10.0)
        paint.drawPoint((i+Ox)*onePixelX,Oy*onePixelY);
    for(double i = leftY;i<=rightY;i+=10.0)
        paint.drawPoint(Ox*onePixelX,(i+Oy)*onePixelY);

    if(!notEmpty) {
        paint.end();
        ui->outputGraph->setPixmap(graph);
        return;
    }

    paint.setPen(QPen(Qt::green,1,Qt::SolidLine));
    paint.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    while(isnan(f(leftX)))
        leftX+=step;

    path.moveTo((leftX+Ox)*onePixelX,(f(leftX)+Oy)*onePixelY);
    for(double i = (double)leftX+step;i<=(double)rightX;i+=step) {
        //paint.drawPoint((i+Ox)*onePixelX,(f(i)+Oy)*onePixelY);
        path.lineTo((i+Ox)*onePixelX,(f(i)+Oy)*onePixelY);
        //qDebug() << i;
    }
    paint.drawPath(path);
    paint.end();
    ui->outputGraph->setPixmap(graph);
    return;
}

void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::on_clear_clicked()
{
    recountPixels();
    drawGraph();
}

void MainWindow::on_draw_clicked()
{
    getData();
    recountPixels();
    drawGraph(1);
}
