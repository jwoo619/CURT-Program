#include "get_wireless_data.h"
#include "ui_get_wireless_data.h"
#include <QFile>
#include <QTextStream>
#include <qtconcurrentrun.h>
#include <QThread>
#include <QProcess>
#include <QTimer>
#include <iostream>
using namespace std;

void write_script(){
    QFile file1("/home/pi/Desktop/key");
    file1.open(QFile::ReadOnly|QFile::Text);
    QTextStream in(&file1);
    QFile file2("/home/pi/Desktop/tello.sh");
    file2.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&file2);
    out << "#!/bin/bash" << endl;
    out << "ifconfig mon0 down" << endl;
    out << "ifconfig wlan0 down" << endl;
    out << "pkill wpa_supplicant" << endl;
    out << "ifconfig wlan0 up" << endl;
    out << "source /home/pi/nexmon/setup_env.sh" << endl;
    out << "make install-firmware" << endl;
    out << "sleep 5" << endl;
    out << "nexutil -k157/80" << endl;
    out << "nexutil -k" << endl;
    out << "nexutil -Iwlan0 -s500 -b -l34 -v`makecsiparams -c 157/40 -C 1 -N 1 -m ";
    out << in.readLine().toUtf8().constData();
    out << " | tail -n 1`" << endl;
    out << "iw phy `iw dev wlan0 info | gawk '/wiphy/ {printf \"phy\" $2}'` interface add mon0 type monitor" << endl;
    out << "ifconfig mon0 up" << endl;
    out << "tcpdump -i wlan0 dst port 5500 -vv -w tello.pcap" << endl;

    file1.close();
    file2.close();
}

void run_shell(){
    system("sudo cp /home/pi/Desktop/tello.sh ./");
    system("sudo chmod +x tello.sh");
    system("sudo ./tello.sh");
}
void hi(Ui::Get_wireless_data *ui){
    QThread::msleep(15000);
    ui->pushButton->setText("STOP");
    cout << ui->pushButton->text().toUtf8().constData()<< endl;
}


Get_wireless_data::Get_wireless_data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Get_wireless_data)
{
    ui->setupUi(this);

    write_script();
    QtConcurrent::run(run_shell);
    QtConcurrent::run(hi,ui);
}

Get_wireless_data::~Get_wireless_data()
{
    delete ui;
}

void Get_wireless_data::on_pushButton_clicked()
{
    if(strcmp(ui->pushButton->text().toUtf8().constData(),"STOP")==0){
        system("sudo kill 15 `ps -aux | grep \"pcap\" | grep root | awk '{print $2}'`");
        exit(1);
    }
}
