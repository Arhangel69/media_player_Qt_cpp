#include "medpl_pr/mainwindow.hpp"
#include <QApplication>
#include <iostream>
#include <QSound>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    std::cout<<"Complete!\n";
    return a.exec();
}
