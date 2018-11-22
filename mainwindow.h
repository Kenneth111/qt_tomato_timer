#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include "settingsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
    int min_left;
    int sec_left;
    int min_setting;
    int sec_setting;
    SettingsDialog settings_dialog;
    QString format_time(int, int);
    void init_time(int, int);
    void update_lcd(int, int);

public slots:
    void update_ctime();
    void btn_start();
    void btn_stop();
    void show_settings();
    void setup(int, int);

};

#endif // MAINWINDOW_H
