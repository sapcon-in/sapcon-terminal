#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QWidget>
#include<QList>
#include <QRect>
#include<QPushButton>
#include"answer_box.h"
#include<QComboBox>
#include"qextserialport.h"
#include "qextserialenumerator.h"
#include<QPlainTextEdit>
#include<QTimer>
#include<QLabel>
#include<QDateTime>
#include <QTime>
#include <QString>
#include <QDir>
#include <QFile>
#include<QFileDialog>
#include<QProcess>
#include<QIntValidator>
class QGridLayout;

class serialComm : public QWidget
{
    Q_OBJECT
public:
    
    explicit serialComm(QGridLayout *layout,QWidget *parent = 0);
    QList<QextPortInfo> portnumber;
    QextSerialEnumerator *getportname;
    QComboBox *baudrate;
    QComboBox *comports;
    QComboBox *profiles;
    QPushButton *connect_button;
    QPushButton *refresh_button;
    QPushButton *save_button;
    QPushButton *get_button;
    QCheckBox *time_stamp;
    QCheckBox *append_new_line;
    QList<QString> baudrate_list;
    QList<QString> comports_list;
    QextSerialPort *port;
    QList<QString> profile_list;
    QPlainTextEdit *io_plaintext;
    QTimer *timer; // for usb
    QCheckBox *log_checkbox;
    QLineEdit *log_time_lineedit;
    QLabel *log_label;
    QPushButton *clear_display;
    QComboBox *font_size;
    QPushButton *log_file;
    QPushButton *clear_file;
    QLabel *dir_path;
    QString SerialIn;
    bool append_time;
    QString dirpath;
    QFile *name_of_file;
    QTime time_of_log;
    QDateTime *date_time;
     bool ser_connected;
    QStringList receivedList;
    QStringList TimerList;
    QStringList SendList;
    bool checkList[10];
    int  checkNumber[10];
    QTimer *answer_timer;
    int reply_count;
    QComboBox *update_graph;
    QString tempFile;
    QProcess *filter;
    QIntValidator *validator;
     QString buffer;
     QDir dir;
     QPushButton *filter_brows;
     QCheckBox   *filter_ckeckbox;
     QCheckBox *hexToAscii;
     QLabel *hextoAscii_label;
     QString filterpath;
     QLabel *filterDisp;
     QCheckBox *timestamp;
     QCheckBox *new_line;
     QLabel *time_stamp_checkbox;
     QLabel *new_line_checkbox;


     ~serialComm();

signals:
     void save_parameter_data(QString);
     void get_parameter_data(QString);
    
public slots:
    void set_baudrate_on_combobox();
    void set_comports_on_combobox();
    void set_connection(int x);
    void set_profiles_on_combobox();
    void responceFromInstruments();
    void timeoutfunction();
    void set_log_mode();
    void clear_display_textedit();
    void del_log_path();
    void set_log_path();
    void set_font(int x);
    void set_connection_temp();
    void tx_serial_exe(QString);
    void filter_proc_error(QProcess::ProcessError error);
    //void compare_match();
    void compare_match(QString, QString, QString, int, bool y);
    void timeoutAnswer();
    void save_parameter();
    void get_parameter();
    void set_filter_path();
    void hex_mode_toggle(bool);

};

#endif // SERIALCOMM_H
