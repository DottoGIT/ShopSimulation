#include "mainwindow.h"

#include <QApplication>
#include <memory>
#include "shop.h"
#include "loggerWindow.h"
#include "logger.h"

int main(int argc, char *argv[])
{
    Logger::Info("<mian.cpp> Program rozpoczal sie");
    QApplication a(argc, argv);
    auto shop = std::make_unique<Shop>();
    MainWindow w(shop.get());
    LoggerWindow loggerWindow;
    w.show();
    loggerWindow.show();
    return a.exec();
}
