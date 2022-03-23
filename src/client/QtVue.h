
#pragma once


#include "MainModel.h"
#include "ServerController.h"


// #include <QApplication>
// #include <QScopedPointer>

class QtVue
{
    MainController mainController;
    MainModel *mainModel = mainController.getMainModel();
    ServerController *serverController = new ServerController {&mainController};
    
    // QScopedPointer<QApplication> app;
    
public:
    QtVue(int argc, char *argv[]);
    ~QtVue();

    int run();
};
