#ifndef QUARY_BOX_H
#define QUARY_BOX_H

#include <QWidget>
#include <QPushButton>
#include<QCheckBox>
#include<QLineEdit>
#include<QBoxLayout>
#include <QSignalMapper>
#include<QList>
#include<QObject>
#include<QTimer>
#include<QIntValidator>
#include<QSettings>

#define QUARY_ROW_LIMIT 7
class QGridLayout;


class quary_box : public QWidget
{
    Q_OBJECT
public:
    int row_count[QUARY_ROW_LIMIT];
   QPushButton *quary_pushbutton;
   QCheckBox *quary_checkBox;
   QLineEdit *quary_commands;
   QLineEdit *quary_timer;
   QSignalMapper *quary_continuous;
   QPushButton *quary_cross;
   QGridLayout *layout;
   QSignalMapper *quary_request;
   QSignalMapper *quary_del;
   QPushButton   *adding_row;
int checked;
QIntValidator *validator;
   QSettings *settings;

   QList<QCheckBox*>  quary_checkBoxlist;
   QList<QLineEdit*> quary_commandslist;
   QList<QLineEdit*> quary_timerlist;
   QList<QPushButton*> quary_pushbutton_list;
   QList<QPushButton*> quary_cross_list;
   bool hexMode = false;


   QTimer *quary_timeout;


   explicit quary_box(QGridLayout *layout,QWidget *parent = 0);
   ~quary_box();
    
signals:

   void tx_serial(QString);

    
public slots:
   void checkbox_status(int);
   void add_row();
   void add_row_group(int row, int i);
   void send_commands(int x);
   void delete_row(int x);
   void enable_row(int x);    
   void send_to_serial();
 //  void change_time_of_timer(QString x);
   void save_parameter(QString profile);
   void get_parameter(QString profile);
};

#endif // QUARY_BOX_H
