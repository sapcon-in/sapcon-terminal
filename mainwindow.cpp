#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quary_box.h"
#include"answer_box.h"
#include"qextserialport.h"
#include <QScreen>
#include<QDebug>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setMinimumSize(600,600);
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->gridLayout);
    serialinterface = new serialComm(ui->gridLayout,this);
    quary_mode = new quary_box(ui->gridLayout,this);
    answer_mode = new answer_box(ui->gridLayout,this);
    connect(quary_mode,SIGNAL(tx_serial(QString)),serialinterface,SLOT(tx_serial_exe(QString)));
    connect(answer_mode,SIGNAL(send_reply(QString,QString,QString,int,bool)),serialinterface,SLOT(compare_match(QString,QString,QString,int,bool)));
    connect(serialinterface,SIGNAL(save_parameter_data(QString)),quary_mode,SLOT(save_parameter(QString)));
    connect(serialinterface,SIGNAL(save_parameter_data(QString)),answer_mode,SLOT(save_parameter(QString)));
    connect(serialinterface,SIGNAL(get_parameter_data(QString)),answer_mode,SLOT(get_parameter(QString)));
    connect(serialinterface,SIGNAL(get_parameter_data(QString)),quary_mode,SLOT(get_parameter(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}



