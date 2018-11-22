#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>

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
    QString format_time(int, int);
    void init_time(int, int);

public slots:
    void update_lcd();
    void btn_start();
    void btn_stop();
};

#endif // MAINWINDOW_H
