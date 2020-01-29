#include "set_bcm.h"
#include "ui_set_bcm.h"
#include "set_devices.h"
#include "info.h"
#include "mainwindow.h"
#include <iostream>
#include <QDir>
#include <QDebug>
using namespace std;
Set_bcm::Set_bcm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Set_bcm)
{
    ui->setupUi(this);
}

Set_bcm::~Set_bcm()
{
    delete ui;
}

void Set_bcm::on_listWidget_currentTextChanged(const QString &currentText)
{
    QString text = currentText;
    strcpy(Info::wifi_chip,text.toUtf8().constData());
    cout << Info::wifi_chip << endl;
}

void Set_bcm::on_buttonBox_accepted()
{
    QString dir = "/home/pi/nexmon/patches/";
    if(strcmp(Info::wifi_chip,"bcm4330")==0)
        dir += "bcm4330/5_90_100_41_sta/nexmon";
    else if(strcmp(Info::wifi_chip,"bcm4339")==0)
        dir += "bcm4339/6_37_34_43/nexmon";
    else if(strcmp(Info::wifi_chip,"bcm43438")==0)
        dir += "bcm43438/7_45_41_26/nexmon";
    else if(strcmp(Info::wifi_chip,"bcm43455")==0)
        dir += "bcm43455/7_120_5_1_sta_C0/nexmon";
    else if(strcmp(Info::wifi_chip,"bcm4356")==0)
        dir += "bcm4356/7_35_101_5_sta/nexmon";
    else if(strcmp(Info::wifi_chip,"bcm43596a0")==0)
        dir += "bcm43596a0/9.96.4_sta_c0/nexmon";
    else if(strcmp(Info::wifi_chip,"bcm4335b0")==0)
        dir += "bcm4335b0/6.30.171.1_sta/nexmon";
    else if(strcmp(Info::wifi_chip,"bcm43430a1")==0)
        dir += "bcm43430a1/7_45_41_46/nexmon";
    else if(strcmp(Info::wifi_chip,"bcm43451b1")==0)
        dir += "bcm43451b1/7_63_43_0/rom_extraction";
    else if(strcmp(Info::wifi_chip,"bcm43455c0")==0)
        dir += "bcm43455c0/7_45_189/nexmon_csi";
    else if(strcmp(Info::wifi_chip,"bcm4358")==0)
        dir += "bcm4358/7_112_300_14_sta/nexmon";
    else if(strcmp(Info::wifi_chip,"bcm4361b0")==0)
        dir += "bcm4361b0/13_38_55_1_sta/nexmon";

    QDir::setCurrent(dir);
    this->hide();
    Set_devices set_device;
    set_device.setModal(true);
    set_device.exec();
}

void Set_bcm::on_buttonBox_rejected()
{
    exit(1);
}
