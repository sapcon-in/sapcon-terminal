#include "mainwindow.h"
#include <QApplication>

#define APP_NAME "Sapcon Terminal"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationDomain("sapcon.in");
    a.setOrganizationName("Sapcon Instruments Pvt. Ltd.");
    a.setApplicationName(APP_NAME);
    QPixmap pixmap = QPixmap(":/new/prefix1/LOGO.png");
    MainWindow w;
     w.setWindowIcon(pixmap);
    w.show();    
    return a.exec();
}
