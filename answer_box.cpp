#include "answer_box.h"
#include<qdebug.h>

answer_box::answer_box(QGridLayout *layout, QWidget *parent) :
    QWidget(parent)
{

    this->layout = layout;
    adding_row = new QPushButton("&Answer");
    adding_row->setMaximumHeight(30);
    layout->addWidget(adding_row,0,14,1,2);
    connect(adding_row, SIGNAL(clicked()),this, SLOT(add_row()));
      validator = new QIntValidator(50, 65535, this);
      for(int i=0;i<ANSWER_ROW_LIMIT;i++)add_row();
      for(int i=1;i<=ANSWER_ROW_LIMIT;i++){delete_row(i);}

      settings = new QSettings("New_Sapcon_terminal","sapcon");

}
answer_box::~answer_box()
{


   delete answer_val;
   delete answer_checkBox;
   delete answer_commands;
   delete answer_timer;
   delete answer_continuous;
   delete answer_cross;
   delete answer_request;
   delete answer_del;
   delete adding_row;
}

void answer_box::checkbox_status(int x)
{
    x-=1;
    emit send_reply(answer_commandslist.at(x)->text(),answer_timerlist.at(x)->text(),\
                    answer_val_list.at(x)->text(),x,answer_checkBoxlist.at(x)->isChecked());
//check_box
//command received
//timer
//send commands




    //qDebug()<<x;
    //qDebug()<<answer_commandslist.count();
}

void answer_box::add_row_group(int row,int i)
{

    QWidget *parent = (QWidget*)this->parent();
    answer_checkBox = new QCheckBox(parent);
    answer_commands = new QLineEdit(parent);
    answer_timer = new QLineEdit(parent);
     answer_val = new QLineEdit("",parent);

    answer_checkBox->setMaximumSize(18,18);
    answer_timer->setMaximumWidth(50);
    answer_timer->setValidator(validator);
    answer_timer->setText("500");
    answer_checkBoxlist.append(answer_checkBox);
    answer_commandslist.append(answer_commands);
    answer_timerlist.append(answer_timer);
    answer_val_list.append(answer_val);

    layout->addWidget(answer_checkBox,row,0,1,1);
    layout->addWidget(answer_commands,row,1,1,3);
    layout->addWidget(answer_timer,row,4,1,1);
    layout->addWidget(answer_val,row,5,1,3);


    answer_continuous = new QSignalMapper(parent);
    connect(answer_checkBox, SIGNAL(clicked()), answer_continuous, SLOT(map()));
    answer_continuous->setMapping(answer_checkBoxlist.last(),i*2-1);
    connect(answer_continuous,SIGNAL(mapped(int)),this,SLOT(checkbox_status(int)));


    answer_checkBox = new QCheckBox(parent);
    answer_commands = new QLineEdit(parent);
    answer_timer = new QLineEdit(parent);
    answer_val = new QLineEdit("",parent);
    answer_checkBox->setMaximumSize(18,18);
    answer_timer->setMaximumWidth(50);
    answer_timer->setText("500");
    answer_checkBoxlist.append(answer_checkBox);
    answer_commandslist.append(answer_commands);
    answer_timerlist.append(answer_timer);
    answer_val_list.append(answer_val);

    answer_cross = new QPushButton("&X",parent);
    answer_cross->setMaximumWidth(30);
    answer_cross->setFont(QFont("Comic Sans MS",10,QFont::Bold));
    answer_cross->setStyleSheet("background-color: rgb(255,30,0);");
    answer_cross_list.append(answer_cross);


    layout->addWidget(answer_checkBox,row,9,1,1);
    layout->addWidget(answer_commands,row,10,1,3);
    layout->addWidget(answer_timer,row,13,1,1);
    layout->addWidget(answer_val,row,14,1,3);
    layout->addWidget(answer_cross,row,17,1,1);


    answer_continuous = new QSignalMapper(parent);
    connect(answer_checkBox, SIGNAL(clicked()), answer_continuous, SLOT(map()));
    answer_continuous->setMapping(answer_checkBoxlist.last(),i*2);
    connect(answer_continuous,SIGNAL(mapped(int)),this,SLOT(checkbox_status(int)));

    answer_del = new QSignalMapper(parent);
    connect(answer_cross, SIGNAL(clicked()), answer_del, SLOT(map()));
    answer_del->setMapping(answer_cross_list.last(),i);
    connect(answer_del,SIGNAL(mapped(int)),this,SLOT(delete_row(int)));

}

void answer_box::send_commands(int x)
{
    qDebug()<<x;
}


void answer_box::enable_row(int x)
{
    answer_checkBoxlist.at(2*(x-1))->show();
    answer_checkBoxlist.at(2*(x-1)+1)->show();
    answer_commandslist.at(2*(x-1))->show();
    answer_commandslist.at(2*(x-1)+1)->show();
    answer_timerlist.at(2*(x-1))->show();
    answer_timerlist.at(2*(x-1)+1)->show();
    answer_val_list.at(2*(x-1))->show();
    answer_val_list.at(2*(x-1)+1)->show();
    answer_cross_list.at(x-1)->show();
}



void answer_box::delete_row(int x)
{
qDebug()<<x;
//x=1;
answer_checkBoxlist.at(2*(x-1))->hide();
answer_checkBoxlist.at(2*(x-1)+1)->hide();
answer_commandslist.at(2*(x-1))->hide();
answer_commandslist.at(2*(x-1)+1)->hide();
answer_timerlist.at(2*(x-1))->hide();
answer_timerlist.at(2*(x-1)+1)->hide();
answer_val_list.at(2*(x-1))->hide();
answer_val_list.at(2*(x-1)+1)->hide();
answer_cross_list.at(x-1)->hide();
}


void answer_box::add_row(){

static int i=1;
        for(int x=0;x<answer_cross_list.count();x++)
        {
            if(answer_cross_list.at(x)->isHidden())
            {
                enable_row(x+1);
                qDebug()<<x;
                return;
            }
        }
if(i<(ANSWER_ROW_LIMIT+1))
{
     row_count[i]=layout->rowCount();
     add_row_group(row_count[i],i);
     i++;
}
}


void answer_box::save_parameter(QString profile)
{

    settings->beginGroup(profile);
    for(int i=0;i<ANSWER_ROW_LIMIT;i++)
    {
           settings->setValue("ansCmd"+QString::number(i),answer_commandslist.at(i)->text());
   //        settings->setValue("ansTime"+QString::number(i),answer_timerlist.at(i)->text());
           settings->setValue("ansReply"+QString::number(i),answer_val_list.at(i)->text());

    }
    settings->endGroup();
}

void answer_box::get_parameter(QString profile)
{
    settings->beginGroup(profile);
      for(int i=0;i<ANSWER_ROW_LIMIT;i++)
      {
        answer_commandslist.at(i)->setText(settings->value("ansCmd"+QString::number(i)).toString());
   //     answer_timerlist.at(i)->setText(settings->value("ansTime"+QString::number(i)).toString());
        answer_val_list.at(i)->setText(settings->value("ansReply"+QString::number(i)).toString());
      }

    settings->endGroup();
}


