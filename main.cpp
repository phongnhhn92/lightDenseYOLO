#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("../data/yolo.ico"));

    int W = 500;
    int H = 500;
    int screenWidth;
    int screenHeight;
    int x, y;

    QDesktopWidget desktop;

    screenWidth = desktop.screen()->width();
    screenHeight = desktop.screen()->height();

    x = (screenWidth - W) / 2;
    y = (screenHeight - H) / 2;


    MainWindow w;
    w.move( x, y );
    w.setWindowTitle("Real-time Object Detection");
    w.show();

    return a.exec();
}
