#include "quary_box.h"
#include"mainwindow.h"
#include<qdebug.h>
#include<QTimer>



quary_box::quary_box(QGridLayout *layout, QWidget *parent) :
    QWidget(parent)
{
    this->layout = layout;
    adding_row = new QPushButton("&Quary");
    adding_row->setMaximumHeight(30);
    layout->addWidget(adding_row,0,16,1,1);
    connect(adding_row, SIGNAL(clicked()),this, SLOT(add_row()));   
    quary_timeout= new QTimer();
    connect(quary_timeout, SIGNAL(timeout()), this, SLOT(send_to_serial()));
     validator = new QIntValidator(50, 65535, this);
     for(int i=0;i<QUARY_ROW_LIMIT;i++){add_row();}
     for(int i=1;i<=QUARY_ROW_LIMIT;i++){delete_row(i);}

      settings = new QSettings("New_Sapcon_terminal","sapcon");




}
quary_box::~quary_box()
{

   delete quary_pushbutton;
   delete quary_checkBox;
   delete quary_commands;
   delete quary_timer;
   delete quary_continuous;
   delete quary_cross;
   delete quary_request;
   delete quary_del;
   delete adding_row;
}

void quary_box::checkbox_status(int x)
{
    x=x;

    for(int i=0;i<quary_cross_list.count();i++)
    {
        if(quary_checkBoxlist.at(i)->isChecked())++checked;
    }

    if(checked==0)quary_timeout->stop();
    else quary_timeout->start(100);

}

void quary_box::add_row_group(int row,int i)
{
    QWidget *parent = (QWidget*)this->parent();
    quary_checkBox = new QCheckBox(parent);
    quary_commands = new QLineEdit(parent);
    quary_timer = new QLineEdit(parent);
    quary_timer->setValidator(validator);
    quary_pushbutton = new QPushButton("M"+QString::number(i*2-1),parent);
    quary_pushbutton->setMaximumWidth(30);
    quary_checkBox->setMaximumSize(18,18);
    quary_timer->setMaximumWidth(50);

    quary_checkBoxlist.append(quary_checkBox);
    quary_commandslist.append(quary_commands);
    quary_timerlist.append(quary_timer);
    quary_pushbutton_list.append(quary_pushbutton);
    quary_timer->setText("500");
    layout->addWidget(quary_checkBox,row,0,1,1);
    layout->addWidget(quary_commands,row,1,1,5);
    layout->addWidget(quary_timer,row,6,1,1);
    layout->addWidget(quary_pushbutton,row,7,1,1);


    quary_continuous = new QSignalMapper(parent);
    connect(quary_checkBox, SIGNAL(clicked()), quary_continuous, SLOT(map()));
    quary_continuous->setMapping(quary_checkBoxlist.last(),i*2-1);
    connect(quary_continuous,SIGNAL(mapped(int)),this,SLOT(checkbox_status(int)));

    quary_request = new QSignalMapper(parent);
    connect(quary_pushbutton, SIGNAL(clicked()), quary_request, SLOT(map()));
    quary_request->setMapping(quary_pushbutton_list.last(),i*2-1);
    connect(quary_request,SIGNAL(mapped(int)),this,SLOT(send_commands(int)));

    quary_checkBox = new QCheckBox(parent);
    quary_commands = new QLineEdit(parent);
    quary_timer = new QLineEdit(parent);
    quary_pushbutton = new QPushButton("M"+QString::number(i*2),parent);


    quary_pushbutton->setMaximumWidth(30);
    quary_checkBox->setMaximumSize(18,18);
    quary_timer->setMaximumWidth(50);
    quary_timer->setText("500");
    quary_timer->setValidator(validator);

    quary_checkBoxlist.append(quary_checkBox);
    quary_commandslist.append(quary_commands);
    quary_timerlist.append(quary_timer);
    quary_pushbutton_list.append(quary_pushbutton);

    quary_cross = new QPushButton("&X",parent);
    quary_cross->setMaximumWidth(30);
    quary_cross->setFont(QFont("Comic Sans MS",10,QFont::Bold));
    quary_cross->setStyleSheet("background-color: rgb(255,30,0);");
    quary_cross_list.append(quary_cross);

    layout->addWidget(quary_checkBox,row,9,1,1);
    layout->addWidget(quary_commands,row,10,1,5);

    layout->addWidget(quary_timer,row,15,1,1);
    layout->addWidget(quary_pushbutton,row,16,1,1);
    layout->addWidget(quary_cross,row,17,1,1);


    quary_continuous = new QSignalMapper(parent);
    connect(quary_checkBox, SIGNAL(clicked()), quary_continuous, SLOT(map()));
    quary_continuous->setMapping(quary_checkBoxlist.last(),i*2);
    connect(quary_continuous,SIGNAL(mapped(int)),this,SLOT(checkbox_status(int)));

    quary_request = new QSignalMapper(parent);
    connect(quary_pushbutton, SIGNAL(clicked()), quary_request, SLOT(map()));
    quary_request->setMapping(quary_pushbutton_list.last(),i*2);
    connect(quary_request,SIGNAL(mapped(int)),this,SLOT(send_commands(int)));


    quary_del = new QSignalMapper(parent);
    connect(quary_cross, SIGNAL(clicked()), quary_del, SLOT(map()));
    quary_del->setMapping(quary_cross_list.last(),i);
    connect(quary_del,SIGNAL(mapped(int)),this,SLOT(delete_row(int)));

}

void quary_box::send_commands(int x)
{   
  emit tx_serial(quary_commandslist.at(x-1)->text());
}


void quary_box::enable_row(int x)
{
    quary_checkBoxlist.at(2*(x-1))->show();
    quary_checkBoxlist.at(2*(x-1)+1)->show();
    quary_commandslist.at(2*(x-1))->show();
    quary_commandslist.at(2*(x-1)+1)->show();
    quary_timerlist.at(2*(x-1))->show();
    quary_timerlist.at(2*(x-1)+1)->show();
    quary_pushbutton_list.at(2*(x-1))->show();
    quary_pushbutton_list.at(2*(x-1)+1)->show();
    quary_cross_list.at(x-1)->show();
}



void quary_box::delete_row(int x)
{
qDebug()<<x;
quary_checkBoxlist.at(2*(x-1))->hide();
quary_checkBoxlist.at(2*(x-1))->setChecked(false);
quary_checkBoxlist.at(2*(x-1)+1)->hide();
quary_checkBoxlist.at(2*(x-1)+1)->setChecked(false);
quary_commandslist.at(2*(x-1))->hide();
quary_commandslist.at(2*(x-1)+1)->hide();
quary_timerlist.at(2*(x-1))->hide();
quary_timerlist.at(2*(x-1)+1)->hide();
quary_pushbutton_list.at(2*(x-1))->hide();
quary_pushbutton_list.at(2*(x-1)+1)->hide();
quary_cross_list.at(x-1)->hide();
}


void quary_box::add_row(){

    static int i=1;
            for(int x=0;x<quary_cross_list.count();x++)
            {
                if(quary_cross_list.at(x)->isHidden())
                {
                    enable_row(x+1);
                    qDebug()<<x;
                    return;
                }
            }
    if(i<(QUARY_ROW_LIMIT+1))
    {
         row_count[i]=layout->rowCount();
         add_row_group(row_count[i],i);
         i++;
    }
}



void quary_box::send_to_serial()
{
    static int x=0;
    if(quary_checkBoxlist.count()==0){quary_timeout->stop();return;}
    if(checked==0){quary_timeout->stop();return;}
    else
    if(quary_checkBoxlist.at(x)->isChecked())
    {
        emit tx_serial(quary_commandslist.at(x)->text());
        quary_timeout->start(quary_timerlist.at(x)->text().toInt());
    } 
    else quary_timeout->start(0);
    x++;
    if(x>=quary_checkBoxlist.count())x=0;
}

void quary_box::save_parameter(QString profile)
{   
    settings->beginGroup(profile);
    for(int i=0;i<QUARY_ROW_LIMIT;i++)
    {
           settings->setValue("quaryCmd"+QString::number(i),quary_commandslist.at(i)->text());
     //      settings->setValue("quaryTime"+QString::number(i),quary_timerlist.at(i)->text());
    }
    settings->endGroup();
}

void quary_box::get_parameter(QString profile)
{
    settings->beginGroup(profile);
      for(int i=0;i<QUARY_ROW_LIMIT;i++)
      {
        quary_commandslist.at(i)->setText(settings->value("quaryCmd"+QString::number(i)).toString());
      //  quary_timerlist.at(i)->setText(settings->value("quaryTime"+QString::number(i)).toString());
      }

    settings->endGroup();
}


