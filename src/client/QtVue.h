
#pragma once


#include "MainModel.h"
#include "ServerController.h"

#include <QApplication>
#include <QScopedPointer>

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class QtVue
{
    MainController mainController;
    MainModel *mainModel = mainController.getMainModel();
    ServerController *serverController = new ServerController {&mainController};

    QScopedPointer<QApplication> app;

    /* === Register Window === */
    QWidget *registerMainWidget;
    QHBoxLayout *horizontalLayout_r1;
    QGroupBox *registerGroupBox;
    QVBoxLayout *verticalLayout_r1;
    QWidget *usernameVBoxRegister;
    QVBoxLayout *verticalLayout_r2;
    QLabel *usernameLabelRegister;
    QLineEdit *usernameLineEditRegister;
    QWidget *passwordVBoxRegister;
    QVBoxLayout *verticalLayout_r3;
    QLabel *passwordLabelRegister;
    QLineEdit *passwordLineEditRegister;
    QWidget *confirmPassVBox;
    QVBoxLayout *verticalLayout_r4;
    QLabel *confirmPasswordLabel;
    QLineEdit *confirmPasswordLineEdit;
    QPushButton *registerButton;

    void setupRegisterUI();

    /* === Login Window === */
    QWidget *loginMainWidget;
    QHBoxLayout *horizontalLayout_l1;
    QGroupBox *loginGroupBox;
    QVBoxLayout *verticalLayout_l1;
    QWidget *usernameVBoxLogin;
    QVBoxLayout *verticalLayout_l2;
    QLabel *usernameLabelLogin;
    QLineEdit *usernameLineEditLogin;
    QWidget *passwordVBoxLogin;
    QVBoxLayout *verticalLayout_l3;
    QLabel *passwordLabelLogin;
    QLineEdit *passwordLineEditLogin;
    QPushButton *loginButton;
    QLabel *registerLabel;
    QPushButton *registerButtonLogin;

    void setupLoginUI();

    /* === Game Window === */
    void setupGameUI();

public:
    QtVue(int argc, char *argv[]);
    ~QtVue();

    int run();
};
