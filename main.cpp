#include "firstpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FirstPage w;
    w.show();
    return a.exec();
}
