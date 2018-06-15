#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "yolo_v2_class.h"

using namespace std;
using namespace cv;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Detector *detector;
    std::vector<std::string> obj_names;


private slots:
    void on_actionReset_triggered();

    void on_actionExit_Program_triggered();

    void on_btnBrowse_clicked();

    void on_btnDetect_clicked();

    void on_btnWebcamOpen_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
