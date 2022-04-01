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
#include <QListWidget>
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

    void handleCreateGameButtonClicked();
    void handleJoinGameButtonClicked(const int &gameId);

private:
    Ui::QtVue *ui;
    QStackedWidget *stackWidget;

    QTabWidget *loginTabBar;
    QLabel *loginMessage {};
    QLabel *registerMessage {};

    QTabWidget *mainTabBar {};

    QStackedWidget *gameStack {};
    QStackedWidget *gameIdsScroll {};
    QStackedWidget *createGameScroll {};
    QList<QCheckBox *> *pickFriendsList {};

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

    bool isTrainingGame = false;
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
    std::atomic<bool> gameUpdated {false};
    std::atomic<bool> friendsUpdated {false};
    std::atomic<bool> gameIdsUpdated {false};
    std::atomic<bool> gameLoaded {false};

    // Friends
    QListWidget *friendListLW;
    QListWidget *chatHistLW;
    QListWidget *friendInvLW;
    QListWidget *friendSentLW;

    /**
     * @brief Creates the layout of Login And Register tabs
     * 
     */
    void createLoginAndRegister();

    /**
     * @brief Creates a Main Page object accessible by a logged in user
     * 
     */
    void createMainPage();

    /**
     * @brief Creates the layout of a Game Page, with joinable games from friends invitations and creation game interface
     * 
     */
    void createGamePage();

    /**
     * @brief Creates the layout of a Friends tab, with chat, friend requests and friends list
     * 
     */
    void createFriendsPage();

    /**
     * @brief Creates a Leaderboard Page object with top 10 players of the server shown
     * [@details also shows your rank]
     */
    void createLeaderboardPage();

    /**
     * @brief Creates a Board object, its graphic representation and action buttons
     * 
     * @param layout 
     */
    void createBoard(QBoxLayout *layout);

    /**
     * @brief Creates a Training Page object, with dedicated creation of the board to the user and AI
     * 
     */
    void createTrainingPage();

    /**
     * @brief Loads the board from the server mainModel and draws it in its state
     * 
     */
    void drawBoard();

    /**
     * @brief Get the Cell Coordinates object
     * 
     * @param x 
     * @param y 
     * @return Point 
     */
    Point getCellCoordinates(int x, int y) const;

    /**
     * @brief Updates all values responsively by fetching client's data with the server's
     * 
     */
    void updateValues();

    /**
     * @brief Function that calls updateNotifications() if any event modifies a notification value
     * 
     */
    void update(QuoridorEvent) override;

    template <typename Callable>
    /**
     * @brief Toggles the values of the notifications when called in updateValues
     * 
     * @param toBeUpdated 
     * @param updateFunc 
     */
    void updatePart(std::atomic<bool> &toBeUpdated, Callable updateFunc);

    /**
     * @brief Updates user's elo from fetched data from the server
     * 
     */
    void updateELO();

    /**
     * @brief Updates and Draws the leaderboard shown in the "LeaderBboard" tab
     * 
     */
    void updateLeaderboard();

    /**
     * @brief Fetches from server and displays all friends related requests
     * 
     */
    void updateRelations();

    /**
     * @brief Calls updateChatEntries()
     * 
     */
    void updateChats();

    /**
     * @brief Fetches from server all chats and updates the displayed chat messages
     * 
     */
    void updateChatEntries();

    /**
     * @brief Updates the labels of tabs where a changement has been made and not yet seen by the user
     * [@details puts the "*" symbol in the tab to display the notification]
     */
    void updateNotifications();

    /**
     * @brief Fetches from server all friends you have in your friends list in order to display in the "Friends" tab
     * 
     */
    void updateFriends();

    /**
     * @brief Displays all joinable games you are invited to and handles the user connection process
     * 
     */
    void updateGameIds();

    /**
     * @brief Draws the board with updated values following a player's turn
     * 
     */
    void updateGame();
};

class DrawLabel : public QLabel
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Draw Label object containing the whole canva of the board
     * 
     * @param parent 
     * @param vue 
     */
    explicit DrawLabel(QWidget *parent = nullptr, QtVue *vue = nullptr);

private:
    QtVue *vue;

    /**
     * @brief Represents events made on the board
     * 
     * @param e 
     * @return true 
     * @return false 
     */
    bool event(QEvent *e) override;

    /**
     * @brief Mouse press event listener, gets the position of the mouse on click
     * [@details gives the position of the mouse to a board click handler]
     * @param event 
     */
    void mousePressEvent(QMouseEvent *event) override;
    
    /**
     * @brief Hover event listener, gets the position of the mouse on hovering a board element
     * [@details gives the position of the mouse to a board hover handler]
     * @param event 
     */
    void hoverMoveEvent(QHoverEvent *event);
};
