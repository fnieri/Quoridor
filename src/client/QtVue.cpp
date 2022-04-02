//
// Created by louis on 3/30/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QtVue.h" resolved

#include "QtVue.h"
#include "ui_QtVue.h"

DrawLabel::DrawLabel(QWidget *parent, QtVue *vue)
    : QLabel(parent)
    , vue(vue)
{
    this->setAttribute(Qt::WA_Hover, true);
}

void DrawLabel::mousePressEvent(QMouseEvent *event)
{
    QLabel::mousePressEvent(event);
    vue->handleBoardPress(event->x(), event->y());
}

void DrawLabel::hoverMoveEvent(QHoverEvent *event)
{
    vue->handleBoardMove(event->pos().x(), event->pos().y());
}

bool DrawLabel::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::HoverMove: {
        hoverMoveEvent(dynamic_cast<QHoverEvent *>(e));
        return true;
    }
    default:
        break;
    }
    return QLabel::event(e);
}

QtVue::QtVue(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QtVue)
{
    ui->setupUi(this);

    mainModel = mainController.getMainModel();
    mainModel->registerObserver(this);

    gameModel = mainModel->getCurrentGame();
    serverController = new ServerController {&mainController};

    stackWidget = new QStackedWidget(this);
    stackWidget->setStyleSheet(QLatin1String("QPushButton {\n" // https://gist.github.com/espdev/4f1565b18497a42d317cdf2531b7ef05 the great majority of that
                                                               // styleSheet comes from the git user : "espdev"
                                             "color: rgb(255, 255, 255);\n"
                                             "background-color: rgb(8, 76, 102);\n"
                                             "border-radius: 3px;\n"
                                             "border:none;\n"
                                             "border-bottom:3px solid rgb(0,0,0);\n"
                                             "}\n"
                                             "\n"
                                             "QPushButton:hover {\n"
                                             "background-color: rgb(20, 125, 164);\n"
                                             "border-bottom:1px solid rgb(0,0,0);\n"
                                             "}\n"
                                             "\n"
                                             "QPushButton:focus {\n"
                                             "border-bottom:none;\n"
                                             "border-top:2px solid rgb(0,0,0);\n"
                                             "border-left:1px solid rgb(0,0,0);\n"
                                             "border-right:1px solid rgb(0,0,0);\n"
                                             "background-color: rgb(18, 111, 145);\n"
                                             "}\n"
                                             "\n"
                                             "\n"
                                             "QPushButton:pressed {\n"
                                             "background-color: rgb(18, 111, 160);\n"
                                             "border-top:3px solid rgb(0,0,0);\n"
                                             "}\n"
                                             "QTabWidget::pane {\n"
                                             "    border: 1px solid black;\n"
                                             "    background: white;\n"
                                             "}\n"
                                             "\n"
                                             "QTabWidget::tab-bar:top {\n"
                                             "    top: 1px;\n"
                                             "}\n"
                                             "\n"
                                             "QTabWidget::tab-bar:bottom {\n"
                                             "    bottom: 1px;\n"
                                             "}\n"
                                             "\n"
                                             "QTabWidget::tab-bar:left {\n"
                                             "    right: 1px;\n"
                                             "}\n"
                                             "\n"
                                             "QTabWidget::tab-bar:right {\n"
                                             "    left: 1px;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab {\n"
                                             "    border: 1px solid black;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:selected {\n"
                                             "    background: white;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:!selected {\n"
                                             "    background: silver;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:!selected:hover {\n"
                                             "    background: #999;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:top:!selected {\n"
                                             "    margin-top: 3px;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:bottom:!selected {\n"
                                             "    margin-bottom: 3px;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:top, QTabBar::tab:bottom {\n"
                                             "    min-width: 8ex;\n"
                                             "    margin-right: -1px;\n"
                                             "    padding: 5px 10px 5px 10px;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:top:selected {\n"
                                             "    border-bottom-color: none;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:bottom:selected {\n"
                                             "    border-top"
                                             "-color: none;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:top:last, QTabBar::tab:bottom:last,\n"
                                             "QTabBar::tab:top:only-one, QTabBar::tab:bottom:only-one {\n"
                                             "    margin-right: 0;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:left:!selected {\n"
                                             "    margin-right: 3px;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:right:!selected {\n"
                                             "    margin-left: 3px;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:left, QTabBar::tab:right {\n"
                                             "    min-height: 8ex;\n"
                                             "    margin-bottom: -1px;\n"
                                             "    padding: 10px 5px 10px 5px;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:left:selected {\n"
                                             "    border-left-color: none;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:right:selected {\n"
                                             "    border-right-color: none;\n"
                                             "}\n"
                                             "\n"
                                             "QTabBar::tab:left:last, QTabBar::tab:right:last,\n"
                                             "QTabBar::tab:left:only-one, QTabBar::tab:right:only-one {\n"
                                             "    margin-bottom: 0;\n"
                                             "}"));
    stackWidget->setGeometry(0, 0, this->width(), this->height());

    loginTabBar = new QTabWidget(this);
    createLoginAndRegister();
    mainTabBar = new QTabWidget(this);
    connect(mainTabBar, &QTabWidget::tabBarClicked, this, &QtVue::updateNotifications);
}

QtVue::~QtVue()
{
    delete ui;
}

void QtVue::handleLoginButtonClicked(const std::string &username, const std::string &password)
{
    if (!serverController->login(username, password)) {
        loginMessage->setText("Wrong username or password");
    } else {
        serverController->fetchData();
        loginMessage->setText("Successfully logged in");
        createMainPage();
        stackWidget->removeWidget(loginTabBar);
    }
}

void QtVue::handleRegisterButtonClicked(const std::string &username, const std::string &password, const std::string &repeatPassword)
{
    if (password == repeatPassword && !username.empty() && !password.empty()) {
        if (serverController->registerUser(username, password)) {
            registerMessage->setText("Successfully registered. You can now log in.");
        } else {
            registerMessage->setText("Error creating account. Username probably already exists");
        }
    } else {
        registerMessage->setText("Passwords don't match or username is empty");
    }
}

void QtVue::createLoginAndRegister()
{
    auto loginBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    auto registerBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto loginTextEntry = new QLineEdit(this);
    loginTextEntry->setMinimumSize(QSize(311, 31));
    loginTextEntry->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"));
    loginTextEntry->setPlaceholderText("Username");
    loginBoxLayout->addWidget(loginTextEntry);

    auto passwordTextEntry = new QLineEdit(this);
    passwordTextEntry->setMinimumSize(QSize(311, 31));
    passwordTextEntry->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"));
    passwordTextEntry->setPlaceholderText("Password");
    passwordTextEntry->setEchoMode(QLineEdit::Password);
    loginBoxLayout->addWidget(passwordTextEntry);

    loginMessage = new QLabel("");
    loginMessage->setAlignment(Qt::AlignTop);
    loginBoxLayout->addWidget(loginMessage);

    auto loginButton = new QPushButton("Login", this);
    loginButton->setAutoDefault(true);
    loginButton->setMinimumSize(QSize(311, 31));
    connect(loginButton, &QPushButton::clicked, this, [this, loginTextEntry, passwordTextEntry]() {
        handleLoginButtonClicked(loginTextEntry->text().toStdString(), passwordTextEntry->text().toStdString());
    });
    loginBoxLayout->addWidget(loginButton);

    auto registerUsernameTextEntry = new QLineEdit(this);
    registerUsernameTextEntry->setMinimumSize(QSize(311, 31));
    registerUsernameTextEntry->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"));
    registerUsernameTextEntry->setPlaceholderText("Username");
    registerBoxLayout->addWidget(registerUsernameTextEntry);

    auto registerPasswordTextEntry = new QLineEdit(this);
    registerPasswordTextEntry->setMinimumSize(QSize(311, 31));
    registerPasswordTextEntry->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"));
    registerPasswordTextEntry->setPlaceholderText("Password");
    registerPasswordTextEntry->setEchoMode(QLineEdit::Password);
    registerBoxLayout->addWidget(registerPasswordTextEntry);

    auto registerPasswordConfirmTextEntry = new QLineEdit(this);
    registerPasswordConfirmTextEntry->setMinimumSize(QSize(311, 31));
    registerPasswordConfirmTextEntry->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"));
    registerPasswordConfirmTextEntry->setPlaceholderText("Confirm password");
    registerPasswordConfirmTextEntry->setEchoMode(QLineEdit::Password);
    registerBoxLayout->addWidget(registerPasswordConfirmTextEntry);

    registerMessage = new QLabel("");
    registerMessage->setAlignment(Qt::AlignTop);
    registerBoxLayout->addWidget(registerMessage);

    auto registerButton = new QPushButton("Register", this);
    registerButton->setMinimumSize(QSize(311, 31));
    connect(registerButton, &QPushButton::clicked, this, [this, registerUsernameTextEntry, registerPasswordTextEntry, registerPasswordConfirmTextEntry]() {
        handleRegisterButtonClicked(registerUsernameTextEntry->text().toStdString(), registerPasswordTextEntry->text().toStdString(),
            registerPasswordConfirmTextEntry->text().toStdString());
    });
    registerBoxLayout->addWidget(registerButton);

    auto loginBox = new QWidget(this);
    loginBoxLayout->setAlignment(Qt::AlignTop);
    loginBox->setLayout(loginBoxLayout);

    auto registerBox = new QWidget(this);
    registerBoxLayout->setAlignment(Qt::AlignTop);
    registerBox->setLayout(registerBoxLayout);

    loginTabBar->addTab(loginBox, "Login");
    loginTabBar->addTab(registerBox, "Register");
    createTrainingPage();

    stackWidget->addWidget(loginTabBar);
}

void QtVue::createGamePage()
{
    quitButton = new QPushButton("Exit to main menu", this);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(handleQuitGameButtonClicked()));
    surrenderButton = new QPushButton("Surrender", this);
    surrenderButton->setVisible(false);
    connect(surrenderButton, SIGNAL(clicked()), this, SLOT(handleSurrenderButtonClicked()));
    gameChatHistLW = new QListWidget {};

    auto gamePickerLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto pickJoinGameLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    auto joinGameTitle = new QLabel("Pick a game to join");
    joinGameTitle->setStyleSheet("QLabel { font-weight: bold; }");
    pickJoinGameLayout->addWidget(joinGameTitle, 0, Qt::AlignTop);

    auto joinGameLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    joinGameLayout->setAlignment(Qt::AlignTop);
    auto joinGameScrollArea = new QScrollArea(this);
    gameIdsScroll = new QStackedWidget(this);
    joinGameLayout->addWidget(new QLabel("Loading games..."));
    auto pickGameWidget = new QWidget(this);
    pickGameWidget->setLayout(joinGameLayout);
    gameIdsScroll->addWidget(pickGameWidget);
    gameIdsScroll->setMinimumSize(500, 300);
    joinGameScrollArea->setWidget(gameIdsScroll);
    pickJoinGameLayout->addWidget(joinGameScrollArea);

    auto joinGameWidget = new QFrame(this);
    joinGameWidget->setFrameShape(QFrame::Box);
    joinGameWidget->setLayout(pickJoinGameLayout);
    gamePickerLayout->addWidget(joinGameWidget);

    auto createGameLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto createGameTitle = new QLabel("Create a game");
    createGameTitle->setStyleSheet("QLabel { font-weight: bold; }");
    createGameLayout->addWidget(createGameTitle, 0, Qt::AlignTop);

    auto pickFriendsLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    pickFriendsLayout->setAlignment(Qt::AlignTop);
    auto pickFriendsScrollArea = new QScrollArea(this);
    createGameScroll = new QStackedWidget(this);
    pickFriendsLayout->addWidget(new QLabel("Loading friends..."));
    auto pickFriendsWidget = new QWidget(this);
    pickFriendsWidget->setLayout(pickFriendsLayout);
    createGameScroll->addWidget(pickFriendsWidget);
    createGameScroll->setMinimumSize(500, 300);
    pickFriendsScrollArea->setWidget(createGameScroll);
    createGameLayout->addWidget(pickFriendsScrollArea);

    auto createGameButton = new QPushButton("Invite friends and create game");
    connect(createGameButton, SIGNAL(clicked()), this, SLOT(handleCreateGameButtonClicked()));
    createGameLayout->addWidget(createGameButton);
    createGameLayout->setGeometry(QRect(0, 0, 100, 100));

    auto createGameWidget = new QFrame(this);
    createGameWidget->setFrameShape(QFrame::Box);
    createGameWidget->setLayout(createGameLayout);
    gamePickerLayout->addWidget(createGameWidget);

    auto gamePage = new QWidget(this);
    gamePickerLayout->setAlignment(Qt::AlignTop);
    gamePage->setLayout(gamePickerLayout);
    gameStack = new QStackedWidget(this);
    gameStack->addWidget(gamePage);

    mainTabBar->addTab(gameStack, "Games");
}

void QtVue::createFriendsPage()
{
    auto friendsPageLayout = new QHBoxLayout {};
    friendsPageLayout->setSpacing(0);

    auto titleFont = QFont {};
    titleFont.setBold(true);

    auto getTitle = [titleFont](const std::string &title) {
        auto label = new QLabel {QString::fromStdString(title)};
        label->setAlignment(Qt::AlignHCenter);
        label->setFont(titleFont);
        return label;
    };

    // Friend list
    auto friendListW = new QWidget {};
    friendListW->setMaximumWidth(200);
    auto friendListL = new QVBoxLayout {};

    auto friendListTitle = getTitle("Friend list");
    friendListL->addWidget(friendListTitle);

    friendListLW = new QListWidget {};
    auto friendListLWAction = [this]() {
        auto userItem = friendListLW->currentItem();
        if (userItem) {
            auto user = userItem->text().toStdString();
            serverController->fetchFriendMessages(*mainModel->getUsername(), user);
            updateChats();
        }
    };
    connect(friendListLW, &QListWidget::itemClicked, this, friendListLWAction);
    friendListL->addWidget(friendListLW);

    auto remFriendButton = new QPushButton {"Remove friend"};
    auto remFriendAction = [this]() {
        auto userItem = friendListLW->currentItem();
        if (userItem) {
            auto user = userItem->text().toStdString();
            serverController->removeFriend(*mainModel->getUsername(), user);
            serverController->fetchFriends();
        }
    };
    connect(remFriendButton, &QPushButton::clicked, this, remFriendAction);
    friendListL->addWidget(remFriendButton);

    friendListW->setLayout(friendListL);
    friendsPageLayout->addWidget(friendListW);

    // Central chat
    auto chatW = new QWidget {};
    auto chatL = new QVBoxLayout {};

    chatHistLW = new QListWidget {};
    /* chatHistLW->setWordWrap(true); */
    chatL->addWidget(chatHistLW);

    auto messageLE = new QLineEdit {};
    messageLE->setPlaceholderText("Aa");
    auto messageLEAction = [this, messageLE]() {
        auto receiverItem = friendListLW->currentItem();
        if (receiverItem) {
            auto receiver = receiverItem->text().toStdString();
            auto text = messageLE->text().toStdString();
            messageLE->clear();
            if (!text.empty()) {
                serverController->sendFriendMessage(*mainModel->getUsername(), receiver, text);
                serverController->fetchFriendMessages(*mainModel->getUsername(), receiver);
            }
        }
    };
    connect(messageLE, &QLineEdit::returnPressed, this, messageLEAction);
    chatL->addWidget(messageLE);

    chatW->setLayout(chatL);
    friendsPageLayout->addWidget(chatW);

    // Right hand side friends actions (FA)
    auto FAWidget = new QWidget {};
    FAWidget->setMaximumWidth(200);
    auto FALayout = new QVBoxLayout {};

    auto FARecTitle = getTitle("Invitations received");
    FALayout->addWidget(FARecTitle);

    friendInvLW = new QListWidget {};
    FALayout->addWidget(friendInvLW);

    // Decline and accept buttons
    auto invRespW = new QWidget {};
    auto invRespL = new QHBoxLayout {};

    auto decInvB = new QPushButton {"Decline"};
    auto decInvBAction = [this]() {
        auto userItem = friendInvLW->currentItem();
        if (userItem) {
            auto user = userItem->text().toStdString();
            serverController->declineFriendRequest(user, *mainModel->getUsername());
            serverController->fetchFriendRequestsReceived();
            serverController->fetchFriends();
        }
    };
    connect(decInvB, &QPushButton::clicked, this, decInvBAction);
    invRespL->addWidget(decInvB);

    auto accInvB = new QPushButton {"Accept"};
    auto accInvBAction = [this]() {
        auto userItem = friendInvLW->currentItem();
        if (userItem) {
            auto user = userItem->text().toStdString();
            serverController->acceptFriendRequest(user, *mainModel->getUsername());
            serverController->fetchFriendRequestsReceived();
            serverController->fetchFriends();
        }
    };
    connect(accInvB, &QPushButton::clicked, this, accInvBAction);
    invRespL->addWidget(accInvB);

    invRespW->setLayout(invRespL);
    FALayout->addWidget(invRespW);

    auto FASentTitle = getTitle("Invitations sent");
    FALayout->addWidget(FASentTitle);

    friendSentLW = new QListWidget {};
    FALayout->addWidget(friendSentLW);

    auto sendInvLE = new QLineEdit {};
    sendInvLE->setPlaceholderText("Aa");
    FALayout->addWidget(sendInvLE);

    auto sendInvB = new QPushButton {"Send invitation"};
    auto sendInvBAction = [this, sendInvLE]() {
        auto newFriend = sendInvLE->text().toStdString();
        if (newFriend != *mainModel->getUsername()) {
            serverController->sendFriendRequest(*mainModel->getUsername(), newFriend);
            serverController->fetchFriendRequestsSent();
        }
        sendInvLE->clear();
    };
    connect(sendInvB, &QPushButton::clicked, this, sendInvBAction);
    FALayout->addWidget(sendInvB);

    FAWidget->setLayout(FALayout);
    friendsPageLayout->addWidget(FAWidget);

    // Tab page
    auto friendsPage = new QWidget(this);
    friendsPage->setLayout(friendsPageLayout);

    mainTabBar->addTab(friendsPage, "Friends");
}

void QtVue::createLeaderboardPage()
{
    auto leaderboardPageLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    leaderboardLayout = new QTableWidget(10, 2, this);
    leaderboardLayout->setHorizontalHeaderLabels({"Username", "ELO"});
    leaderboardLayout->setEditTriggers(QAbstractItemView::NoEditTriggers);
    leaderboardPageLayout->addWidget(leaderboardLayout);

    auto eloWidget = new QWidget {};
    auto eloLayout = new QHBoxLayout {eloWidget};

    auto preELOText = new QLabel("Your current ELO: ");

    auto userEloFont = QFont {};
    userEloFont.setBold(true);

    userEloLabel = new QLabel("");
    userEloLabel->setFont(userEloFont);

    eloLayout->addWidget(preELOText);
    eloLayout->addWidget(userEloLabel);
    eloLayout->addStretch();

    leaderboardPageLayout->addWidget(eloWidget);

    auto refreshButton = new QPushButton {"Refresh"};
    connect(refreshButton, &QPushButton::clicked, this, [&]() {
        serverController->fetchLeaderboard();
        serverController->fetchElo();
    });
    leaderboardPageLayout->addWidget(refreshButton);

    auto leaderboardPage = new QWidget(this);
    leaderboardPage->setLayout(leaderboardPageLayout);

    mainTabBar->addTab(leaderboardPage, "Leaderboard");
}

void QtVue::createBoardChat(QBoxLayout *layout)
{
    // Central chat
    auto chatW = new QWidget {};
    auto chatL = new QVBoxLayout {};

    gameChatHistLW = new QListWidget {};
    chatL->addWidget(gameChatHistLW);

    auto messageLE = new QLineEdit {};
    messageLE->setPlaceholderText("Aa");
    auto messageLEAction = [this, messageLE]() {
        auto text = messageLE->text().toStdString();
        if (!text.empty()) {
            std::vector<std::string> playersInGame = gameModel->getPlayersNames();
            serverController->sendGameMessage(*mainModel->getUsername(), playersInGame, text, currentGameId);
            serverController->fetchGameMessages(currentGameId);
        }
        messageLE->clear();
    };
    connect(messageLE, &QLineEdit::returnPressed, this, messageLEAction);
    chatL->addWidget(messageLE);

    chatW->setLayout(chatL);
    layout->addWidget(chatW);
}

void QtVue::drawBoard()
{
    gameModel = mainModel->getCurrentGame();
    canvasPixmap->fill(Qt::white);
    if (mainModel->isInGame() && gameModel) {
        if (gameModel->hasWinner()) {
            painter->drawText(QRect(0, 0, 300, 100), "Player: " + QString::fromStdString(gameModel->getWinner()) + " has won!");
            selectHorizontalWall->setVisible(false);
            selectVerticalWall->setVisible(false);
            selectPawnMove->setVisible(false);
            selectWallMove->setVisible(false);
            if (!isTrainingGame) {
                surrenderButton->setVisible(false);
                quitButton->setVisible(true);
            }
        } else {
            player = gameModel->getPlayerIdx(*mainModel->getUsername());
            playerTurn = gameModel->getCurrentPlayer();

            gameModel->updateBoardIntMatrix(boardIntMatrix, player);
            if (boardMoveIntMatrix.empty()) {
                boardMoveIntMatrix = boardIntMatrix;
            }

            const int freeCell = 0, playerOne = 1, playerTwo = 2, playerThree = 3, playerFour = 4, emptyQuoridor = 5, occupiedVerticalQuoridor = 6,
                      occupiedHorizontalQuoridor = 7;
            std::vector<Qt::GlobalColor> playerColors {Qt::cyan, Qt::yellow, Qt::blue, Qt::magenta};
            std::string remainingWallsText;
            auto remainingWallsMap = gameModel->getPlayersRemainingWalls();
            for (auto &[playerUsername, remainingWalls] : remainingWallsMap) {
                remainingWallsText += playerUsername + ": " + std::to_string(remainingWalls) + ", ";
            }

            painter->drawText(QRect(0, 650, 200, 100), "You are player: " + QString::fromStdString(std::to_string(player)));
            painter->drawText(QRect(0, 670, 200, 100), "Player's turn: " + QString::fromStdString(std::to_string(*playerTurn)));
            painter->drawText(QRect(0, 690, 500, 100),
                "Player: " + QString::fromStdString("Remaining walls: " + remainingWallsText.substr(0, remainingWallsText.size() - 2)));

            int dx = 10, dy = 10;
            Qt::GlobalColor cellColor;
            for (auto i = 0; i < boardIntMatrix.size(); i++) {
                for (auto j = 0; j < boardIntMatrix[i].size(); j++) {
                    int gridValue = boardIntMatrix[i][j];

                    switch (gridValue) {
                    case freeCell: {
                        // draw a free cell
                        cellColor = Qt::darkGray;
                        if (moveType == 0) {
                            if (boardMoveIntMatrix[i][j] == correctMove) {
                                cellColor = Qt::green;
                            } else if (boardMoveIntMatrix[i][j] == incorrectMove) {
                                cellColor = Qt::red;
                            }
                        }
                        painter->fillRect(dx, dy, cellSize, cellSize, cellColor);
                        break;
                    }

                    case emptyQuoridor: {
                        // don't draw anything otherwise
                        if (moveType == 1) {
                            if (boardMoveIntMatrix[i][j] == correctMove) {
                                cellColor = Qt::green;
                            } else if (boardMoveIntMatrix[i][j] == incorrectMove) {
                                cellColor = Qt::red;
                            } else {
                                cellColor = Qt::white;
                            }
                            if (wallOrientation == WallOrientation::Vertical && j % 2 == 1) {
                                painter->fillRect(dx + cellSize / 4, dy, cellSize / 2, cellSize, cellColor);
                            } else if (wallOrientation == WallOrientation::Horizontal && i % 2 == 1) {
                                painter->fillRect(dx, dy + cellSize / 4, cellSize, cellSize / 2, cellColor);
                            }
                        }
                        break;
                    }

                    case occupiedVerticalQuoridor: {
                        cellColor = Qt::darkRed;
                        painter->fillRect(dx + cellSize / 4, dy, cellSize / 2, cellSize, cellColor);
                        break;
                    }
                    case occupiedHorizontalQuoridor: {
                        cellColor = Qt::darkRed;
                        painter->fillRect(dx, dy + cellSize / 4, cellSize, cellSize / 2, cellColor);
                        break;
                    }

                    case playerOne:
                    case playerTwo:
                    case playerThree:
                    case playerFour:
                        // draw a player one cell
                        {
                            cellColor = playerColors[gridValue - 1];
                            painter->fillRect(dx, dy, cellSize, cellSize, cellColor);
                            break;
                        }

                    default:
                        break;
                    }

                    dx += cellSize;
                }
                dy += cellSize;
                dx = 10;
            }
            painter->setPen(QPen(Qt::black, 2));
            painter->drawRect(0, 0, cellSize * (int)boardIntMatrix.size() + 20, cellSize * (int)boardIntMatrix.size() + 20);
        }
    } else if (!isTrainingGame) {
        painter->drawText(QRect(0, 0, 500, 100), "Waiting for other players to join...");
    }
    drawLabel->setPixmap(*canvasPixmap);
}

void QtVue::createBoard(QBoxLayout *layout)
{
    canvasPixmap = new QPixmap(QSize(620, 740));
    painter = new QPainter(canvasPixmap);
    drawLabel = new DrawLabel(this, this);
    layout->addWidget(drawLabel);

    selectPawnMove = new QPushButton("Pawn");
    selectPawnMove->setMinimumSize(QSize(0, 31));
    selectWallMove = new QPushButton("Wall");
    selectWallMove->setMinimumSize(QSize(0, 31));
    selectHorizontalWall = new QPushButton("Horizontal");
    selectHorizontalWall->setMinimumSize(QSize(0, 31));
    selectVerticalWall = new QPushButton("Vertical");
    selectVerticalWall->setMinimumSize(QSize(0, 31));
    connect(selectPawnMove, SIGNAL(clicked()), this, SLOT(handlePawnButtonClicked()));
    connect(selectWallMove, SIGNAL(clicked()), this, SLOT(handleWallButtonClicked()));
    connect(selectHorizontalWall, SIGNAL(clicked()), this, SLOT(handleHorizontalWallButtonClicked()));
    connect(selectVerticalWall, SIGNAL(clicked()), this, SLOT(handleVerticalWallButtonClicked()));
    selectPawnMove->setCheckable(true);
    selectWallMove->setCheckable(true);
    selectHorizontalWall->setCheckable(true);
    selectVerticalWall->setCheckable(true);
    selectPawnMove->setChecked(true);
    selectHorizontalWall->setChecked(true);
    selectHorizontalWall->setVisible(false);
    selectVerticalWall->setVisible(false);
    selectPawnMove->setVisible(false);
    selectWallMove->setVisible(false);
    auto selectWallOrientationLayout = new QHBoxLayout;
    selectWallOrientationLayout->addWidget(selectHorizontalWall);
    selectWallOrientationLayout->addWidget(selectVerticalWall);
    layout->addLayout(selectWallOrientationLayout);

    auto selectPawnWallLayout = new QHBoxLayout;
    selectPawnWallLayout->addWidget(selectPawnMove);
    selectPawnWallLayout->addWidget(selectWallMove);
    layout->addLayout(selectPawnWallLayout);
}

void QtVue::createTrainingPage()
{
    auto trainingPageLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    createBoard(trainingPageLayout);

    auto trainingStartButton = new QPushButton("Start training with Jürgen the AI", this);
    trainingStartButton->setMinimumSize(QSize(311, 31));
    connect(trainingStartButton, &QPushButton::clicked, this, [this, trainingStartButton]() {
        isTrainingGame = true;
        mainModel->createAiGame();
        selectPawnMove->setVisible(true);
        selectWallMove->setVisible(true);
        trainingStartButton->setText("Restart");
        mainModel->setIsGameStarted(true);
        drawBoard();
    });

    trainingPageLayout->addWidget(trainingStartButton);

    auto trainingPage = new QWidget(this);
    trainingPage->setLayout(trainingPageLayout);

    loginTabBar->addTab(trainingPage, "Training");
}

void QtVue::updateValues()
{
    updateNotifications();
    updatePart(eloUpdated, [this]() { this->updateELO(); });
    updatePart(leaderboardUpdated, [this]() { this->updateLeaderboard(); });
    updatePart(relationsUpdated, [this]() { this->updateRelations(); });
    updatePart(chatsUpdated, [this]() { this->updateChats(); });
    updatePart(friendsUpdated, [this]() { this->updateFriends(); });
    updatePart(gameIdsUpdated, [this]() { this->updateGameIds(); });
    updatePart(gameUpdated, [this]() { this->updateGame(); });
    updatePart(gameChatUpdated, [this]() { this->updateGameChat(); });
}

template <typename Callable>
void QtVue::updatePart(std::atomic<bool> &toBeUpdated, Callable updateFunc)
{
    if (toBeUpdated) {
        updateFunc();
        toBeUpdated = false;
    }
}

void QtVue::update(QuoridorEvent event)
{
    switch (event) {
    case QuoridorEvent::EloModified:
        eloUpdated = true;
        break;
    case QuoridorEvent::LeaderboardModified:
        leaderboardUpdated = true;
        break;
    case QuoridorEvent::RelationsModified:
        relationsUpdated = true;
        break;
    case QuoridorEvent::ChatsModified:
        chatsUpdated = true;
        break;
    case QuoridorEvent::FriendsUpdated:
        friendsUpdated = true;
        break;
    case QuoridorEvent::GameIdsUpdated:
        gameIdsUpdated = true;
        break;
    case QuoridorEvent::GameUpdated:
        gameUpdated = true;
        break;
    case QuoridorEvent::GameChatUpdated:
        gameChatUpdated = true;
        break;
    default:
        break;
    }
}

void QtVue::updateELO()
{
    auto userElo = static_cast<int>(*mainModel->getELO());
    userEloLabel->setText(QString::fromStdString(std::to_string(userElo)));
}

void QtVue::updateLeaderboard()
{
    auto lb = mainModel->getLeaderboard();

    leaderboardLayout->setRowCount((int)lb->size());

    for (auto i = 0; i < lb->size(); ++i) {
        auto username = lb->at(i).first;
        auto elo = std::to_string(static_cast<int>(lb->at(i).second));

        auto usernameItem = new QTableWidgetItem {username.c_str()};
        usernameItem->setTextAlignment(Qt::AlignHCenter);
        auto eloItem = new QTableWidgetItem {elo.c_str()};
        eloItem->setTextAlignment(Qt::AlignHCenter);

        if (username == *mainModel->getUsername()) {
            auto font = QFont {};
            font.setBold(true);
            usernameItem->setFont(font);
            eloItem->setFont(font);
        }

        leaderboardLayout->setItem(i, 0, usernameItem);
        leaderboardLayout->setItem(i, 1, eloItem);
    }
}

void QtVue::updateFriends()
{
    if (mainModel->getHasFriends()) {
        pickFriendsList = new QList<QCheckBox *>;
        auto friendList = mainModel->getFriendList();
        auto friendListLayout = new QVBoxLayout;
        friendListLayout->setAlignment(Qt::AlignTop);
        for (auto &f : *friendList) {
            auto friendCheckbox = new QCheckBox(QString::fromStdString(f));
            pickFriendsList->append(friendCheckbox);
            friendListLayout->addWidget(friendCheckbox);
        }

        auto friendListWidget = new QWidget(this);
        friendListWidget->setLayout(friendListLayout);

        auto oldFriendListWidget = createGameScroll->currentWidget();
        createGameScroll->addWidget(friendListWidget);
        createGameScroll->removeWidget(oldFriendListWidget);
    } else {
        auto oldFriendListWidget = createGameScroll->currentWidget();
        createGameScroll->addWidget(new QLabel("No friends :("));
        createGameScroll->removeWidget(oldFriendListWidget);
    }
}

void QtVue::updateRelations()
{
    auto friendList = mainModel->getFriendList();
    auto friendInv = mainModel->getFriendRequestsReceived();
    auto friendSent = mainModel->getFriendRequestsSent();

    auto updateRel = [](QListWidget *w, const std::vector<std::string> *l) {
        w->clear();
        if (l) {
            for (auto &entry : *l) {
                w->addItem(QString::fromStdString(entry));
            }
        }
    };

    updateRel(friendListLW, friendList);
    updateRel(friendInvLW, friendInv);
    updateRel(friendSentLW, friendSent);
}

void QtVue::updateGame()
{
    quitButton->setVisible(false);
    selectPawnMove->setVisible(true);
    selectWallMove->setVisible(true);
    surrenderButton->setVisible(true);
    drawBoard();
}

void QtVue::updateGameIds()
{
    auto gameIds = mainModel->getGameIDs();
    auto gameIdsLayout = new QVBoxLayout;
    for (auto &i : *gameIds) {
        std::string friendsListStr;
        for (int j = 0; j < i.second.size() - 1; ++j) {
            friendsListStr += i.second[j] + ", ";
        }
        friendsListStr += i.second[i.second.size() - 1];
        std::string gameDescription = "Game ID: " + std::to_string(i.first) + "     " + friendsListStr;

        auto joinGameBtn = new QPushButton(QString::fromStdString(gameDescription));
        connect(joinGameBtn, &QPushButton::clicked, this, [&, i]() { handleJoinGameButtonClicked(i.first); });
        gameIdsLayout->addWidget(joinGameBtn);
    }

    auto gameIdsListWidget = new QWidget(this);
    gameIdsLayout->setAlignment(Qt::AlignTop);
    gameIdsListWidget->setLayout(gameIdsLayout);
    auto oldGameIdWidget = gameIdsScroll->currentWidget();
    gameIdsScroll->addWidget(gameIdsListWidget);
    gameIdsScroll->removeWidget(oldGameIdWidget);
}

void QtVue::updateChats()
{
    if (mainModel->getHasFriends()) {
        auto userItem = friendListLW->currentItem();
        if (userItem) {
            auto user = userItem->text().toStdString();
            /* serverController->fetchFriendMessages(*mainModel->getUsername(), user); */
            auto chat = mainModel->getChatWith(user);

            chatHistLW->clear();

            for (const auto &entry : *chat) {
                auto msg = entry.sender + ": " + entry.sentMessage;
                auto qmsg = QString::fromStdString(msg);
                /* auto qmsg = QString::fromStdString(entry.sentMessage); */
                /* auto listItem = new QListWidgetItem {qmsg}; */
                /* if (entry.sender == *mainModel->getUsername()) { */
                /*     listItem->setTextAlignment(Qt::AlignRight); */
                /* } */
                /* chatHistLW->addItem(listItem); */
                chatHistLW->addItem(qmsg);
            }
        }
    }
}

void QtVue::updateGameChat()
{
    if (mainModel->isInGame()) {
        auto gameChat = mainModel->getGameMessages();
        gameChatHistLW->clear();
        for (const auto &entry : *gameChat) {
            auto msg = entry.sender + ": " + entry.sentMessage;
            auto qmsg = QString::fromStdString(msg);
            gameChatHistLW->addItem(qmsg);
        }
    }
}

void QtVue::updateNotifications()
{
    auto currentTabIdx = mainTabBar->currentIndex();
    if (currentTabIdx == -1)
        return;

    /* std::cerr << currentTabIdx; */

    if (currentTabIdx != 1 && mainModel->hasFriendNotification()) {
        mainTabBar->setTabText(1, "Friends*");
    } else if (currentTabIdx == 1 && mainModel->hasFriendNotification()) {
        mainModel->setFriendNotification(false);
        mainTabBar->setTabText(1, "Friends");
    } else {
        mainTabBar->setTabText(1, "Friends");
    }

    if (currentTabIdx != 0 && mainModel->hasGameNotification()) {
        mainTabBar->setTabText(0, "Games*");
    } else if (currentTabIdx == 0 && mainModel->hasGameNotification()) {
        mainModel->setGameNotification(false);
        mainTabBar->setTabText(0, "Games");
    } else {
        mainTabBar->setTabText(0, "Games");
    }
}

void QtVue::createMainPage()
{
    createGamePage();
    createFriendsPage();
    createLeaderboardPage();

    serverController->fetchData();

    stackWidget->addWidget(mainTabBar);
    stackWidget->setCurrentWidget(mainTabBar);

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QtVue::updateValues);
    timer->start(1000);
}

Point QtVue::getCellCoordinates(int x, int y) const
{
    int i = (y - cellSize * 2) / cellSize;
    int j = (x - 10) / cellSize;
    return {j, i};
}

void QtVue::handleBoardPress(int x, int y)
{
    if (gameModel) {
        auto cellCoordinates = getCellCoordinates(x, y);
        if (moveType == 0) {
            if (gameModel->isMoveValid(cellCoordinates / 2, player) && *gameModel->getCurrentPlayer() == player) {
                auto playerAction = gameModel->getPlayerAction(cellCoordinates / 2, player);
                gameModel->processAction(playerAction.serialized().dump());
                if (!isTrainingGame)
                    serverController->playPlayerAction(playerAction, player);
            }
        } else if (moveType == 1) {
            if (gameModel->isWallValid(cellCoordinates / 2, wallOrientation, player) && *gameModel->getCurrentPlayer() == player) {
                auto wallAction = gameModel->getWallAction(cellCoordinates / 2, wallOrientation, player);
                gameModel->processAction(wallAction.serialized().dump());
                if (!isTrainingGame)
                    serverController->playWallAction(wallAction, player);
            }
        }
        drawBoard();
    }
}

void QtVue::handleBoardMove(int x, int y)
{
    if (gameModel) {
        if (gameUpdated)
            updateValues();

        auto cellCoordinates = getCellCoordinates(x, y);
        boardMoveIntMatrix = boardIntMatrix;
        try {
            if (moveType == 0) {
                if (*gameModel->getCurrentPlayer() == player && gameModel->isMoveValid(cellCoordinates / 2, player)) {
                    boardMoveIntMatrix.at(cellCoordinates.y()).at(cellCoordinates.x()) = correctMove;
                } else {
                    boardMoveIntMatrix.at(cellCoordinates.y()).at(cellCoordinates.x()) = incorrectMove;
                }
            } else if (moveType == 1) {
                if (*gameModel->getCurrentPlayer() == player && gameModel->isWallValid(cellCoordinates / 2, wallOrientation, player)) {
                    int dx = wallOrientation == WallOrientation::Horizontal ? 1 : 0;
                    int dy = wallOrientation == WallOrientation::Vertical ? 1 : 0;
                    boardMoveIntMatrix.at(cellCoordinates.y()).at(cellCoordinates.x()) = correctMove;
                    boardMoveIntMatrix.at(cellCoordinates.y() + dy).at(cellCoordinates.x() + dx) = correctMove;
                    boardMoveIntMatrix.at(cellCoordinates.y() + dy * 2).at(cellCoordinates.x() + dx * 2) = correctMove;
                } else {
                    boardMoveIntMatrix.at(cellCoordinates.y()).at(cellCoordinates.x()) = incorrectMove;
                }
            }
            drawBoard();
        } catch (std::out_of_range &e) {
        }
    }
}

void QtVue::handlePawnButtonClicked()
{
    if (!selectPawnMove->isChecked()) {
        selectPawnMove->setChecked(true);
    }
    moveType = 0;
    selectHorizontalWall->setVisible(false);
    selectVerticalWall->setVisible(false);
    selectWallMove->setChecked(false);
}

void QtVue::handleWallButtonClicked()
{
    if (!selectWallMove->isChecked()) {
        selectWallMove->setChecked(true);
    }
    moveType = 1;
    selectHorizontalWall->setVisible(true);
    selectVerticalWall->setVisible(true);
    selectPawnMove->setChecked(false);
}

void QtVue::handleHorizontalWallButtonClicked()
{
    if (!selectHorizontalWall->isChecked()) {
        selectHorizontalWall->setChecked(true);
    }
    wallOrientation = WallOrientation::Horizontal;
    selectVerticalWall->setChecked(false);
}

void QtVue::handleVerticalWallButtonClicked()
{
    if (!selectVerticalWall->isChecked()) {
        selectVerticalWall->setChecked(true);
    }
    wallOrientation = WallOrientation::Vertical;
    selectHorizontalWall->setChecked(false);
}

void QtVue::handleCreateGameButtonClicked()
{
    std::vector<std::string> friendsPicked;
    for (auto &friendCheckbox : *pickFriendsList) {
        if (friendCheckbox->isChecked()) {
            friendsPicked.push_back(friendCheckbox->text().toStdString());
        }
    }
    if (friendsPicked.size() == 1 || friendsPicked.size() == 3) {
        serverController->createGame(*mainModel->getUsername(), friendsPicked);
    }
}

void QtVue::handleJoinGameButtonClicked(const int &gameId)
{
    isTrainingGame = false;
    currentGameId = gameId;
    gameChatHistLW->clear();
    mainModel->setIsGameStarted(false);
    serverController->joinGame(gameId, *mainModel->getUsername());

    auto boardLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    createBoard(boardLayout);
    boardLayout->addWidget(surrenderButton);
//    quitButton->setVisible(false);
    boardLayout->addWidget(quitButton);
    auto boardWidget = new QWidget(this);
    boardWidget->setLayout(boardLayout);

    auto layout = new QBoxLayout(QBoxLayout::LeftToRight);
    layout->addWidget(boardWidget);
    createBoardChat(layout);

    auto mainWidget = new QWidget(this);
    mainWidget->setLayout(layout);
    gameStack->addWidget(mainWidget);
    gameStack->setCurrentWidget(mainWidget);
    drawBoard();
}

void QtVue::handleQuitGameButtonClicked()
{
    gameStack->removeWidget(gameStack->currentWidget());
    serverController->fetchGameIds();
    if (gameModel && gameModel->hasWinner()) {
        serverController->fetchGameIds();
        mainModel->unloadGame();
        gameModel = nullptr;
    } else {
        serverController->quitGame(currentGameId, *mainModel->getUsername());
    }
}

void QtVue::handleSurrenderButtonClicked()
{
    serverController->surrend(*mainModel->getUsername());
    handleQuitGameButtonClicked();
}

bool QtVue::isConnectedToServer()
{
    return serverController->isConnected();
}
