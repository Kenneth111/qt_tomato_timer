#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString display_num;

    ui->setupUi(this);
    this->min_setting = 25;
    this->sec_setting = 0;
    this->init_time(this->min_setting, this->sec_setting);
    this->update_lcd(this->min_left, this->sec_left);
    this->m_timer = new QTimer();
    connect(this->m_timer, SIGNAL(timeout()), this, SLOT(update_ctime()));
    connect(this->ui->pushButton_start, SIGNAL(clicked()), this, SLOT(btn_start()));
    connect(this->ui->pushButton_stop, SIGNAL(clicked()), this, SLOT(btn_stop()));
    connect(this->ui->pushButton_setting, SIGNAL(clicked()), this, SLOT(show_settings()));
    connect(&(this->settings_dialog), SIGNAL(setup(int,int)), this, SLOT(setup(int,int)));
}

void MainWindow::init_time(int min, int sec){
    this->min_left = min;
    this->sec_left = sec;
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
    this->init_time(this->min_setting, this->sec_setting);
    this->update_lcd(this->min_left, this->sec_left);
    this->m_timer->start(1000);
}

void MainWindow::btn_stop(){
    if(this->m_timer->isActive()){
        this->m_timer->stop();
    }
}

void MainWindow::update_lcd(int min, int sec){
    QString display_num;
    display_num = this->format_time(min, sec);
    this->ui->lcdNumber->display(display_num);
}

void MainWindow::update_ctime(){

    if (this->sec_left == 0){
        if (this->min_left == 0){
            this->m_timer->stop();
            this->setWindowState( (windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
            this->activateWindow();
            QMessageBox msg;
            msg.setText("Congrats!");
            msg.exec();
            return;
        }
        this->min_left -= 1;
        this->sec_left = 59;
    } else {
        this->sec_left -= 1;
    }
    this->update_lcd(this->min_left, this->sec_left);
}

void MainWindow::show_settings(){
    this->settings_dialog.show();
}

void MainWindow::setup(int min, int sec){
    if(this->m_timer->isActive()){
        this->m_timer->stop();
    }
    this->min_setting = min;
    this->sec_setting = sec;
    this->init_time(this->min_setting, this->sec_setting);
    this->update_lcd(min, sec);
}

MainWindow::~MainWindow()
{
    if(this->m_timer->isActive()){
        this->m_timer->stop();
    }
    delete ui;
}
