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
    loginTextEntry->setPlaceholderText("Login");
    loginBoxLayout->addWidget(loginTextEntry);

    auto passwordTextEntry = new QLineEdit(this);
    passwordTextEntry->setPlaceholderText("Password");
    passwordTextEntry->setEchoMode(QLineEdit::Password);
    loginBoxLayout->addWidget(passwordTextEntry);

    loginMessage = new QLabel("");
    loginMessage->setAlignment(Qt::AlignTop);
    loginBoxLayout->addWidget(loginMessage);

    auto loginButton = new QPushButton("Login", this);
    connect(loginButton, &QPushButton::clicked, this, [this, loginTextEntry, passwordTextEntry]() {
        handleLoginButtonClicked(loginTextEntry->text().toStdString(), passwordTextEntry->text().toStdString());
    });
    loginBoxLayout->addWidget(loginButton);

    auto registerUsernameTextEntry = new QLineEdit(this);
    registerUsernameTextEntry->setPlaceholderText("Login");
    registerBoxLayout->addWidget(registerUsernameTextEntry);

    auto registerPasswordTextEntry = new QLineEdit(this);
    registerPasswordTextEntry->setPlaceholderText("Password");
    registerPasswordTextEntry->setEchoMode(QLineEdit::Password);
    registerBoxLayout->addWidget(registerPasswordTextEntry);

    auto registerPasswordConfirmTextEntry = new QLineEdit(this);
    registerPasswordConfirmTextEntry->setPlaceholderText("Confirm password");
    registerPasswordConfirmTextEntry->setEchoMode(QLineEdit::Password);
    registerBoxLayout->addWidget(registerPasswordConfirmTextEntry);

    registerMessage = new QLabel("");
    registerMessage->setAlignment(Qt::AlignTop);
    registerBoxLayout->addWidget(registerMessage);

    auto registerButton = new QPushButton("Register", this);
    connect(registerButton, &QPushButton::clicked, this, [this, registerUsernameTextEntry, registerPasswordTextEntry, registerPasswordConfirmTextEntry]() {
        handleRegisterButtonClicked(registerUsernameTextEntry->text().toStdString(), registerPasswordTextEntry->text().toStdString(),
            registerPasswordConfirmTextEntry->text().toStdString());
    });
    registerBoxLayout->addWidget(registerButton);

    auto loginBox = new QWidget(this);
    loginBox->setLayout(loginBoxLayout);

    auto registerBox = new QWidget(this);
    registerBox->setLayout(registerBoxLayout);

    createTrainingPage();

    loginTabBar->addTab(loginBox, "Login");
    loginTabBar->addTab(registerBox, "Register");

    stackWidget->addWidget(loginTabBar);
}

void QtVue::createGamePage()
{
    auto gamePickerLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto tLabel = new QLabel("Game page");
    gamePickerLayout->addWidget(tLabel);

    auto gamePage = new QWidget(this);
    gamePage->setLayout(gamePickerLayout);

    mainTabBar->addTab(gamePage, "Games");
}

void QtVue::createFriendsPage()
{
    auto friendsPageLayout = new QHBoxLayout {};

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
    auto friendListL = new QVBoxLayout {};

    auto friendListTitle = getTitle("Friend list");
    friendListL->addWidget(friendListTitle);

    friendListLW = new QListWidget {};
    connect(friendListLW, &QListWidget::itemClicked, this, &QtVue::updateChatEntries);
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
        serverController->sendFriendRequest(*mainModel->getUsername(), sendInvLE->text().toStdString());
        serverController->fetchFriendRequestsSent();
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

void QtVue::updateChatEntries()
{
    if (!mainModel->getFriendList()->empty()) {
        auto userItem = friendListLW->currentItem();
        if (userItem) {
            auto user = userItem->text().toStdString();
            serverController->fetchFriendMessages(*mainModel->getUsername(), user);
            auto chat = mainModel->getChatWith(user);

            chatHistLW->clear();

            for (const auto &entry : *chat) {
                auto msg = entry.sender + ": " + entry.sentMessage;
                auto qmsg = QString::fromStdString(msg);
                chatHistLW->addItem(qmsg);
            }
        }
    }
}

void QtVue::createLeaderboardPage()
{
    auto leaderboardPageLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    leaderboardLayout = new QTableWidget(10, 2, this);
    leaderboardLayout->setHorizontalHeaderLabels({"Username", "ELO"});
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
    connect(refreshButton, &QPushButton::clicked, this, [&]() { serverController->fetchLeaderboard(); });
    leaderboardPageLayout->addWidget(refreshButton);

    auto leaderboardPage = new QWidget(this);
    leaderboardPage->setLayout(leaderboardPageLayout);

    mainTabBar->addTab(leaderboardPage, "Leaderboard");
}

void QtVue::drawBoard()
{
    gameModel = mainModel->getCurrentGame();
    if (gameModel) {
        if (gameModel->hasWinner()) {
            painter->drawText(QRect(0, 0, 100, 100), "Player: " + QString::fromStdString(gameModel->getWinner()) + " has won!");
        } else {
            if (player == -1) {
                player = gameModel->getPlayerIdx(*mainModel->getUsername());
                playerTurn = gameModel->getCurrentPlayer();
            }
            gameModel->updateBoardIntMatrix(boardIntMatrix);
            if (boardMoveIntMatrix.empty()) {
                boardMoveIntMatrix = boardIntMatrix;
            }

            const int freeCell = 0, playerOne = 1, playerTwo = 2, playerThree = 3, playerFour = 4, emptyQuoridor = 5, occupiedVerticalQuoridor = 6,
                      occupiedHorizontalQuoridor = 7;
            std::vector<Qt::GlobalColor> playerColors {Qt::red, Qt::green, Qt::blue, Qt::magenta};
            std::vector<std::vector<int>> quoridorDirection {
                {0, 4},
                {5, 0}
            }; // 0 = vertical, 1 = horizontal

            canvasPixmap->fill(Qt::white);
            int dx = 10, dy = 100;
            Qt::GlobalColor cellColor;
            for (auto i = 0; i < boardIntMatrix.size(); i++) {
                for (auto j = 0; j < boardIntMatrix[i].size(); j++) {
                    int gridValue = boardIntMatrix[i][j];

                    switch (gridValue) {
                    case freeCell:
                        // draw a free cell
                        {
                            if (boardMoveIntMatrix[i][j] == correctMove) {
                                cellColor = Qt::green;
                            } else if (boardMoveIntMatrix[i][j] == incorrectMove) {
                                cellColor = Qt::red;
                            } else {
                                cellColor = Qt::darkGray;
                            }
                            painter->fillRect(dx, dy, cellSize, cellSize, cellColor);
                            break;
                        }

                        //                if (isClickValid(dx, dy) && isMoveValid(j, i)) {
                        //                    // if mouse is pressed on this cell/quoridor
                        //                    c.DrawText(dx, dy, "\u25A0");
                        //                    handleCellClick(j, i);
                        //                } else if (mouseInCell(dx, dy) && isPlayerTurn()) {
                        //                    // if mouse is pressed on this cell/quoridor
                        //                    c.DrawText(dx, dy, "\u25A0", isMoveValid(j, i) ? Color::Green : Color::Red);
                        //                    c.DrawText(150, 185, "x: " + std::to_string(j) + ", y: " + std::to_string(i));
                        //                } else {
                        //                    c.DrawText(dx, dy, "\u25A1");
                        //                }

                    case emptyQuoridor:
                        break;
                        //                if (mouseInQuoridor(dx, dy) && mousePressed && isWallPlacementValid(j, i)) {
                        //                    std::vector<int> direction = quoridorDirection[wallOrientation];
                        //                    c.DrawBlockLine(dx - direction[0], dy - direction[1], dx + direction[0], dy + direction[1]);
                        //                    handleWallAdd(j, i);
                        //                } else if (mouseInQuoridor(dx, dy) && isPlayerTurn() && isWallPlacementValid(j, i)) {
                        //                    std::vector<int> direction = quoridorDirection[wallOrientation];
                        //                    c.DrawBlockLine(dx - direction[0], dy - direction[1], dx + direction[0], dy + direction[1], Color::Green);
                        //                }
                        // don't draw anything otherwise

                    case occupiedVerticalQuoridor:
                    case occupiedHorizontalQuoridor: {
                        //                std::vector<int> direction = quoridorDirection[gridValue - occupiedVerticalQuoridor];
                        //                c.DrawBlockLine(dx - direction[0], dy - direction[1], dx + direction[0], dy + direction[1]);
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
                        //                c.DrawText(dx, dy, "\u25A0", playerColors[gridValue - 1]);

                    default:
                        break;
                    }
                    //            if (testBoard[i][j] == 1) {
                    //                cellColor = Qt::red;
                    //            } else {
                    //                cellColor = Qt::black;
                    //                painter->setPen(QPen(Qt::black, 5));
                    //            }
                    //            painter->fillRect(dx, dy, cellSize, cellSize, cellColor);

                    dx += cellSize;
                }
                dy += cellSize;
                dx = 10;
            }
            painter->setPen(QPen(Qt::black, 2));
            painter->drawRect(0, 90, cellSize * (int)boardIntMatrix.size() + 20, cellSize * (int)boardIntMatrix.size() + 20);
        }
    }
    drawLabel->setPixmap(*canvasPixmap);
}

void QtVue::createTrainingPage()
{
    auto trainingPageLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto tLabel = new QLabel("Training page");
    tLabel->setAlignment(Qt::AlignTop);
    trainingPageLayout->addWidget(tLabel);

    // this is board
    canvasPixmap = new QPixmap(QSize(800, 800));
    painter = new QPainter(canvasPixmap);
    drawLabel = new DrawLabel(this, this);
    trainingPageLayout->addWidget(drawLabel);

    selectPawnMove = new QPushButton("Pawn");
    selectWallMove = new QPushButton("Wall");
    connect(selectPawnMove, SIGNAL(clicked()), this, SLOT(handlePawnButtonClicked()));
    connect(selectWallMove, SIGNAL(clicked()), this, SLOT(handleWallButtonClicked()));
    selectPawnMove->setCheckable(true);
    selectWallMove->setCheckable(true);
    selectPawnMove->setChecked(true);
    selectPawnMove->setVisible(false);
    selectWallMove->setVisible(false);

    auto selectPawnWallLayout = new QHBoxLayout;
    selectPawnWallLayout->addWidget(selectPawnMove);
    selectPawnWallLayout->addWidget(selectWallMove);
    trainingPageLayout->addLayout(selectPawnWallLayout);

    auto trainingStartButton = new QPushButton("Start training", this);
    connect(trainingStartButton, &QPushButton::clicked, this, [this, trainingStartButton]() {
        mainModel->createAiGame();
        selectPawnMove->setVisible(true);
        selectWallMove->setVisible(true);
        trainingStartButton->setText("Restart");
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

    leaderboardLayout->setRowCount(lb->size());

    for (auto i = 0; i < lb->size(); ++i) {
        auto username = lb->at(i).first;
        auto elo = std::to_string(static_cast<int>(lb->at(i).second));

        auto usernameItem = new QTableWidgetItem {username.c_str()};
        auto eloItem = new QTableWidgetItem {elo.c_str()};

        leaderboardLayout->setItem(i, 0, usernameItem);
        leaderboardLayout->setItem(i, 1, eloItem);
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

void QtVue::updateChats()
{
    updateChatEntries();
}

void QtVue::updateNotifications()
{
    auto currentTabIdx = mainTabBar->currentIndex();
    if (currentTabIdx == -1)
        return;

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
    int i = (y - 25) / cellSize;
    int j = (x - 10) / cellSize;
    return {j, i};
}

void QtVue::handleBoardPress(int x, int y)
{
    //    int i = (y-50) / cellSize;
    //    int j = (x - 10) / cellSize;
    //
    //    std::cout << "i: " << i << " j: " << j << std::endl;
    //    std::cout << boardIntMatrix[i][j] << std::endl;
}

void QtVue::handleBoardMove(int x, int y)
{
    if (gameModel) {
        auto cellCoordinates = getCellCoordinates(x, y);
        boardMoveIntMatrix = boardIntMatrix;
        try {
            if (gameModel->isMoveValid(cellCoordinates)) {
                boardMoveIntMatrix.at(cellCoordinates.y()).at(cellCoordinates.x()) = correctMove;
            } else {
                boardMoveIntMatrix.at(cellCoordinates.y()).at(cellCoordinates.x()) = incorrectMove;
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
        moveType = 0;
    }
    selectWallMove->setChecked(false);
}

void QtVue::handleWallButtonClicked()
{
    if (!selectWallMove->isChecked()) {
        selectWallMove->setChecked(true);
        moveType = 1;
    }
    selectPawnMove->setChecked(false);
}
