#include <QApplication>

#include "Controller.hpp"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Controller controller;
  return app.exec();
}