#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString display_num;
    ui->setupUi(this);
    this->min_left = 25;
    this->sec_left = 0;
    display_num = this->format_time(this->min_left, this->sec_left);
    this->ui->lcdNumber->display(display_num);
    this->m_timer = new QTimer();
    connect(this->m_timer, SIGNAL(timeout()), this, SLOT(update_lcd()));
    connect(this->ui->pushButton_start, SIGNAL(clicked()), this, SLOT(btn_start()));
    connect(this->ui->pushButton_stop, SIGNAL(clicked()), this, SLOT(btn_stop()));
}

QString MainWindow::format_time(int min, int sec){
    QString str_min;
    QString str_sec;
    QString display_num;
    str_min.setNum(min);
    if(min < 10){
        str_min = "0" + str_min;
    }
    str_sec.setNum(sec);
    if(sec < 10){
        str_sec = "0" + str_sec;
    }
    display_num = str_min + ":" + str_sec;
    return display_num;
}

void MainWindow::btn_start(){
    if(this->m_timer->isActive()){
        return;
    }
    QString display_num;
    this->min_left = 25;
    this->sec_left = 0;
    display_num = this->format_time(this->min_left, this->sec_left);
    this->ui->lcdNumber->display(display_num);
    this->m_timer->start(1000);
}

void MainWindow::btn_stop(){
    if(this->m_timer->isActive()){
        this->m_timer->stop();
    }
}

void MainWindow::update_lcd(){
    QString display_num;
    if (this->sec_left == 0){
        if (this->min_left == 0){
            return;
        }
        this->min_left -= 1;
        this->sec_left = 59;
    } else {
        this->sec_left -= 1;
    }
    display_num = this->format_time(this->min_left, this->sec_left);
    this->ui->lcdNumber->display(display_num);
}

MainWindow::~MainWindow()
{
    if(this->m_timer->isActive()){
        this->m_timer->stop();
    }
    delete ui;
}
