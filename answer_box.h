#ifndef ANSWER_BOX_H
#define ANSWER_BOX_H

#include <QWidget>
#include <QPushButton>
#include<QCheckBox>
#include<QLineEdit>
#include<QBoxLayout>
#include <QSignalMapper>
#include<QList>
#include<QObject>
#include<QIntValidator>
#include<QSettings>


#define ANSWER_ROW_LIMIT 5

class QGridLayout;

class answer_box : public QWidget
{
    Q_OBJECT
public:
    int row_count[ANSWER_ROW_LIMIT];
    QLineEdit *answer_val;
    QCheckBox *answer_checkBox;
    QLineEdit *answer_commands;
    QLineEdit *answer_timer;
    QSignalMapper *answer_continuous;
    QPushButton *answer_cross;
    QGridLayout *layout;
    QSignalMapper *answer_request;
    QSignalMapper *answer_del;
    QPushButton   *adding_row;
    QList<QCheckBox*>  answer_checkBoxlist;
    QList<QLineEdit*> answer_commandslist;
    QList<QLineEdit*> answer_timerlist;
    QList<QLineEdit*> answer_val_list;
    QList<QPushButton*> answer_cross_list;
    QSettings *settings;

QIntValidator *validator;
    explicit answer_box(QGridLayout *layout,QWidget *parent = 0);
    ~answer_box();

 signals:
    void send_reply(QString,QString,QString,int,bool);

 public slots:
    void checkbox_status(int);
    void add_row();
    void add_row_group(int row , int i);
    void send_commands(int);
    void delete_row(int x);
    void enable_row(int x);
  //  void send_to_serial();
    void save_parameter(QString profile);
    void get_parameter(QString profile);
};

#endif // ANSWER_BOX_H
