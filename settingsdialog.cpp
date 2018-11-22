#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    connect(this->ui->pushButton_ok, SIGNAL(clicked(bool)), this, SLOT(btn_ok()));
    connect(this->ui->pushButton_cancel, SIGNAL(clicked(bool)), this, SLOT(btn_cancel()));
}

void SettingsDialog::btn_ok(){
    int min, sec;
    min = this->ui->spinBox_min->value();
    sec = this->ui->spinBox_sec->value();
    emit setup(min, sec);
    this->hide();
}

void SettingsDialog::btn_cancel(){
    this->hide();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
