//
// Created by louis on 3/30/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QtVue.h" resolved

#include "QtVue.h"
#include "ui_QtVue.h"

QtVue::QtVue(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QtVue)
{
    ui->setupUi(this);

    mainModel = mainController.getMainModel();
    gameModel = mainModel->getCurrentGame();
    serverController = new ServerController {&mainController};

    stackWidget = new QStackedWidget(this);
    stackWidget->setGeometry(0, 0, this->width(), this->height());

    loginTabBar = new QTabWidget(this);
    createLoginAndRegister();
    mainTabBar = new QTabWidget(this);
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
    auto *loginBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    auto *registerBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto loginTextEntry = new QLineEdit(this);
    loginTextEntry->setPlaceholderText("Login");
    loginBoxLayout->addWidget(loginTextEntry);

    auto passwordTextEntry = new QLineEdit(this);
    passwordTextEntry->setPlaceholderText("Password");
    passwordTextEntry->setEchoMode(QLineEdit::Password);
    loginBoxLayout->addWidget(passwordTextEntry);

    loginMessage = new QLabel("");
    loginBoxLayout->addWidget(loginMessage);

    auto *loginButton = new QPushButton("Login", this);
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
    registerBoxLayout->addWidget(registerMessage);

    auto *registerButton = new QPushButton("Register", this);
    connect(registerButton, &QPushButton::clicked, this, [this, registerUsernameTextEntry, registerPasswordTextEntry, registerPasswordConfirmTextEntry]() {
        handleRegisterButtonClicked(registerUsernameTextEntry->text().toStdString(), registerPasswordTextEntry->text().toStdString(),
            registerPasswordConfirmTextEntry->text().toStdString());
    });
    registerBoxLayout->addWidget(registerButton);

    auto *loginBox = new QWidget(this);
    loginBox->setLayout(loginBoxLayout);

    auto *registerBox = new QWidget(this);
    registerBox->setLayout(registerBoxLayout);

    createTrainingPage();

    loginTabBar->addTab(loginBox, "Login");
    loginTabBar->addTab(registerBox, "Register");

    stackWidget->addWidget(loginTabBar);
}

void QtVue::createGamePage()
{
    auto *gamePickerLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto *tLabel = new QLabel("Game page");
    gamePickerLayout->addWidget(tLabel);

    auto *gamePage = new QWidget(this);
    gamePage->setLayout(gamePickerLayout);

    mainTabBar->addTab(gamePage, "Games");
}

void QtVue::createFriendsPage()
{
    auto *friendsPageLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto *tLabel = new QLabel("friends page");
    friendsPageLayout->addWidget(tLabel);

    auto *friendsPage = new QWidget(this);
    friendsPage->setLayout(friendsPageLayout);

    mainTabBar->addTab(friendsPage, "Friends");
}

void QtVue::createLeaderboardPage()
{
    auto *leaderboardPageLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    userEloLabel = new QLabel("");
    leaderboardPageLayout->addWidget(userEloLabel);

    auto *leaderboardPage = new QWidget(this);
    leaderboardPage->setLayout(leaderboardPageLayout);

    mainTabBar->addTab(leaderboardPage, "Leaderboard");
}

void QtVue::createTrainingPage()
{
    auto *trainingPageLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    auto *tLabel = new QLabel("Training page");
    trainingPageLayout->addWidget(tLabel);

    auto *drawLabel = new QLabel();
    auto *canvasPixmap = new QPixmap(QSize(500, 500));
    auto *painter = new QPainter(canvasPixmap);
    drawLabel->setPixmap(*canvasPixmap);

    painter->setPen(QPen(Qt::black, 5));
    painter->drawRect(50, 50, 50, 50);

    auto *trainingPage = new QWidget(this);
    trainingPage->setLayout(trainingPageLayout);

    loginTabBar->addTab(trainingPage, "Training");
}

void QtVue::updateValues()
{
    auto userElo = mainModel->getELO();
    userEloLabel->setText(QString::fromStdString(std::to_string(*userElo)));
}

void QtVue::createMainPage()
{
    createLeaderboardPage();
    createGamePage();
    createFriendsPage();

    stackWidget->addWidget(mainTabBar);
    stackWidget->setCurrentWidget(mainTabBar);

    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QtVue::updateValues);
    timer->start(1000);
}
