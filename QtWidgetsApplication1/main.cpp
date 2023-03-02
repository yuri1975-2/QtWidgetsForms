#include "MainForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainForm w;
    w.show();
    auto retValue(a.exec());
    qDebug() << "end of program";
    return retValue;
}
