#include "serialcomm.h"
#include"qextserialport.h"
#include "qextserialenumerator.h"
#include<QDebug>
#include<QDir>
#include<QString>
#include<QFile>
 #include <QMessageBox>
#include <QDebug>


serialComm::serialComm(QGridLayout *layout, QWidget *parent) :
      QWidget(parent)
{
    port = NULL;
    ser_connected = false;
    connect_button = new QPushButton(tr("&Connect"));
    connect_button->setMinimumWidth(100);
    connect_button->setMaximumHeight(30);
    connect_button->setMinimumWidth(70);
    layout->addWidget(connect_button,0,3,1,1);
    connect(connect_button,SIGNAL(clicked()),this,SLOT(set_connection_temp()));

    baudrate = new QComboBox();
    set_baudrate_on_combobox();
    baudrate->setMaximumHeight(30);
      baudrate->setMinimumWidth(70);
    layout->addWidget(baudrate,0,1,1,1);
    connect(baudrate,SIGNAL(currentIndexChanged(int)),this,SLOT(set_connection(int)));

    comports = new QComboBox();
    set_comports_on_combobox();
    comports->setMaximumHeight(30);
    comports->setMinimumWidth(70);
    layout->addWidget(comports,0,2,1,1);
    connect(comports,SIGNAL(currentIndexChanged(int)),this,SLOT(set_connection(int)));

   /* connect_button = new QPushButton(tr("&Connect"));
    connect_button->setMinimumWidth(100);
    connect_button->setMaximumHeight(30);
    connect_button->setMinimumWidth(70);
    layout->addWidget(connect_button,0,3,1,1);
    connect(connect_button,SIGNAL(clicked()),this,SLOT(set_connection_temp()));*/


    refresh_button = new QPushButton("&Refresh");
    refresh_button->setMaximumHeight(30);
    refresh_button->setMinimumWidth(70);
    layout->addWidget(refresh_button,0,4,1,1);
    connect(refresh_button,SIGNAL(clicked()),this,SLOT(set_comports_on_combobox()));

QStringList temp;
temp.append("3");
temp.append("6");
temp.append("9");
temp.append("12");
temp.append("15");
temp.append("25");
temp.append("50");
temp.append("75");
temp.append("100");

     validator = new QIntValidator(50, 65535, this);



    profiles = new QComboBox();
    set_profiles_on_combobox();
    profiles->setMaximumHeight(30);
    layout->addWidget(profiles,0,5,1,1);

    save_button = new QPushButton(tr("&Save"));
    save_button->setMinimumWidth(70);
    save_button->setMaximumHeight(30);
    layout->addWidget(save_button,0,6,1,1);
    connect(save_button,SIGNAL(clicked()),this,SLOT(save_parameter()));

    get_button = new QPushButton(tr("&Get"));
    get_button->setMinimumWidth(70);
    get_button->setMaximumHeight(30);
    layout->addWidget(get_button,0,7,1,1);
    connect(get_button,SIGNAL(clicked()),this,SLOT(get_parameter()));




    clear_display = new QPushButton("&Empty");
    clear_display->setMaximumHeight(30);
    layout->addWidget(clear_display,1,1,1,1);
    connect(clear_display,SIGNAL(clicked()),this,SLOT(clear_display_textedit()));

    font_size = new QComboBox();
    font_size->setMaximumHeight(30);
    font_size->addItem("06");
    font_size->addItem("08");
    font_size->addItem("10");
    font_size->addItem("12");
    font_size->addItem("14");
    font_size->addItem("16");
    font_size->setCurrentIndex(3);
    layout->addWidget(font_size,1,2,1,1);
    connect(font_size,SIGNAL(currentIndexChanged(int)),this,SLOT(set_font(int)));


    log_file = new QPushButton("&Log");
    log_file->setMaximumHeight(30);
    layout->addWidget(log_file,1,3,1,1);
    connect(log_file,SIGNAL(clicked()),this,SLOT(set_log_path()));

    clear_file = new QPushButton("&Delete");
    clear_file->setMaximumHeight(30);
    layout->addWidget(clear_file,1,4,1,1);
    connect(clear_file,SIGNAL(clicked()),this,SLOT(del_log_path()));

    dir_path = new QLabel();
    dir_path->setText("Path:");
    dir_path->setMaximumHeight(20);
    layout->addWidget(dir_path,1,5,1,7);




    log_checkbox = new QCheckBox();
    log_checkbox->setMaximumSize(18,18);
    layout->addWidget(log_checkbox,1,14,1,1,Qt::AlignRight);
    connect(log_checkbox,SIGNAL(clicked()),this,SLOT(set_log_mode()));

    log_label = new QLabel("Connection \nCheck");
    log_label->setMaximumSize(80,30);
    layout->addWidget(log_label,1,15,1,1);


    log_time_lineedit = new QLineEdit("10000");
    log_time_lineedit->setValidator(validator);
    log_time_lineedit->setMinimumSize(50,20);
    log_time_lineedit->setMaximumSize(100,20);
    layout->addWidget(log_time_lineedit,1,16,1,1);

    /*
     QCheckBox timestamp;
     QCheckBox new_line;
     QLabel time_checkbox;
     QLabel new_line_checkbox;
     */
    timestamp = new QCheckBox();
    timestamp->setMaximumSize(15,15);
    layout->addWidget(timestamp,2,14,1,1,Qt::AlignRight);

    time_stamp_checkbox = new QLabel("Time");
    time_stamp_checkbox->setMaximumSize(80,30);
    layout->addWidget(time_stamp_checkbox,2,15,1,1);

    new_line = new QCheckBox();
    new_line->setMaximumSize(18,18);
    layout->addWidget(new_line,2,15,1,1,Qt::AlignRight);

    new_line_checkbox = new QLabel("NO NL");
    new_line_checkbox->setMaximumSize(80,30);
    layout->addWidget(new_line_checkbox,2,16,1,1);

    filter_ckeckbox = new QCheckBox();
    filter_ckeckbox->setMaximumSize(18,18);
    layout->addWidget(filter_ckeckbox,2,1,1,1,Qt::AlignRight);


    filter_brows = new QPushButton("&Filter");
    filter_brows->setMaximumHeight(30);
    layout->addWidget(filter_brows,2,2,1,1);
    connect(filter_brows,SIGNAL(clicked()),this,SLOT(set_filter_path()));

    update_graph = new QComboBox();
    update_graph->addItems(temp);
    update_graph->setMaximumHeight(30);
    update_graph->setMinimumWidth(70);
    layout->addWidget(update_graph,2,3,1,1);

    filterDisp = new QLabel("FPath:");
    layout->addWidget(filterDisp,2,4,1,5,Qt::AlignLeft);

    hexToAscii = new QCheckBox();
    hexToAscii->setMaximumSize(18,18);
    layout->addWidget(hexToAscii,2,5,1,1,Qt::AlignRight);

    hextoAscii_label = new QLabel("Hex Data");
    layout->addWidget(hextoAscii_label,2,6,1,3,Qt::AlignHCenter);


    io_plaintext = new QPlainTextEdit();
    io_plaintext->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    io_plaintext->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    io_plaintext->setMaximumBlockCount(1000);
    io_plaintext->setReadOnly(true);
    layout->addWidget(io_plaintext,layout->rowCount(),1,2,16);

    connect(hexToAscii,SIGNAL(clicked(bool)),this,SLOT(hex_mode_toggle(bool)));

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeoutfunction()));
    set_font(3);
    answer_timer = new QTimer();
    connect(answer_timer, SIGNAL(timeout()), this, SLOT(timeoutAnswer()));

     filter = new QProcess();
     connect(filter,SIGNAL(error(QProcess::ProcessError)),this,SLOT(filter_proc_error(QProcess::ProcessError)));



 }



void serialComm::set_filter_path()
{
    QString oldpath;
    oldpath = filterpath;
    filterpath = QFileDialog::getOpenFileName(this, tr("Save File"),
                                           "",
                                           tr("(*.sh)"));/*getExistingDirectory( this, tr("Open Directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);*/
    if(filterpath.isEmpty())filterpath= oldpath;

    filterDisp->setText("FPath:"+filterpath);


}


void serialComm::set_log_path(){   
QString oldpath;
oldpath = dirpath;

    dirpath = QFileDialog::getSaveFileName(this, tr("Save File"),
                                           "",
                                           tr("(*.csv )"));
    /*getExistingDirectory( this, tr("Open Directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);*/


    if(dirpath.isEmpty())dirpath = oldpath;
    if(!dirpath.isEmpty())
    {
tempFile = dirpath;
tempFile.truncate(tempFile.lastIndexOf("/"));


    if(!dirpath.endsWith(".CSV",Qt::CaseInsensitive))
    {
        dirpath.append(".CSV");
    }

    dir_path->setText("Path:= .."+dirpath.right(50));
            qDebug()<<tempFile<<dirpath;


    if(!QFile::exists(filterpath))
        QFile::copy(":/new/prefix1/.filter.sh",tempFile+"/.filter.sh");
    else
        QFile::copy(filterpath,tempFile+"/.filter.sh");

    QFile::setPermissions(tempFile+"/.filter.sh",QFile::ExeOther|QFile::ReadOther|QFile::WriteOther|QFile::ReadOwner|QFile::ReadUser|QFile::ExeUser|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup);




}
}

void serialComm::del_log_path()
{
    QFile file(dirpath);
    file.remove();
    file.close();
    dirpath.clear();
    dir_path->clear();
}

void serialComm::set_font(int x)
{
    x=x;
    QFont test;
    test.setPointSize(font_size->currentText().toInt());
    io_plaintext->setFont(test);
}


 serialComm::~serialComm()
{

    delete baudrate;
    delete getportname;
    delete comports;
    delete profiles;
    delete connect_button;
    delete refresh_button;
    delete time_stamp;
    delete append_new_line;
    delete port;
    delete timer;
    delete log_checkbox;
    delete log_time_lineedit;
    delete log_label;


}

 void serialComm::clear_display_textedit()
{
     io_plaintext->clear();
 }

void serialComm::timeoutfunction(){

    QString str1 =  comports->currentText();
    str1.truncate(6);
    qDebug()<<str1;

    portnumber = getportname->getPorts();

    long time = log_time_lineedit->text().toLong();
    if(time!=0) timer->start(time);

    for(int i=0;i<portnumber.count();i++)
    {
       if(comports->currentText() == portnumber.at(portnumber.count()-i-1).portName)
       {
           return;
       }
    }
    for(int i=0;i<portnumber.count();i++)
    {
       QString str2 = portnumber.at(portnumber.count()-i-1).portName;
       str2.truncate(6);
       qDebug()<<str2;

      if( str1==str2)
       {
         set_comports_on_combobox();
         set_connection(1);
         break;
       }
    }
}
void serialComm::filter_proc_error(QProcess::ProcessError error){
    qDebug()<<error<<filter->errorString();

}

void serialComm::set_connection_temp()
{

    if(ser_connected==false)
    {
        set_connection(1);
        connect_button->setText(tr("&Disconnect"));     
        if(log_checkbox->isChecked())
        {
            long time = log_time_lineedit->text().toLong();
            if(time!=0)
            timer->start(time);
        }
    }
    else
    {
        if(port->isOpen()) port->close();
        connect_button->setText(tr("&Connect"));
        ser_connected=false;
        timer->stop();
        qDebug()<<"disconnected";
    }
}

void serialComm::set_baudrate_on_combobox()
{

   // baudrate_list.append("110");
 //   baudrate_list.append("300");
  //  baudrate_list.append("600");
    baudrate_list.append("1200");
    baudrate_list.append("2400");
    baudrate_list.append("4800");
    baudrate_list.append("9600");
  //  baudrate_list.append("14400");
    baudrate_list.append("19200");
  //  baudrate_list.append("28800");
    baudrate_list.append("38400");
   // baudrate_list.append("56000");
    baudrate_list.append("57600");
    baudrate_list.append("115200");
    baudrate_list.append("962100");
 //   baudrate_list.append("128000");
    baudrate->addItems(baudrate_list);
}

void serialComm::set_comports_on_combobox()
{
    int temp=0;

    disconnect(comports,SIGNAL(currentIndexChanged(int)),this,SLOT(set_connection(int)));
    QString str1 =comports->currentText();
    str1.truncate(6);
    portnumber = getportname->getPorts();
    comports->clear();
    for(int i=0;i<portnumber.count();i++)
    {
        QString str2 = portnumber.at(portnumber.count()-i-1).portName;
        str2.truncate(6);
        if(str1==str2) temp = i;
        bool realPort = false;
        #ifdef Q_OS_LINUX
        if (QString(portnumber.at(portnumber.count()-i-1).portName).startsWith("ttyUSB"))
                realPort = true;
        #endif
        if (realPort)
            comports->addItem(portnumber.at(portnumber.count()-i-1).portName);
    }
comports->setCurrentIndex(temp);
 connect(comports,SIGNAL(currentIndexChanged(int)),this,SLOT(set_connection(int)));
 ser_connected = false;
 connect_button->setText("&Connect");
}


void serialComm::set_connection(int x)
{
  QString old_port;
  if(port!=NULL)delete port;
  port = new QextSerialPort(comports->currentText());
  qDebug()<<comports->currentText();
  x= port->open(QIODevice::ReadWrite);
   if(!x) {
        ser_connected = false;
        connect_button->setText("&Connect");QMessageBox::warning(this,"Warning","Port is not open\n please try again");
        return;}
  port->setBaudRate(BaudRateType(baudrate->currentText().toLong()));
  port->setFlowControl(FLOW_OFF);
  port->setStopBits(STOP_1);
  port->setDataBits(DATA_8);
  port->setParity(PAR_NONE);
  connect(port,SIGNAL(readyRead()),this,SLOT(responceFromInstruments()));
  old_port = comports->currentText();
  ser_connected = true;
  connect_button->setText("&Disconnect");
  qDebug()<<"connected";

}




void serialComm::set_profiles_on_combobox()
{
    profile_list.append("Profile1");
    profile_list.append("Profile2");
    profile_list.append("Profile3");
    profile_list.append("Profile4");
    profile_list.append("Profile5");
    profile_list.append("Profile6");
    profile_list.append("Profile7");
    profiles->addItems(profile_list);

}

void serialComm::set_log_mode()
{
    if(log_checkbox->isChecked())
    {
        long time = log_time_lineedit->text().toLong();
        if(time!=0)
        timer->start(time);
    }
  else
    {
        timer->stop();
    }
}


void serialComm::responceFromInstruments()
{
   static int save_values=0;
    QString temp,New_time,New_Date;
    static bool update_time =false;
    QByteArray test3;
    test3=port->readAll();
    temp = QString(test3);



    if(receivedList.count()>0) SerialIn+=temp;


    if((update_time== true)&&(append_time==true))
    {
     New_time = QTime::currentTime().toString("hh-mm-ss-zzz : ");
     New_Date = QDate::currentDate().toString("yyyy-MM-dd-");
    }

    for(int i=0;i<receivedList.count();i++) //fixit
    {
        if(SerialIn.contains(receivedList.at(i)))//checked
        {
            answer_timer->start(TimerList.at(i).toInt());
            reply_count = i;
            SerialIn.clear();
        }
    }

    if((temp.indexOf('\r'))!=-1){update_time = true;save_values++;}
    else if((temp.indexOf('\n')!=-1))update_time = true;
    else if(update_time==true && timestamp->isChecked())
    {
        io_plaintext->insertPlainText(New_Date.toLatin1()+New_time.toLatin1());
        if(!dirpath.isEmpty())
        {
        QFile file(dirpath);
        file.open(QIODevice::Append |QIODevice::WriteOnly | QIODevice::ReadOnly);
       // file.write(New_Date.toLatin1());
      //  file.write(New_time.toLatin1());
        file.close();
        }
        update_time = false;
    }
    io_plaintext->moveCursor(QTextCursor::End);
    if(hexToAscii->isChecked()){
        io_plaintext->insertPlainText(QString(test3.toHex()));
        if(test3.length() > 10)
            io_plaintext->appendPlainText("\n");

    }
    else{
        io_plaintext->insertPlainText(temp.toLatin1());
    }

    if(!dirpath.isEmpty())
    {
    buffer.append(temp);
    QFile file(dirpath);
    file.open(QIODevice::Append );
    if(hexToAscii->isChecked())
        file.write(QString(test3.toHex()).toLatin1());
    else
        file.write(temp.toLatin1());
    file.close();
    //qDebug()<<temp;
  //  qDebug()<<save_values<<"    gap   "<<update_graph->currentText().toInt();
   if(save_values>=update_graph->currentText().toInt() or (hexToAscii->isChecked()))
    {
        QFile tempfile(tempFile+"/.temp.CSV");
        tempfile.open(QIODevice::Append);
        if(hexToAscii->isChecked())
            tempfile.write(test3.toHex());
        else
            tempfile.write(buffer.toLatin1());
        if (new_line->isChecked()){
            tempfile.write("\n");
        }
        qDebug()<<"hex "<<QString(test3.toHex()).toLatin1();

        tempfile.close();
        buffer.clear();
        save_values=0;
        QString test5;
        if(!filter_ckeckbox->isChecked())
        {
            test5  = "cat " + tempFile+"/.temp.CSV"+QString("|")+ tempFile +"/.filter.sh "+ tempFile;
        }
        else
        {
            test5  = "cat " + tempFile+"/.temp.CSV"+QString("|")+ filterpath + tempFile;
        }

        filter->start("/bin/bash",QStringList()<<"-c"<<test5);
        filter->waitForFinished();
        //tempfile.remove();

    }
}

}

void serialComm::tx_serial_exe(QString x)
{
    static bool warnned =  false;
   if(port != NULL){
    if(port->isOpen() )
     {
        if(!hexToAscii->isChecked())
        {
            port->write(x.toLatin1());
            if(!new_line->isChecked())
            {
                port->write("\n");
                port->write("\r");
            }
            warnned = false;
        }
        else
        {
            port->write(QByteArray::fromHex(x.toLatin1()));
            warnned = false;

        }
        port->flush();
    }
    else {
       if(warnned==false)
       {
        QMessageBox::warning(this,"Warning","Port is not open");
        warnned = true;
       }
      // qDebug()<<"from hex"<<QByteArray::fromHex(x.toLatin1());
    }

    }
   else if(warnned==false)
   {
       warnned = true;
       QMessageBox::warning(this,"Warning","Port is not open:\nPlease connect or close it and re-open terminal ");

   }
   //qDebug()<<"from hex"<<QByteArray::fromHex(x.toLatin1()).size();

   // qDebug()<<x.toLatin1()<<"in serial";
}


void serialComm::compare_match(QString received,QString time_out,QString send,int x,bool y)
{

    if(receivedList.count()==0)
    {
        receivedList.append(received);
        TimerList.append(time_out);
        SendList.append(send);
        checkList[receivedList.count()-1] = y;
        checkNumber[receivedList.count()-1]=x;
    }
    else
    {
        for(int i=0;i<receivedList.count();i++)
        {
            if(x==checkNumber[i])
            {
                receivedList.replace(i,received);
                TimerList.replace(i,time_out);
                SendList.replace(i,send);
                checkList[i] = y;
                checkNumber[i]=x;
            }
        }


    }

}

void serialComm::timeoutAnswer()
{
    if(port!=NULL)
    {
        if(port->isOpen()){
            port->write(SendList.at(reply_count).toLatin1());
            if(!new_line->isChecked())
            {
                port->write("\n");
                port->write("\r");
            }
        }

    }
}

void serialComm::save_parameter()
{
    emit save_parameter_data(profiles->currentText());
}

void serialComm::get_parameter()
{
        emit get_parameter_data(profiles->currentText());
}

void serialComm::hex_mode_toggle(bool enable)
{

}


