//
// Created by louis on 3/30/22.
//

#pragma once
#include <atomic>
#include <iostream>

#include <QBoxLayout>
#include <QButtonGroup>
#include <QCheckBox>
#include <QHoverEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QTimer>
#include <QToolBox>
#include <QWidget>
#include <QHoverEvent>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFrame>

#include "MainModel.h"
#include "ServerController.h"
#include "src/common/Message.h"
#include "src/common/Observer.h"
#include "src/common/Point.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class QtVue;
}
QT_END_NAMESPACE

class DrawLabel;

class QtVue : public QWidget, public Observer
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
    void handleHorizontalWallButtonClicked();
    void handleVerticalWallButtonClicked();

private:
    Ui::QtVue *ui;
    QStackedWidget *stackWidget;

    QTabWidget *loginTabBar;
    QLabel *loginMessage {};
    QLabel *registerMessage {};

    QTabWidget *mainTabBar;

    QBoxLayout *joinGameLayout;

    QLabel *userEloLabel {};
    QTableWidget *leaderboardLayout {};

    int cellSize = 35;
    DrawLabel *drawLabel {};
    QPixmap *canvasPixmap {};
    QPainter *painter {};

    MainController mainController;
    MainModel *mainModel;
    ServerController *serverController;
    GameModel *gameModel;

    QPushButton *selectPawnMove{};
    QPushButton *selectWallMove{};
    QPushButton *selectHorizontalWall{};
    QPushButton *selectVerticalWall{};
    int moveType = 0; // 0 = pawn, 1 = wall
    int player = -1, correctMove = 10, incorrectMove = -10;
    WallOrientation wallOrientation = WallOrientation::Horizontal;
    const int *playerTurn;
    std::vector<std::vector<int>> boardIntMatrix;
    std::vector<std::vector<int>> boardMoveIntMatrix;

    std::atomic<bool> eloUpdated {true};
    std::atomic<bool> leaderboardUpdated {false};
    std::atomic<bool> relationsUpdated {false};
    std::atomic<bool> chatsUpdated {false};

    void createLoginAndRegister();
    void createMainPage();
    void createGamePage();
    void createFriendsPage();
    void createLeaderboardPage();
    void createTrainingPage();

    void drawBoard();
    Point getCellCoordinates(int x, int y) const;

    void updateValues();
    void update(QuoridorEvent) override;

    template <typename Callable>
    void updatePart(std::atomic<bool> &toBeUpdated, Callable updateFunc);

    void updateELO();
    void updateLeaderboard();
    void updateRelations();
    void updateChats();
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
