//
// Created by louis on 3/30/22.
//

#pragma once
#include <iostream>

#include <QCheckBox>
#include <QLabel>
#include <QTabWidget>
#include <QToolBox>
#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>

#include "MainModel.h"
#include "ServerController.h"
#include "src/common/Message.h"
#include "src/common/Point.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class QtVue;
}
QT_END_NAMESPACE

class QtVue : public QWidget
{
    Q_OBJECT

public:
    explicit QtVue(QWidget *parent = nullptr);
    ~QtVue() override;

private slots:
    void handleLoginButtonClicked(const std::string &username, const std::string &password);
    void handleRegisterButtonClicked(const std::string &username, const std::string &password, const std::string &repeatPassword);

private:
    Ui::QtVue *ui;
    QStackedWidget *stackWidget;

    QTabWidget *loginTabBar;
    QLabel *loginMessage{};
    QLabel *registerMessage{};

    QTabWidget *mainTabBar;

    MainController mainController;
    MainModel *mainModel;
    GameModel *gameModel;
    ServerController *serverController;

    void createLoginAndRegister();
    void createMainPage();
    void createGamePage();
    void createFriendsPage();
    void createLeaderboardPage();
};
