#include "set_devices.h"
#include "ui_set_devices.h"
#include "get_wireless_data.h"
#include "set_bcm.h"
#include <QListWidget>
#include "QtNetwork/QNetworkInterface"
#include "QString"
#include <QProcess>
#include <iostream>
#include <QThread>
#include <qtconcurrentrun.h>
#include <QTextStream>
#include <QFile>
using namespace std;
int cnt;
string mac_data;
string c_data;

void Set_devices::on_toolButton_clicked(){
    ui->label_3->setText("");
    ui->toolButton->setVisible(false);
}
void Set_devices::on_toolButton_2_clicked(){
    ui->label_5->setText("");
    ui->toolButton_2->setVisible(false);
}
void Set_devices::on_toolButton_3_clicked(){
    ui->label_7->setText("");
    ui->toolButton_3->setVisible(false);
}
void Set_devices::on_toolButton_4_clicked(){
    ui->label_8->setText("");
    ui->toolButton_4->setVisible(false);
}
void Set_devices::on_toolButton_5_clicked(){
    ui->label_11->setText("");
    ui->toolButton_5->setVisible(false);
}
void Set_devices::on_listWidget_currentTextChanged(const QString &currentText)
{
    string str = currentText.toUtf8().constData();
    str = str.substr(str.find("\t")+1,17);
    c_data = str;
}
void set_device(Ui::Set_devices* ui){
    system("sudo arp-scan -I eth0 -l | grep -E ..:..:..:..:..:.. > /home/pi/Desktop/arp-table.txt");
    QFile file("/home/pi/Desktop/arp-table.txt");
    file.open(QFile::ReadOnly|QFile::Text);
    QTextStream in(&file);
    while(1){
        QString data = in.readLine().toUtf8().constData();
        if(data[0]=='\0')
            break;
        ui->listWidget->addItem(data);
    }
}

Set_devices::Set_devices(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Set_devices)
{
    ui->setupUi(this);
    cnt = 0;
    ui->toolButton->setVisible(false);
    ui->toolButton_2->setVisible(false);
    ui->toolButton_3->setVisible(false);
    ui->toolButton_4->setVisible(false);
    ui->toolButton_5->setVisible(false);
    QtConcurrent::run(set_device,ui);
}

Set_devices::~Set_devices()
{
    delete ui;
}

void Set_devices::on_pushButton_clicked()
{
    if(ui->checkBox->checkState()){
        c_data = ui->plainTextEdit->toPlainText().toUtf8().constData();
        ui->plainTextEdit->setPlainText("");
        ui->checkBox->setChecked(false);
        if(c_data.length() != 12)
            return;
        else{
            for(int i = 0; i < 5; i++)
                c_data.insert(2+3*i,":");
        }
    }
    if(ui->label_3->text()==""){
        ui->label_3->setText(QString::fromStdString(c_data));
        ui->toolButton->setVisible(true);
    }
    else if(ui->label_5->text()==""){
        ui->label_5->setText(QString::fromStdString(c_data));
        ui->toolButton_2->setVisible(true);
    }
    else if(ui->label_7->text()==""){
        ui->label_7->setText(QString::fromStdString(c_data));
        ui->toolButton_3->setVisible(true);
    }
    else if(ui->label_8->text()==""){
        ui->label_8->setText(QString::fromStdString(c_data));
        ui->toolButton_4->setVisible(true);
    }
    else if(ui->label_11->text()==""){
        ui->label_11->setText(QString::fromStdString(c_data));
        ui->toolButton_5->setVisible(true);
    }
}
void set_mac_data(Ui::Set_devices* ui){
    if(ui->label_3->text()!=""){
        mac_data += ui->label_3->text().toUtf8().constData();
        mac_data += ",";
    }
    if(ui->label_5->text()!=""){
        cout << "Hi" << endl;
        mac_data += ui->label_5->text().toUtf8().constData();
        mac_data += ",";
    }
    if(ui->label_7->text()!=""){
        mac_data += ui->label_7->text().toUtf8().constData();
        mac_data += ",";
    }
    if(ui->label_8->text()!=""){
        mac_data += ui->label_8->text().toUtf8().constData();
        mac_data += ",";
    }
    if(ui->label_11->text()!=""){
        mac_data += ui->label_11->text().toUtf8().constData();
    }
}
void Set_devices::on_buttonBox_accepted()
{
    QFile file("/home/pi/Desktop/key");
    set_mac_data(ui);
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&file);
    out << QString::fromStdString(mac_data) << endl;
    cout << mac_data << endl;
    this->hide();
    Get_wireless_data get_wireless_data;
    get_wireless_data.setModal(true);
    get_wireless_data.exec();
}

void Set_devices::on_buttonBox_rejected()
{
    this->hide();
    Set_bcm set_bcm;
    set_bcm.setModal(true);
    set_bcm.exec();
}
