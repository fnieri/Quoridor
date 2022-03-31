//
// Created by louis on 3/30/22.
//

#pragma once
#include <iostream>

#include <QBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTabWidget>
#include <QTimer>
#include <QToolBox>
#include <QWidget>
#include <QHoverEvent>
#include <QRadioButton>
#include <QButtonGroup>

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
    void handleBoardMove(int x, int y);

private slots:
    void handleLoginButtonClicked(const std::string &username, const std::string &password);
    void handleRegisterButtonClicked(const std::string &username, const std::string &password, const std::string &repeatPassword);
    void handlePawnButtonClicked();
    void handleWallButtonClicked();

private:
    Ui::QtVue *ui;
    QStackedWidget *stackWidget;

    QTabWidget *loginTabBar;
    QLabel *loginMessage {};
    QLabel *registerMessage {};

    QTabWidget *mainTabBar;

    QLabel *userEloLabel {};
    QBoxLayout *leaderboardLayout {};

    int cellSize = 35;
    DrawLabel *drawLabel {};
    QPixmap *canvasPixmap {};
    QPainter *painter {};

    MainController mainController;
    MainModel *mainModel;
    ServerController *serverController;
    GameModel *gameModel;

    int player = -1, correctMove = 10, incorrectMove = -10;
    const int *playerTurn;
    std::vector<std::vector<int>> boardIntMatrix;
    std::vector<std::vector<int>> boardMoveIntMatrix;

    void createLoginAndRegister();
    void createMainPage();
    void createGamePage();
    void createFriendsPage();
    void createLeaderboardPage();
    void createTrainingPage();

    void drawBoard();
    Point getCellCoordinates(int x, int y) const;

    void updateValues();
};

class DrawLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DrawLabel(QWidget *parent = nullptr, QtVue *vue = nullptr);

private:
    QtVue *vue;

    bool event(QEvent *e) override;

    void mousePressEvent(QMouseEvent *event) override;
    void hoverMoveEvent(QHoverEvent *event);
};