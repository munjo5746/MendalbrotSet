#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <xmmintrin.h>
#include <iostream>
#include <QPainter>
#include <QLabel>
#include <Windows.h>
#include <QApplication>
#include <math.h>
#include <fstream>

using namespace std;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit MainWindow(QWidget *parent = 0);
    //~MainWindow();
    void draw_sse(QImage &image,int max_iter);
    void draw_norm(QImage &image,int max_iter);
    void update();

private:
    QImage screen;
    QLabel *label;
};

#endif // MAINWINDOW_H
