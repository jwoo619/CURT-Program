#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "set_bcm.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    Set_bcm set_bcm;
    set_bcm.setModal(true);
    set_bcm.exec();
}
