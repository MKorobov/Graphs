#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawGraph(bool notEmpty = 0);
    void recountPixels();
    void getData();
    double f(double x);
    bool isNaN(double x);
    
private slots:
    void on_exit_clicked();

    void on_clear_clicked();

    void on_draw_clicked();

    void on_save_clicked();

private:
    Ui::MainWindow *ui;
    double leftX,rightX;
    double leftY,rightY;
    int pictWidth,pictHeight;
    double step;
    double onePixelX,onePixelY;
    double Ox,Oy;
};

#endif // MAINWINDOW_H
