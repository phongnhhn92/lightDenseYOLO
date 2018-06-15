#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "yolo_v2_class.h"
#include "thread"

using namespace std;
using namespace cv;

std::vector<std::string> objects_names_from_file(std::string const filename) {
    std::ifstream file(filename);
    std::vector<std::string> file_lines;
    if (!file.is_open()) return file_lines;
    for (std::string line; file >> line;) file_lines.push_back(line);
    std::cout << "object names loaded \n";
    return file_lines;
}
void draw_boxes(cv::Mat mat_img, std::vector<bbox_t> result_vec, std::vector<std::string> obj_names) {

    for (auto &i : result_vec) {
            cv::Scalar color(60, 160, 260);
            cv::Scalar color2(120, 60, 150);
            cv::rectangle(mat_img, cv::Rect(i.x, i.y, i.w, i.h), color, 3);

            if (obj_names.size() >= i.obj_id)
            {
                string w = to_string(i.w);
                string h = to_string(i.h);
                putText(mat_img, obj_names[i.obj_id], cv::Point2f(i.x, i.y - 10), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, color2);
                //putText(mat_img, h, cv::Point2f(i.x, i.y - 20), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, color);
                //putText(mat_img, w, cv::Point2f(i.x, i.y - 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, color);
            }
            /*if (i.track_id > 0)
                    putText(mat_img, std::to_string(i.track_id), cv::Point2f(i.x + 5, i.y + 15), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, color);*/
    }
    namedWindow("Result",WINDOW_AUTOSIZE);
    moveWindow("Result",300,50);
    cv::imshow("Result", mat_img);
}

void show_result(std::vector<bbox_t> const result_vec, std::vector<std::string> const obj_names) {
    for (auto &i : result_vec) {
            if (obj_names.size() > i.obj_id) std::cout << obj_names[i.obj_id] << " - ";
            std::cout << "obj_id = " << i.obj_id << ",  x = " << i.x << ", y = " << i.y
                    << ", w = " << i.w << ", h = " << i.h
                    << std::setprecision(3) << ", prob = " << i.prob << std::endl;

    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    try
    {
        this->detector = new Detector("../data/lightDenseYOLO.cfg", "../data/lightDenseYOLO.weights");
        obj_names = objects_names_from_file("../data/coco.names");
    }
    catch(std::exception &e){ std::cerr << "exception: " << e.what() << "\n"; getchar(); }
    catch (...) { std::cerr << "unknown exception \n"; getchar(); }

    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::blue);

    ui->lblStatus->setAutoFillBackground(true);
    ui->lblStatus->setPalette(sample_palette);
    ui->lblStatus->setText("Ready");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionReset_triggered()
{
    ui->txtPath->clear();
}

void MainWindow::on_actionExit_Program_triggered()
{
    QApplication::quit();
}

void MainWindow::on_btnBrowse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Select file","/home/phong",tr("Images (*.png *.xpm *.jpg);;Video files (*.mp4 *.MOV *.avi)"));
    ui->txtPath->setText(fileName);
}

void MainWindow::on_btnDetect_clicked()
{
    destroyAllWindows();
    string path = ui->txtPath->text().toStdString();
    if(path == "")
        QMessageBox::information(this,"Warning","Please select an image or a video");
    else
    {
        std::string const file_ext = path.substr(path.find_last_of(".") + 1);
        if (file_ext == "avi" || file_ext == "mp4" || file_ext == "mjpg" || file_ext == "MOV") {	// video file
            VideoCapture cap(path);
            cout<<path<<endl;

            if( !cap.isOpened())
            {
                QMessageBox::information(this,"Warning","Error reading video !");
            }
            while(1){
                Mat frame;
                cap>>frame;
                if(frame.empty())
                {
                    QMessageBox::information(this,"Information","Video ended !");
                    break;
                }
                std::vector<bbox_t> result_vec = this->detector->detect(frame);
                draw_boxes(frame, result_vec, obj_names);

                char c=(char)waitKey(25);
                if(c==27)
                    break;
            }
            cap.release();
            // Closes all the frames
            destroyAllWindows();
        }
        else
        {
            cv::Mat mat_img = cv::imread(path);
            std::vector<bbox_t> result_vec = this->detector->detect(mat_img);
            //show_result(result_vec, obj_names);
            draw_boxes(mat_img, result_vec, obj_names);
        }
    }
}

void MainWindow::on_btnWebcamOpen_clicked()
{
    destroyAllWindows();
    VideoCapture cap;
    if(!cap.open(0))
    {
        QMessageBox::information(this,"Warning","No webcam detected !");
    }

    for(;;)
    {
        Mat frame;
        cap>>frame;
        if(frame.empty())
        {
            QMessageBox::information(this,"Information","No webcam detected !");
            break;
        }
        std::vector<bbox_t> result_vec = this->detector->detect(frame);
        draw_boxes(frame, result_vec, obj_names);

        char c=(char)waitKey(25);
        if(c==27)
            break;

    }
    cap.release();
    destroyAllWindows();
}
