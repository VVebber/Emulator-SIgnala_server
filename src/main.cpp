#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  qRegisterMetaType<qintptr>("qintptr");
  MainWindow w;
  QObject::connect(&a, &QApplication::aboutToQuit, &w, &MainWindow::closeMainWindow);

  w.show();
  return a.exec();
}
