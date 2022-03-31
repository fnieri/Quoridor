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
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>

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

class DrawLabel;

class QtVue : public QWidget
{
    Q_OBJECT

public:
    explicit QtVue(QWidget *parent = nullptr);
    ~QtVue() override;
    void handleBoardPress(int x, int y);

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

    QLabel *userEloLabel{};

    int cellSize = 35, corridorSize = 15;
    std::vector<std::vector<int>> testBoard{{0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {0, 0, 0, 0, 0, 0, 0, 0, 0}};
    DrawLabel *drawLabel{};
    QPixmap *canvasPixmap{};
    QPainter *painter{};

    MainController mainController;
    MainModel *mainModel;
    GameModel *gameModel;
    ServerController *serverController;

    void createLoginAndRegister();
    void createMainPage();
    void createGamePage();
    void createFriendsPage();
    void createLeaderboardPage();
    void createTrainingPage();

    void drawBoard();

    void updateValues();
};

class DrawLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DrawLabel(QWidget *parent = nullptr, QtVue *vue = nullptr);

private:
    QtVue *vue;

    void mousePressEvent(QMouseEvent *event) override;
    //    void mouseMoveEvent(QMouseEvent *event) override;
    //    void mouseReleaseEvent(QMouseEvent *event) override;
};