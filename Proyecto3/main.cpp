#include "ZipReader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ZipReader w;
    w.show();
      return a.exec();
}
