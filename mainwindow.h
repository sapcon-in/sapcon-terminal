#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"quary_box.h"
#include<QList>
#include <QRect>
#include<QPushButton>
#include"answer_box.h"
#include<QComboBox>
#include"serialcomm.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
   // QList<quary_box*> boxlist;
    quary_box *quary_mode ;
    answer_box  *answer_mode;
    serialComm *serialinterface;


    ~MainWindow();
signals:


public slots:

    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
