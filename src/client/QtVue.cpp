
#include "QtVue.h"

#include <iostream>

QtVue::QtVue(int argc, char *argv[])
    : app(new QApplication(argc, argv))
{
}

QtVue::~QtVue()
{
}

int QtVue::run()
{
    setupRegisterUI();
    setupLoginUI();
    setupGameUI();
    setupMainUI();
    
    appMainWidget->show();
    gotoLoginWindow();
    // gotoGameWindow();

    return app->exec();
}

/* === Main Window === */
void QtVue::setupMainUI(){
    appMainWidget = new QWidget();
    if (appMainWidget->objectName().isEmpty())
        appMainWidget->setObjectName(QStringLiteral("appMainWidget"));
    appMainWidget->resize(1280, 720);
    gridLayout = new QGridLayout(appMainWidget);
    gridLayout->setSpacing(0);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    appMainStacked = new QStackedWidget(appMainWidget);
    appMainStacked->setObjectName(QStringLiteral("appMainStacked"));
    
    appMainStacked->addWidget(registerMainWidget);
    appMainStacked->addWidget(loginMainWidget);
    appMainStacked->addWidget(gameMainWidget);

    gridLayout->addWidget(appMainStacked, 0, 0, 1, 1);
    
    appMainWidget->setWindowTitle("Quoridor");
}

/* === Register Window === */
void QtVue::setupRegisterUI()
{
    registerMainWidget = new QWidget();
    registerMainWidget->setObjectName(QStringLiteral("registerMainWidget"));
    horizontalLayout_r1 = new QHBoxLayout(registerMainWidget);
    horizontalLayout_r1->setObjectName(QStringLiteral("horizontalLayout_r1"));
    registerGroupBox = new QGroupBox(registerMainWidget);
    registerGroupBox->setObjectName(QStringLiteral("registerGroupBox"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(registerGroupBox->sizePolicy().hasHeightForWidth());
    registerGroupBox->setSizePolicy(sizePolicy);
    registerGroupBox->setMinimumSize(QSize(372, 251));
    registerGroupBox->setStyleSheet(QLatin1String("background-color: rgb(196, 207, 218);\n"
                                                  "border-radius: 10px;"));
    registerGroupBox->setFlat(false);
    registerGroupBox->setCheckable(false);
    verticalLayout_r1 = new QVBoxLayout(registerGroupBox);
    verticalLayout_r1->setSpacing(4);
    verticalLayout_r1->setObjectName(QStringLiteral("verticalLayout_r1"));
    verticalLayout_r1->setSizeConstraint(QLayout::SetDefaultConstraint);
    verticalLayout_r1->setContentsMargins(29, 16, 27, 16);
    messageLabelRegister = new QLabel(registerGroupBox);
    messageLabelRegister->setObjectName(QStringLiteral("messageLabelRegister"));
    sizePolicy.setHeightForWidth(messageLabelRegister->sizePolicy().hasHeightForWidth());
    messageLabelRegister->setSizePolicy(sizePolicy);
    messageLabelRegister->setMinimumSize(QSize(311, 31));
    messageLabelRegister->setStyleSheet(QLatin1String("font: 8pt \"MS Shell Dlg 2\";\n"
                                                      "color: rgb(179, 38, 30);"));
    messageLabelRegister->setAlignment(Qt::AlignCenter);

    verticalLayout_r1->addWidget(messageLabelRegister);
    usernameVBoxRegister = new QWidget(registerGroupBox);
    usernameVBoxRegister->setObjectName(QStringLiteral("usernameVBoxRegister"));
    sizePolicy.setHeightForWidth(usernameVBoxRegister->sizePolicy().hasHeightForWidth());
    usernameVBoxRegister->setSizePolicy(sizePolicy);
    usernameVBoxRegister->setMinimumSize(QSize(311, 31));
    usernameVBoxRegister->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
                                                      "border-radius: 0px;"));
    verticalLayout_r2 = new QVBoxLayout(usernameVBoxRegister);
    verticalLayout_r2->setSpacing(1);
    verticalLayout_r2->setObjectName(QStringLiteral("verticalLayout_r2"));
    verticalLayout_r2->setContentsMargins(5, 1, 1, 2);
    usernameLabelRegister = new QLabel(usernameVBoxRegister);
    usernameLabelRegister->setObjectName(QStringLiteral("usernameLabelRegister"));
    usernameLabelRegister->setStyleSheet(QLatin1String("color: rgb(20, 125, 164);\n"
                                                       "border-radius: none;"));
    usernameLabelRegister->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    verticalLayout_r2->addWidget(usernameLabelRegister);

    usernameLineEditRegister = new QLineEdit(usernameVBoxRegister);
    usernameLineEditRegister->setObjectName(QStringLiteral("usernameLineEditRegister"));
    usernameLineEditRegister->setStyleSheet(QLatin1String("QLineEdit {\n"
                                                          "border-radius: none;\n"
                                                          "}\n"
                                                          "\n"
                                                          ""));

    verticalLayout_r2->addWidget(usernameLineEditRegister);

    verticalLayout_r1->addWidget(usernameVBoxRegister);

    passwordVBoxRegister = new QWidget(registerGroupBox);
    passwordVBoxRegister->setObjectName(QStringLiteral("passwordVBoxRegister"));
    sizePolicy.setHeightForWidth(passwordVBoxRegister->sizePolicy().hasHeightForWidth());
    passwordVBoxRegister->setSizePolicy(sizePolicy);
    passwordVBoxRegister->setMinimumSize(QSize(311, 31));
    passwordVBoxRegister->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
                                                      "border-radius: 0px;"));
    verticalLayout_r3 = new QVBoxLayout(passwordVBoxRegister);
    verticalLayout_r3->setSpacing(1);
    verticalLayout_r3->setObjectName(QStringLiteral("verticalLayout_r3"));
    verticalLayout_r3->setContentsMargins(5, 1, 1, 2);
    passwordLabelRegister = new QLabel(passwordVBoxRegister);
    passwordLabelRegister->setObjectName(QStringLiteral("passwordLabelRegister"));
    passwordLabelRegister->setStyleSheet(QLatin1String("color: rgb(20, 125, 164);\n"
                                                       "border-radius: none;"));

    verticalLayout_r3->addWidget(passwordLabelRegister);

    passwordLineEditRegister = new QLineEdit(passwordVBoxRegister);
    passwordLineEditRegister->setObjectName(QStringLiteral("passwordLineEditRegister"));
    passwordLineEditRegister->setStyleSheet(QStringLiteral(""));
    passwordLineEditRegister->setEchoMode(QLineEdit::Password);

    verticalLayout_r3->addWidget(passwordLineEditRegister);

    verticalLayout_r1->addWidget(passwordVBoxRegister);

    confirmPassVBox = new QWidget(registerGroupBox);
    confirmPassVBox->setObjectName(QStringLiteral("confirmPassVBox"));
    sizePolicy.setHeightForWidth(confirmPassVBox->sizePolicy().hasHeightForWidth());
    confirmPassVBox->setSizePolicy(sizePolicy);
    confirmPassVBox->setMinimumSize(QSize(311, 34));
    confirmPassVBox->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
                                                 "border-radius: 0px;"));
    verticalLayout_r4 = new QVBoxLayout(confirmPassVBox);
    verticalLayout_r4->setSpacing(1);
    verticalLayout_r4->setObjectName(QStringLiteral("verticalLayout_r4"));
    verticalLayout_r4->setContentsMargins(5, 1, 1, 2);
    confirmPasswordLabel = new QLabel(confirmPassVBox);
    confirmPasswordLabel->setObjectName(QStringLiteral("confirmPasswordLabel"));
    confirmPasswordLabel->setStyleSheet(QLatin1String("color: rgb(20, 125, 164);\n"
                                                      "border-radius: none;"));

    verticalLayout_r4->addWidget(confirmPasswordLabel);

    confirmPasswordLineEdit = new QLineEdit(confirmPassVBox);
    confirmPasswordLineEdit->setObjectName(QStringLiteral("confirmPasswordLineEdit"));
    confirmPasswordLineEdit->setStyleSheet(QStringLiteral(""));
    confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

    verticalLayout_r4->addWidget(confirmPasswordLineEdit);

    verticalLayout_r1->addWidget(confirmPassVBox);

    registerButton = new QPushButton(registerGroupBox);
    registerButton->setObjectName(QStringLiteral("registerButton"));
    sizePolicy.setHeightForWidth(registerButton->sizePolicy().hasHeightForWidth());
    registerButton->setSizePolicy(sizePolicy);
    registerButton->setMinimumSize(QSize(311, 31));
    registerButton->setStyleSheet(QLatin1String("QPushButton {\n"
                                                "color: rgb(255, 255, 255);\n"
                                                "background-color: rgb(8, 76, 102);\n"
                                                "border-radius: 3px;\n"
                                                "}\n"
                                                "\n"
                                                "QPushButton:hover {\n"
                                                "background-color: rgb(20, 125, 164);\n"
                                                "}\n"
                                                "\n"
                                                "QPushButton:pressed {\n"
                                                "   /*background-color: rgb(18, 111, 145);*/\n"
                                                "	background-color: rgb(85, 170, 127);\n"
                                                "	\n"
                                                "}\n"
                                                "\n"
                                                ""));
    registerButton->setIconSize(QSize(12, 16));

    verticalLayout_r1->addWidget(registerButton);

    horizontalLayout_r1->addWidget(registerGroupBox);

    messageLabelRegister->setText("");
    usernameLabelRegister->setText("Username");
    usernameLineEditRegister->setText("");
    passwordLabelRegister->setText("Password");
    passwordLineEditRegister->setText("");
    confirmPasswordLabel->setText("Confirm password");
    confirmPasswordLineEdit->setText("");
    registerButton->setText("REGISTER");

    messageLabelRegister->hide();

    QObject::connect(registerButton, &QPushButton::clicked, [this]() { this->registerButtonPressed(); });
}

/* === Login Window === */
void QtVue::setupLoginUI()
{
    loginMainWidget = new QWidget();
    loginMainWidget->setObjectName(QStringLiteral("loginMainWidget"));
    horizontalLayout_l1 = new QHBoxLayout(loginMainWidget);
    horizontalLayout_l1->setObjectName(QStringLiteral("horizontalLayout_l1"));
    loginGroupBox = new QGroupBox(loginMainWidget);
    loginGroupBox->setObjectName(QStringLiteral("loginGroupBox"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(loginGroupBox->sizePolicy().hasHeightForWidth());
    loginGroupBox->setSizePolicy(sizePolicy);
    loginGroupBox->setMinimumSize(QSize(372, 251));
    loginGroupBox->setStyleSheet(QLatin1String("background-color: rgb(196, 207, 218);\n"
                                               "border-radius: 10px;"));
    loginGroupBox->setFlat(false);
    loginGroupBox->setCheckable(false);
    verticalLayout_l1 = new QVBoxLayout(loginGroupBox);
    verticalLayout_l1->setSpacing(4);
    verticalLayout_l1->setObjectName(QStringLiteral("verticalLayout_l1"));
    verticalLayout_l1->setContentsMargins(29, 16, 27, 16);
    messageLabelLogin = new QLabel(loginGroupBox);
    messageLabelLogin->setObjectName(QStringLiteral("messageLabelLogin"));
    sizePolicy.setHeightForWidth(messageLabelLogin->sizePolicy().hasHeightForWidth());
    messageLabelLogin->setSizePolicy(sizePolicy);
    messageLabelLogin->setMinimumSize(QSize(311, 31));
    messageLabelLogin->setStyleSheet(QLatin1String("font: 8pt \"MS Shell Dlg 2\";\n"
                                                   "color: rgb(179, 38, 30);"));
    messageLabelLogin->setAlignment(Qt::AlignCenter);
    verticalLayout_l1->addWidget(messageLabelLogin);
    usernameVBoxLogin = new QWidget(loginGroupBox);
    usernameVBoxLogin->setObjectName(QStringLiteral("usernameVBoxLogin"));
    sizePolicy.setHeightForWidth(usernameVBoxLogin->sizePolicy().hasHeightForWidth());
    usernameVBoxLogin->setSizePolicy(sizePolicy);
    usernameVBoxLogin->setMinimumSize(QSize(311, 31));
    usernameVBoxLogin->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
                                                   "border-radius: 0px;"));
    verticalLayout_l2 = new QVBoxLayout(usernameVBoxLogin);
    verticalLayout_l2->setSpacing(1);
    verticalLayout_l2->setObjectName(QStringLiteral("verticalLayout_l2"));
    verticalLayout_l2->setContentsMargins(5, 1, 1, 2);
    usernameLabelLogin = new QLabel(usernameVBoxLogin);
    usernameLabelLogin->setObjectName(QStringLiteral("usernameLabelLogin"));
    usernameLabelLogin->setStyleSheet(QLatin1String("color: rgb(20, 125, 164);\n"
                                                    "border-radius: none;"));
    usernameLabelLogin->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    verticalLayout_l2->addWidget(usernameLabelLogin);

    usernameLineEditLogin = new QLineEdit(usernameVBoxLogin);
    usernameLineEditLogin->setObjectName(QStringLiteral("usernameLineEditLogin"));
    usernameLineEditLogin->setStyleSheet(QLatin1String("QLineEdit {\n"
                                                       "border-radius: none;\n"
                                                       "}\n"
                                                       "\n"
                                                       ""));
    usernameLineEditLogin->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    verticalLayout_l2->addWidget(usernameLineEditLogin);

    verticalLayout_l1->addWidget(usernameVBoxLogin);

    passwordVBoxLogin = new QWidget(loginGroupBox);
    passwordVBoxLogin->setObjectName(QStringLiteral("passwordVBoxLogin"));
    sizePolicy.setHeightForWidth(passwordVBoxLogin->sizePolicy().hasHeightForWidth());
    passwordVBoxLogin->setSizePolicy(sizePolicy);
    passwordVBoxLogin->setMinimumSize(QSize(311, 31));
    passwordVBoxLogin->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
                                                   "border-radius: 0px;"));
    verticalLayout_l3 = new QVBoxLayout(passwordVBoxLogin);
    verticalLayout_l3->setSpacing(1);
    verticalLayout_l3->setObjectName(QStringLiteral("verticalLayout_l3"));
    verticalLayout_l3->setContentsMargins(5, 1, 1, 2);
    passwordLabelLogin = new QLabel(passwordVBoxLogin);
    passwordLabelLogin->setObjectName(QStringLiteral("passwordLabelLogin"));
    passwordLabelLogin->setStyleSheet(QLatin1String("color: rgb(20, 125, 164);\n"
                                                    "border-radius: none;"));

    verticalLayout_l3->addWidget(passwordLabelLogin);

    passwordLineEditLogin = new QLineEdit(passwordVBoxLogin);
    passwordLineEditLogin->setObjectName(QStringLiteral("passwordLineEditLogin"));
    passwordLineEditLogin->setStyleSheet(QStringLiteral(""));
    passwordLineEditLogin->setFrame(true);
    passwordLineEditLogin->setEchoMode(QLineEdit::Password);
    passwordLineEditLogin->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    verticalLayout_l3->addWidget(passwordLineEditLogin);

    verticalLayout_l1->addWidget(passwordVBoxLogin);

    loginButton = new QPushButton(loginGroupBox);
    loginButton->setObjectName(QStringLiteral("loginButton"));
    sizePolicy.setHeightForWidth(loginButton->sizePolicy().hasHeightForWidth());
    loginButton->setSizePolicy(sizePolicy);
    loginButton->setMinimumSize(QSize(311, 31));
    loginButton->setStyleSheet(QLatin1String("QPushButton {\n"
                                             "color: rgb(255, 255, 255);\n"
                                             "background-color: rgb(8, 76, 102);\n"
                                             "border-radius: 3px;\n"
                                             "}\n"
                                             "\n"
                                             "QPushButton:hover {\n"
                                             "background-color: rgb(20, 125, 164);\n"
                                             "}\n"
                                             "\n"
                                             "QPushButton:pressed {\n"
                                             "   background-color: rgb(18, 111, 145);\n"
                                             "}\n"
                                             ""));
    loginButton->setIconSize(QSize(12, 16));

    verticalLayout_l1->addWidget(loginButton);

    registerLabel = new QLabel(loginGroupBox);
    registerLabel->setObjectName(QStringLiteral("registerLabel"));
    sizePolicy.setHeightForWidth(registerLabel->sizePolicy().hasHeightForWidth());
    registerLabel->setSizePolicy(sizePolicy);
    registerLabel->setMinimumSize(QSize(311, 31));
    registerLabel->setStyleSheet(QLatin1String("font: 8pt \"MS Shell Dlg 2\";\n"
                                               "text-decoration: underline;"));
    registerLabel->setAlignment(Qt::AlignCenter);

    verticalLayout_l1->addWidget(registerLabel);

    registerButtonLogin = new QPushButton(loginGroupBox);
    registerButtonLogin->setObjectName(QStringLiteral("registerButtonLogin"));
    sizePolicy.setHeightForWidth(registerButtonLogin->sizePolicy().hasHeightForWidth());
    registerButtonLogin->setSizePolicy(sizePolicy);
    registerButtonLogin->setMinimumSize(QSize(311, 31));
    registerButtonLogin->setStyleSheet(QLatin1String("QPushButton {\n"
                                                     "color: rgb(255, 255, 255);\n"
                                                     "background-color: rgb(8, 76, 102);\n"
                                                     "border-radius: 3px;\n"
                                                     "}\n"
                                                     "\n"
                                                     "QPushButton:hover {\n"
                                                     "background-color: rgb(20, 125, 164);\n"
                                                     "}\n"
                                                     "\n"
                                                     "QPushButton:pressed {\n"
                                                     "   background-color: rgb(18, 111, 145);\n"
                                                     "}\n"
                                                     "\n"
                                                     ""));
    registerButtonLogin->setIconSize(QSize(12, 16));

    verticalLayout_l1->addWidget(registerButtonLogin);

    horizontalLayout_l1->addWidget(loginGroupBox);

    messageLabelLogin->setText("");
    usernameLabelLogin->setText("Username");
    usernameLineEditLogin->setInputMask(QString());
    usernameLineEditLogin->setText("");
    passwordLabelLogin->setText("Password");
    passwordLineEditLogin->setText("");
    loginButton->setText("LOGIN");
    registerLabel->setText("Not registered yet ?");
    registerButtonLogin->setText("REGISTER");

    messageLabelLogin->hide();

    QObject::connect(loginButton, &QPushButton::clicked, [this]() { this->loginButtonPressed(); });
    QObject::connect(registerButtonLogin, &QPushButton::clicked, [this]() { this->gotoRegisterWindow(); });
}

/* === Game Window === */
void QtVue::setupGameUI()
{
	gameMainWidget = new QWidget();
    gameMainWidget->setObjectName(QStringLiteral("gameMainWidget"));
    gameMainWidget->setStyleSheet(QStringLiteral(""));
    verticalLayout = new QVBoxLayout(gameMainWidget);
    verticalLayout->setSpacing(20);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 30);
    topBar = new QFrame(gameMainWidget);
    topBar->setObjectName(QStringLiteral("topBar"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(topBar->sizePolicy().hasHeightForWidth());
    topBar->setSizePolicy(sizePolicy);
    topBar->setMinimumSize(QSize(0, 55));
    topBar->setBaseSize(QSize(0, 0));
    topBar->setCursor(QCursor(Qt::ArrowCursor));
    topBar->setStyleSheet(QLatin1String("QFrame {\n"
                                        "	background-color: rgb(196, 207, 218);\n"
                                        "}"));
    horizontalLayout = new QHBoxLayout(topBar);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, -1, 0);
    topBarButtons = new QWidget(topBar);
    topBarButtons->setObjectName(QStringLiteral("topBarButtons"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(topBarButtons->sizePolicy().hasHeightForWidth());
    topBarButtons->setSizePolicy(sizePolicy1);
    topBarButtons->setStyleSheet(QLatin1String("QPushButton{\n"
                                               "	font: 10pt \"MS Shell Dlg 2\";\n"
                                               "	color: rgb(8,76,102);\n"
                                               "	background-color: rgb(196, 207, 218);\n"
                                               "	border: 3px solid rgb(196, 207, 218);\n"
                                               "	border-radius: 7px;\n"
                                               "	padding: 12px;\n"
                                               "}\n"
                                               "\n"
                                               "QPushButton:hover {\n"
                                               "	color: rgb(20,125,164);\n"
                                               "	border-color: rgb(20,125,164);\n"
                                               "}\n"
                                               "\n"
                                               "QPushButton:focus {\n"
                                               "	color: rgb(20,125,200);\n"
                                               "	border-color: rgb(20,125,164);\n"
                                               "}\n"
                                               "\n"
                                               "QPushButton:pressed {\n"
                                               "	border: 2px solid rgb(196, 207, 218);\n"
                                               "	color: rgb(20,125,200);\n"
                                               "	border-color: rgb(20,125,164);\n"
                                               "}"));
    horizontalLayout_2 = new QHBoxLayout(topBarButtons);
    horizontalLayout_2->setSpacing(5);
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    gameButton = new QPushButton(topBarButtons);
    gameButton->setObjectName(QStringLiteral("gameButton"));
    QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(gameButton->sizePolicy().hasHeightForWidth());
    gameButton->setSizePolicy(sizePolicy2);
    gameButton->setMinimumSize(QSize(0, 0));
    gameButton->setCursor(QCursor(Qt::ArrowCursor));
    gameButton->setMouseTracking(false);
    gameButton->setStyleSheet(QStringLiteral(""));
    gameButton->setCheckable(false);
    gameButton->setChecked(false);
    gameButton->setAutoExclusive(false);

    horizontalLayout_2->addWidget(gameButton);

    friendsButton = new QPushButton(topBarButtons);
    friendsButton->setObjectName(QStringLiteral("friendsButton"));
    sizePolicy2.setHeightForWidth(friendsButton->sizePolicy().hasHeightForWidth());
    friendsButton->setSizePolicy(sizePolicy2);
    friendsButton->setMinimumSize(QSize(0, 0));
    friendsButton->setCursor(QCursor(Qt::ArrowCursor));
    friendsButton->setStyleSheet(QStringLiteral(""));
    friendsButton->setCheckable(false);
    friendsButton->setChecked(false);

    horizontalLayout_2->addWidget(friendsButton);

    leaderboardButton = new QPushButton(topBarButtons);
    leaderboardButton->setObjectName(QStringLiteral("leaderboardButton"));
    sizePolicy2.setHeightForWidth(leaderboardButton->sizePolicy().hasHeightForWidth());
    leaderboardButton->setSizePolicy(sizePolicy2);
    leaderboardButton->setMinimumSize(QSize(0, 0));
    leaderboardButton->setStyleSheet(QStringLiteral(""));

    horizontalLayout_2->addWidget(leaderboardButton);

    horizontalLayout->addWidget(topBarButtons);

    topBarSpacer = new QSpacerItem(50, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(topBarSpacer);

    topBarUser = new QWidget(topBar);
    topBarUser->setObjectName(QStringLiteral("topBarUser"));
    QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(topBarUser->sizePolicy().hasHeightForWidth());
    topBarUser->setSizePolicy(sizePolicy3);
    horizontalLayout_3 = new QHBoxLayout(topBarUser);
    horizontalLayout_3->setSpacing(14);
    horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
    horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    userInfo = new QWidget(topBarUser);
    userInfo->setObjectName(QStringLiteral("userInfo"));
    sizePolicy3.setHeightForWidth(userInfo->sizePolicy().hasHeightForWidth());
    userInfo->setSizePolicy(sizePolicy3);
    verticalLayout_2 = new QVBoxLayout(userInfo);
    verticalLayout_2->setSpacing(5);
    verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
    verticalLayout_2->setContentsMargins(0, 0, 0, 0);
    usernameLabel = new QLabel(userInfo);
    usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
    QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(usernameLabel->sizePolicy().hasHeightForWidth());
    usernameLabel->setSizePolicy(sizePolicy4);
    usernameLabel->setStyleSheet(QLatin1String("QLabel#usernameLabel {\n"
                                               "	color: rgb(7, 39, 51);\n"
                                               "}"));
    usernameLabel->setAlignment(Qt::AlignCenter);

    verticalLayout_2->addWidget(usernameLabel);

    eloLabel = new QLabel(userInfo);
    eloLabel->setObjectName(QStringLiteral("eloLabel"));
    sizePolicy4.setHeightForWidth(eloLabel->sizePolicy().hasHeightForWidth());
    eloLabel->setSizePolicy(sizePolicy4);
    eloLabel->setStyleSheet(QLatin1String("QLabel#eloLabel {\n"
                                          "	color: rgb(7, 39, 51);\n"
                                          "}"));
    eloLabel->setAlignment(Qt::AlignCenter);

    verticalLayout_2->addWidget(eloLabel);

    horizontalLayout_3->addWidget(userInfo);

    logoutButton = new QPushButton(topBarUser);
    logoutButton->setObjectName(QStringLiteral("logoutButton"));
    QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(logoutButton->sizePolicy().hasHeightForWidth());
    logoutButton->setSizePolicy(sizePolicy5);
    logoutButton->setMinimumSize(QSize(55, 35));
    logoutButton->setMaximumSize(QSize(0, 16777215));
    logoutButton->setCursor(QCursor(Qt::ArrowCursor));
    logoutButton->setStyleSheet(QLatin1String("QPushButton#logoutButton{\n"
                                              "	font: 7pt \"MS Shell Dlg 2\";\n"
                                              "	color: rgb(255, 255, 255);\n"
                                              "	background-color: rgb(179,38,30);\n"
                                              "	border: 3px solid rgb(179,38,30);\n"
                                              "	border-radius: 15px;\n"
                                              "}\n"
                                              "\n"
                                              "QPushButton:hover#logoutButton{\n"
                                              "	background-color: rgb(148, 31, 25);\n"
                                              "	border-color: rgb(148, 31,25);\n"
                                              "}\n"
                                              "\n"
                                              "QPushButton:pressed#logoutButton{\n"
                                              "	border-top-color: rgb(167, 33, 28);\n"
                                              "	border-left-color: rgb(167, 33, 28);\n"
                                              "	border-bottom-color: rgb(127, 25, 21);\n"
                                              "	border-right-color: rgb(127, 25, 21);\n"
                                              "}"));

    horizontalLayout_3->addWidget(logoutButton);

    horizontalLayout->addWidget(topBarUser);

    verticalLayout->addWidget(topBar);

    mainStacked = new QStackedWidget(gameMainWidget);
    mainStacked->setObjectName(QStringLiteral("mainStacked"));
    sizePolicy4.setHeightForWidth(mainStacked->sizePolicy().hasHeightForWidth());
    mainStacked->setSizePolicy(sizePolicy4);
    mainStacked->setSizeIncrement(QSize(6, 0));
    gamePage = new QWidget();
    gamePage->setObjectName(QStringLiteral("gamePage"));
    horizontalLayout_4 = new QHBoxLayout(gamePage);
    horizontalLayout_4->setSpacing(10);
    horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
    horizontalLayout_4->setContentsMargins(0, 10, 0, 0);
    gameSidebar = new QFrame(gamePage);
    gameSidebar->setObjectName(QStringLiteral("gameSidebar"));
    QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy6.setHorizontalStretch(1);
    sizePolicy6.setVerticalStretch(0);
    sizePolicy6.setHeightForWidth(gameSidebar->sizePolicy().hasHeightForWidth());
    gameSidebar->setSizePolicy(sizePolicy6);
    gameSidebar->setMinimumSize(QSize(0, 0));
    gameSidebar->setStyleSheet(QLatin1String("QFrame{\n"
                                             "	background-color: rgb(196, 207, 218);\n"
                                             "}"));
    gameSidebar->setFrameShape(QFrame::StyledPanel);
    gameSidebar->setFrameShadow(QFrame::Raised);
    verticalLayout_3 = new QVBoxLayout(gameSidebar);
    verticalLayout_3->setSpacing(10);
    verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
    verticalLayout_3->setContentsMargins(20, 20, 20, 20);
    createGameButton = new QPushButton(gameSidebar);
    createGameButton->setObjectName(QStringLiteral("createGameButton"));
    QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy7.setHorizontalStretch(0);
    sizePolicy7.setVerticalStretch(0);
    sizePolicy7.setHeightForWidth(createGameButton->sizePolicy().hasHeightForWidth());
    createGameButton->setSizePolicy(sizePolicy7);
    createGameButton->setMinimumSize(QSize(0, 35));
    createGameButton->setStyleSheet(QLatin1String("QPushButton#createGameButton{\n"
                                                  "	color: rgb(255, 255, 255);\n"
                                                  "	background-color: rgb(7, 39, 51);\n"
                                                  "	border: 4px solid rgb(7, 39, 51);\n"
                                                  "	border-radius: 8px;\n"
                                                  "	padding: 3px;\n"
                                                  "}\n"
                                                  "\n"
                                                  "QPushButton:hover#createGameButton{\n"
                                                  "	background-color: rgb(8, 76, 102);\n"
                                                  "	border-color: rgb(8, 76, 102);\n"
                                                  "}\n"
                                                  "\n"
                                                  "QPushButton:focus#createGameButton{\n"
                                                  "	background-color: rgb(96, 96, 96);\n"
                                                  "	border-color: rgb(8, 76, 102);\n"
                                                  "}\n"
                                                  "\n"
                                                  "QPushButton:pressed#createGameButton{\n"
                                                  "	background-color: rgb(96, 96, 96);\n"
                                                  "	border-color:  rgb(9, 87, 116) rgb(6, 60, 79) rgb(6, 60, 79)  rgb(9, 87, 116);\n"
                                                  "}"));

    verticalLayout_3->addWidget(createGameButton);

    joinGameButton = new QPushButton(gameSidebar);
    joinGameButton->setObjectName(QStringLiteral("joinGameButton"));
    sizePolicy7.setHeightForWidth(joinGameButton->sizePolicy().hasHeightForWidth());
    joinGameButton->setSizePolicy(sizePolicy7);
    joinGameButton->setMinimumSize(QSize(0, 35));
    joinGameButton->setStyleSheet(QLatin1String("QPushButton#joinGameButton{\n"
                                                "	color: rgb(255, 255, 255);\n"
                                                "	background-color: rgb(7, 39, 51);\n"
                                                "	border: 4px solid rgb(7, 39, 51);\n"
                                                "	border-radius: 8px;\n"
                                                "	padding: 3px;\n"
                                                "}\n"
                                                "\n"
                                                "QPushButton:hover#joinGameButton{\n"
                                                "	background-color: rgb(8, 76, 102);\n"
                                                "	border-color: rgb(8, 76, 102);\n"
                                                "}\n"
                                                "\n"
                                                "QPushButton:focus#joinGameButton{\n"
                                                "	background-color: rgb(96, 96, 96);\n"
                                                "	border-color: rgb(8, 76, 102);\n"
                                                "}\n"
                                                "\n"
                                                "QPushButton:pressed#joinGameButton{\n"
                                                "	background-color: rgb(96, 96, 96);\n"
                                                "	border-color:  rgb(9, 87, 116) rgb(6, 60, 79) rgb(6, 60, 79)  rgb(9, 87, 116);\n"
                                                "}"));

    verticalLayout_3->addWidget(joinGameButton);

    verticalSpacerSidebar = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_3->addItem(verticalSpacerSidebar);

    horizontalLayout_4->addWidget(gameSidebar);

    gameMainStacked = new QStackedWidget(gamePage);
    gameMainStacked->setObjectName(QStringLiteral("gameMainStacked"));
    QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy8.setHorizontalStretch(3);
    sizePolicy8.setVerticalStretch(0);
    sizePolicy8.setHeightForWidth(gameMainStacked->sizePolicy().hasHeightForWidth());
    gameMainStacked->setSizePolicy(sizePolicy8);
    createGamePage = new QWidget();
    createGamePage->setObjectName(QStringLiteral("createGamePage"));
    horizontalLayout_5 = new QHBoxLayout(createGamePage);
    horizontalLayout_5->setSpacing(10);
    horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
    gameConfigurationBox = new QGroupBox(createGamePage);
    gameConfigurationBox->setObjectName(QStringLiteral("gameConfigurationBox"));
    QSizePolicy sizePolicy9(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy9.setHorizontalStretch(2);
    sizePolicy9.setVerticalStretch(0);
    sizePolicy9.setHeightForWidth(gameConfigurationBox->sizePolicy().hasHeightForWidth());
    gameConfigurationBox->setSizePolicy(sizePolicy9);
    gameConfigurationBox->setStyleSheet(QLatin1String("QGroupBox#gameConfigBox{\n"
                                                      "	border: 1px solid rgb(8,76,102);\n"
                                                      "	border-radius: 10px;\n"
                                                      "}"));
    verticalLayout_5 = new QVBoxLayout(gameConfigurationBox);
    verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
    gameConfigurationLabel = new QLabel(gameConfigurationBox);
    gameConfigurationLabel->setObjectName(QStringLiteral("gameConfigurationLabel"));
    sizePolicy7.setHeightForWidth(gameConfigurationLabel->sizePolicy().hasHeightForWidth());
    gameConfigurationLabel->setSizePolicy(sizePolicy7);
    gameConfigurationLabel->setMinimumSize(QSize(0, 20));
    gameConfigurationLabel->setStyleSheet(QLatin1String("QLabel#gameConfigurationLabel{\n"
                                                        "	font: 10pt \"MS Shell Dlg 2\";\n"
                                                        "	color: rgb(7, 39, 51);\n"
                                                        "}"));
    gameConfigurationLabel->setAlignment(Qt::AlignCenter);

    verticalLayout_5->addWidget(gameConfigurationLabel);

    playerNumberLabel = new QLabel(gameConfigurationBox);
    playerNumberLabel->setObjectName(QStringLiteral("playerNumberLabel"));
    sizePolicy7.setHeightForWidth(playerNumberLabel->sizePolicy().hasHeightForWidth());
    playerNumberLabel->setSizePolicy(sizePolicy7);
    playerNumberLabel->setMinimumSize(QSize(0, 31));
    playerNumberLabel->setStyleSheet(QLatin1String("QLabel#playernumberLabel{\n"
                                                   "	border: 1px solid rgb(8,76,102);\n"
                                                   "	color: rgb(7, 39, 51);\n"
                                                   "	border-radius: 3px;\n"
                                                   "}"));
    playerNumberLabel->setTextFormat(Qt::AutoText);
    playerNumberLabel->setScaledContents(false);
    playerNumberLabel->setIndent(7);

    verticalLayout_5->addWidget(playerNumberLabel);

    playerNumberChoices = new QHBoxLayout();
    playerNumberChoices->setObjectName(QStringLiteral("playerNumberChoices"));
    playerNumberChoices->setContentsMargins(40, -1, -1, -1);
    twoPlayersChoice = new QRadioButton(gameConfigurationBox);
    twoPlayersChoice->setObjectName(QStringLiteral("twoPlayersChoice"));

    playerNumberChoices->addWidget(twoPlayersChoice);

    fourPlayersChoice = new QRadioButton(gameConfigurationBox);
    fourPlayersChoice->setObjectName(QStringLiteral("fourPlayersChoice"));

    playerNumberChoices->addWidget(fourPlayersChoice);

    verticalLayout_5->addLayout(playerNumberChoices);

    gameModeLabel = new QLabel(gameConfigurationBox);
    gameModeLabel->setObjectName(QStringLiteral("gameModeLabel"));
    sizePolicy7.setHeightForWidth(gameModeLabel->sizePolicy().hasHeightForWidth());
    gameModeLabel->setSizePolicy(sizePolicy7);
    gameModeLabel->setMinimumSize(QSize(0, 31));
    gameModeLabel->setStyleSheet(QLatin1String("QLabel#gamemodeLabel{\n"
                                               "	border: 1px solid rgb(8,76,102);\n"
                                               "	border-radius: 3px;\n"
                                               "	color: rgb(7, 39, 51);\n"
                                               "}"));
    gameModeLabel->setIndent(7);

    verticalLayout_5->addWidget(gameModeLabel);

    gameModeChoices = new QHBoxLayout();
    gameModeChoices->setObjectName(QStringLiteral("gameModeChoices"));
    gameModeChoices->setContentsMargins(40, -1, -1, -1);
    originalModeChoice = new QRadioButton(gameConfigurationBox);
    originalModeChoice->setObjectName(QStringLiteral("originalModeChoice"));

    gameModeChoices->addWidget(originalModeChoice);

    quotetrisModeChoice = new QRadioButton(gameConfigurationBox);
    quotetrisModeChoice->setObjectName(QStringLiteral("quotetrisModeChoice"));

    gameModeChoices->addWidget(quotetrisModeChoice);

    timerModeChoice = new QRadioButton(gameConfigurationBox);
    timerModeChoice->setObjectName(QStringLiteral("timerModeChoice"));

    gameModeChoices->addWidget(timerModeChoice);

    trainingModeChoice = new QRadioButton(gameConfigurationBox);
    trainingModeChoice->setObjectName(QStringLiteral("trainingModeChoice"));

    gameModeChoices->addWidget(trainingModeChoice);

    verticalLayout_5->addLayout(gameModeChoices);

    gameStartContainer = new QHBoxLayout();
    gameStartContainer->setObjectName(QStringLiteral("gameStartContainer"));
    gameStartContainer->setContentsMargins(-1, 20, -1, 0);
    startLeftSpacer = new QSpacerItem(128, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gameStartContainer->addItem(startLeftSpacer);

    startButton = new QPushButton(gameConfigurationBox);
    startButton->setObjectName(QStringLiteral("startButton"));
    sizePolicy5.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
    startButton->setSizePolicy(sizePolicy5);
    startButton->setMinimumSize(QSize(91, 41));
    startButton->setStyleSheet(QLatin1String("QPushButton#startButton{\n"
                                             "	border: 1px solid rgb(20,125,164);\n"
                                             "	color: rgb(255, 255, 255);\n"
                                             "	background-color: rgb(20,125,164);\n"
                                             "	border-radius: 20px;\n"
                                             "}\n"
                                             "\n"
                                             "QPushButton:hover#startButton {\n"
                                             "	background-color: rgb(8, 76, 102);\n"
                                             "	border-color: rgb(8, 76, 102);\n"
                                             "}\n"
                                             "\n"
                                             "QPushButton:pressed#startButton{\n"
                                             "	border: 6px solid;\n"
                                             "	border-top-color: rgb(9, 87, 116);\n"
                                             "	border-left-color: rgb(9, 87, 116);\n"
                                             "	border-bottom-color: rgb(7, 69, 91);\n"
                                             "	border-right-color: rgb(7, 69, 91);\n"
                                             "}"));

    gameStartContainer->addWidget(startButton);

    startRightSpacer = new QSpacerItem(118, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gameStartContainer->addItem(startRightSpacer);

    verticalLayout_5->addLayout(gameStartContainer);

    horizontalLayout_5->addWidget(gameConfigurationBox);

    inviteFriendsBox = new QGroupBox(createGamePage);
    inviteFriendsBox->setObjectName(QStringLiteral("inviteFriendsBox"));
    sizePolicy6.setHeightForWidth(inviteFriendsBox->sizePolicy().hasHeightForWidth());
    inviteFriendsBox->setSizePolicy(sizePolicy6);
    inviteFriendsBox->setStyleSheet(QLatin1String("QGroupBox#inviteFriendsBox{\n"
                                                  "	/*background-color: rgb(196, 207, 218);*/\n"
                                                  "	border: none;\n"
                                                  "}"));
    inviteFriendsBoxVLayout = new QVBoxLayout(inviteFriendsBox);
    inviteFriendsBoxVLayout->setObjectName(QStringLiteral("inviteFriendsBoxVLayout"));
    inviteFriendsUpSpacer = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Fixed);

    inviteFriendsBoxVLayout->addItem(inviteFriendsUpSpacer);

    inviteGroupBox = new QGroupBox(inviteFriendsBox);
    inviteGroupBox->setObjectName(QStringLiteral("inviteGroupBox"));
    inviteGroupBox->setStyleSheet(QLatin1String("QGroupBox#inviteGroupBox{\n"
                                                "	border: 1px solid rgb(8, 76, 102);\n"
                                                "	border-radius: 5px;\n"
                                                "}"));
    inviteFriendsVLayout = new QVBoxLayout(inviteGroupBox);
    inviteFriendsVLayout->setObjectName(QStringLiteral("inviteFriendsVLayout"));
    inviteFriendsLabel = new QLabel(inviteGroupBox);
    inviteFriendsLabel->setObjectName(QStringLiteral("inviteFriendsLabel"));
    sizePolicy7.setHeightForWidth(inviteFriendsLabel->sizePolicy().hasHeightForWidth());
    inviteFriendsLabel->setSizePolicy(sizePolicy7);
    inviteFriendsLabel->setMinimumSize(QSize(0, 20));
    inviteFriendsLabel->setStyleSheet(QLatin1String("QLabel#invitefriendsLabel{\n"
                                                    "	font: 10pt \"MS Shell Dlg 2\";\n"
                                                    "	color: rgb(7, 39, 51);\n"
                                                    "}"));
    inviteFriendsLabel->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);

    inviteFriendsVLayout->addWidget(inviteFriendsLabel);

    inviteFriendsScrollArea = new QScrollArea(inviteGroupBox);
    inviteFriendsScrollArea->setObjectName(QStringLiteral("inviteFriendsScrollArea"));
    QSizePolicy sizePolicy10(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy10.setHorizontalStretch(0);
    sizePolicy10.setVerticalStretch(0);
    sizePolicy10.setHeightForWidth(inviteFriendsScrollArea->sizePolicy().hasHeightForWidth());
    inviteFriendsScrollArea->setSizePolicy(sizePolicy10);
    inviteFriendsScrollArea->setStyleSheet(QLatin1String("QScrollArea{\n"
                                                         "	border: none;\n"
                                                         "}"));
    inviteFriendsScrollArea->setWidgetResizable(true);
    inviteFriendsScrollAreaWidgetContents = new QWidget();
    inviteFriendsScrollAreaWidgetContents->setObjectName(QStringLiteral("inviteFriendsScrollAreaWidgetContents"));
    inviteFriendsScrollAreaWidgetContents->setGeometry(QRect(0, 0, 313, 69));
    verticalLayout_17 = new QVBoxLayout(inviteFriendsScrollAreaWidgetContents);
    verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
    inviteFriendsScrollArea->setWidget(inviteFriendsScrollAreaWidgetContents);

    inviteFriendsVLayout->addWidget(inviteFriendsScrollArea, 0, Qt::AlignTop);

    inviteFriendsBoxVLayout->addWidget(inviteGroupBox);

    inviteFriendsDownSpacer = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Fixed);

    inviteFriendsBoxVLayout->addItem(inviteFriendsDownSpacer);

    horizontalLayout_5->addWidget(inviteFriendsBox, 0, Qt::AlignVCenter);

    gameMainStacked->addWidget(createGamePage);
    joinGamePage = new QWidget();
    joinGamePage->setObjectName(QStringLiteral("joinGamePage"));
    horizontalLayout_27 = new QHBoxLayout(joinGamePage);
    horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
    liveGamesFrame = new QFrame(joinGamePage);
    liveGamesFrame->setObjectName(QStringLiteral("liveGamesFrame"));
    sizePolicy9.setHeightForWidth(liveGamesFrame->sizePolicy().hasHeightForWidth());
    liveGamesFrame->setSizePolicy(sizePolicy9);
    liveGamesFrame->setAutoFillBackground(false);
    liveGamesFrame->setStyleSheet(QStringLiteral(""));
    livesgamesVLayout = new QVBoxLayout(liveGamesFrame);
    livesgamesVLayout->setSpacing(20);
    livesgamesVLayout->setObjectName(QStringLiteral("livesgamesVLayout"));
    livesgamesVLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    livesgamesVLayout->setContentsMargins(20, 20, 20, 20);
    liveGamesUpSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    livesgamesVLayout->addItem(liveGamesUpSpacer);

    livesGamesLabel = new QLabel(liveGamesFrame);
    livesGamesLabel->setObjectName(QStringLiteral("livesGamesLabel"));
    sizePolicy7.setHeightForWidth(livesGamesLabel->sizePolicy().hasHeightForWidth());
    livesGamesLabel->setSizePolicy(sizePolicy7);
    livesGamesLabel->setMinimumSize(QSize(0, 20));
    livesGamesLabel->setStyleSheet(QLatin1String("QLabel#livesGamesLabel{\n"
                                                 "	font: 10pt \"MS Shell Dlg 2\";\n"
                                                 "	color: rgb(7, 39, 51);\n"
                                                 "}"));
    livesGamesLabel->setAlignment(Qt::AlignCenter);

    livesgamesVLayout->addWidget(livesGamesLabel);

    UMPGroupBox = new QGroupBox(liveGamesFrame);
    UMPGroupBox->setObjectName(QStringLiteral("UMPGroupBox"));
    UMPGroupBox->setStyleSheet(QLatin1String("QGroupBox#UMPGroupBox{\n"
                                             "	border: 2px solid rgb(20, 125, 164);\n"
                                             "}"));
    UMPHLayout_2 = new QHBoxLayout(UMPGroupBox);
    UMPHLayout_2->setObjectName(QStringLiteral("UMPHLayout_2"));
    usernameUMPLabel = new QLabel(UMPGroupBox);
    usernameUMPLabel->setObjectName(QStringLiteral("usernameUMPLabel"));
    usernameUMPLabel->setAlignment(Qt::AlignCenter);

    UMPHLayout_2->addWidget(usernameUMPLabel);

    modeUMPLabel = new QLabel(UMPGroupBox);
    modeUMPLabel->setObjectName(QStringLiteral("modeUMPLabel"));
    modeUMPLabel->setAlignment(Qt::AlignCenter);

    UMPHLayout_2->addWidget(modeUMPLabel);

    playerNumberUMPLabel = new QLabel(UMPGroupBox);
    playerNumberUMPLabel->setObjectName(QStringLiteral("playerNumberUMPLabel"));
    playerNumberUMPLabel->setAlignment(Qt::AlignCenter);

    UMPHLayout_2->addWidget(playerNumberUMPLabel);

    livesgamesVLayout->addWidget(UMPGroupBox);

    liveGamesScrollArea = new QScrollArea(liveGamesFrame);
    liveGamesScrollArea->setObjectName(QStringLiteral("liveGamesScrollArea"));
    liveGamesScrollArea->setStyleSheet(QLatin1String("QScrollArea#livesgamesScrollArea {\n"
                                                     "	border: none;\n"
                                                     "}"));
    liveGamesScrollArea->setWidgetResizable(true);
    liveGamesScrollAreaWidgetContents = new QWidget();
    liveGamesScrollAreaWidgetContents->setObjectName(QStringLiteral("liveGamesScrollAreaWidgetContents"));
    liveGamesScrollAreaWidgetContents->setGeometry(QRect(0, 0, 482, 77));
    verticalLayout_4 = new QVBoxLayout(liveGamesScrollAreaWidgetContents);
    verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
    liveGamesScrollArea->setWidget(liveGamesScrollAreaWidgetContents);

    livesgamesVLayout->addWidget(liveGamesScrollArea);

    liveGamesDownSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    livesgamesVLayout->addItem(liveGamesDownSpacer);

    horizontalLayout_27->addWidget(liveGamesFrame);

    filtersFrame = new QFrame(joinGamePage);
    filtersFrame->setObjectName(QStringLiteral("filtersFrame"));
    sizePolicy6.setHeightForWidth(filtersFrame->sizePolicy().hasHeightForWidth());
    filtersFrame->setSizePolicy(sizePolicy6);
    filtersFrame->setStyleSheet(QLatin1String("background-color: rgb(196, 207, 218);\n"
                                              "border: 1px solid rgb(196, 207, 218);\n"
                                              "border-radius: 20;"));
    filtersFrame->setFrameShape(QFrame::StyledPanel);
    filtersFrame->setFrameShadow(QFrame::Raised);
    notificationsVLayout_2 = new QVBoxLayout(filtersFrame);
    notificationsVLayout_2->setObjectName(QStringLiteral("notificationsVLayout_2"));
    filtersGroupBox = new QGroupBox(filtersFrame);
    filtersGroupBox->setObjectName(QStringLiteral("filtersGroupBox"));
    filtersGroupBox->setStyleSheet(QLatin1String("QGroupBox#filtersGroupBox{\n"
                                                 "	border: 1px solid rgb(8, 76, 102);\n"
                                                 "	border-radius: 20px;\n"
                                                 "}"));
    verticalLayout_6 = new QVBoxLayout(filtersGroupBox);
    verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
    filtersPlayerNumberLabel = new QLabel(filtersGroupBox);
    filtersPlayerNumberLabel->setObjectName(QStringLiteral("filtersPlayerNumberLabel"));
    sizePolicy7.setHeightForWidth(filtersPlayerNumberLabel->sizePolicy().hasHeightForWidth());
    filtersPlayerNumberLabel->setSizePolicy(sizePolicy7);
    filtersPlayerNumberLabel->setMinimumSize(QSize(0, 31));
    filtersPlayerNumberLabel->setStyleSheet(QLatin1String("QLabel#playernumberLabel2{\n"
                                                          "	border: 1px solid rgb(8,76,102);\n"
                                                          "	color: rgb(7, 39, 51);\n"
                                                          "	border-radius: 3px;\n"
                                                          "}"));
    filtersPlayerNumberLabel->setTextFormat(Qt::AutoText);
    filtersPlayerNumberLabel->setScaledContents(false);
    filtersPlayerNumberLabel->setIndent(7);

    verticalLayout_6->addWidget(filtersPlayerNumberLabel);

    filtersNumberChoices = new QComboBox(filtersGroupBox);
    filtersNumberChoices->addItem(QString());
    filtersNumberChoices->addItem(QString());
    filtersNumberChoices->setObjectName(QStringLiteral("filtersNumberChoices"));
    sizePolicy7.setHeightForWidth(filtersNumberChoices->sizePolicy().hasHeightForWidth());
    filtersNumberChoices->setSizePolicy(sizePolicy7);
    filtersNumberChoices->setContextMenuPolicy(Qt::DefaultContextMenu);
    filtersNumberChoices->setStyleSheet(QLatin1String("QComboBox{background-color: transparent;}\n"
                                                      ""));
    filtersNumberChoices->setEditable(false);

    verticalLayout_6->addWidget(filtersNumberChoices);

    filterModeLabel = new QLabel(filtersGroupBox);
    filterModeLabel->setObjectName(QStringLiteral("filterModeLabel"));
    sizePolicy7.setHeightForWidth(filterModeLabel->sizePolicy().hasHeightForWidth());
    filterModeLabel->setSizePolicy(sizePolicy7);
    filterModeLabel->setMinimumSize(QSize(0, 31));
    filterModeLabel->setStyleSheet(QLatin1String("QLabel#gamemodeLabel2{\n"
                                                 "	border: 1px solid rgb(8,76,102);\n"
                                                 "	border-radius: 3px;\n"
                                                 "	color: rgb(7, 39, 51);\n"
                                                 "}"));
    filterModeLabel->setIndent(7);

    verticalLayout_6->addWidget(filterModeLabel);

    filtersModeChoices = new QComboBox(filtersGroupBox);
    filtersModeChoices->addItem(QString());
    filtersModeChoices->addItem(QString());
    filtersModeChoices->addItem(QString());
    filtersModeChoices->addItem(QString());
    filtersModeChoices->setObjectName(QStringLiteral("filtersModeChoices"));
    filtersModeChoices->setStyleSheet(QStringLiteral("background-color: transparent;"));

    verticalLayout_6->addWidget(filtersModeChoices);

    notificationsVLayout_2->addWidget(filtersGroupBox);

    horizontalLayout_27->addWidget(filtersFrame);

    gameMainStacked->addWidget(joinGamePage);

    horizontalLayout_4->addWidget(gameMainStacked);

    mainStacked->addWidget(gamePage);
    ingamePage = new QWidget();
    ingamePage->setObjectName(QStringLiteral("ingamePage"));
    horizontalLayout_33 = new QHBoxLayout(ingamePage);
    horizontalLayout_33->setSpacing(10);
    horizontalLayout_33->setObjectName(QStringLiteral("horizontalLayout_33"));
    horizontalLayout_33->setContentsMargins(0, 10, 0, 0);
    inGameSidebar = new QFrame(ingamePage);
    inGameSidebar->setObjectName(QStringLiteral("inGameSidebar"));
    sizePolicy6.setHeightForWidth(inGameSidebar->sizePolicy().hasHeightForWidth());
    inGameSidebar->setSizePolicy(sizePolicy6);
    inGameSidebar->setMinimumSize(QSize(0, 0));
    inGameSidebar->setStyleSheet(QLatin1String("QFrame{\n"
                                               "	background-color: rgb(196, 207, 218);\n"
                                               "}"));
    inGameSidebar->setFrameShape(QFrame::StyledPanel);
    inGameSidebar->setFrameShadow(QFrame::Raised);
    gamesideBarHLayout = new QVBoxLayout(inGameSidebar);
    gamesideBarHLayout->setObjectName(QStringLiteral("gamesideBarHLayout"));
    quitButtonUpSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gamesideBarHLayout->addItem(quitButtonUpSpacer);

    quitButton = new QPushButton(inGameSidebar);
    quitButton->setObjectName(QStringLiteral("quitButton"));
    quitButton->setStyleSheet(QLatin1String("QPushButton#quitButton{\n"
                                            "	color: rgb(255, 255, 255);\n"
                                            "	background-color: rgb(179, 38, 30);\n"
                                            "	border: 3px solid rgb(179, 38, 30);\n"
                                            "	border-radius: 5px;\n"
                                            "}\n"
                                            "\n"
                                            "QPushButton:hover#quitButton{\n"
                                            "	background-color: rgb(148, 31, 25);\n"
                                            "	border-color: rgb(148, 31,25);\n"
                                            "}\n"
                                            "\n"
                                            "QPushButton:pressed#quitButton{\n"
                                            "	border-top-color: rgb(167, 33, 28);\n"
                                            "	border-left-color: rgb(167, 33, 28);\n"
                                            "	border-bottom-color: rgb(127, 25, 21);\n"
                                            "	border-right-color: rgb(127, 25, 21);\n"
                                            "}"));

    gamesideBarHLayout->addWidget(quitButton);

    gameFlowBox = new QGroupBox(inGameSidebar);
    gameFlowBox->setObjectName(QStringLiteral("gameFlowBox"));
    gameFlowBox->setStyleSheet(QLatin1String("QGroupBox#gameFlowBox{\n"
                                             "	border: 1px solid rgb(8, 76, 102);\n"
                                             "	border-radius: 5px; \n"
                                             "}"));
    verticalLayout_8 = new QVBoxLayout(gameFlowBox);
    verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
    gameFlowLayout = new QHBoxLayout();
    gameFlowLayout->setObjectName(QStringLiteral("gameFlowLayout"));
    gameStatusLabel = new QLabel(gameFlowBox);
    gameStatusLabel->setObjectName(QStringLiteral("gameStatusLabel"));

    gameFlowLayout->addWidget(gameStatusLabel);

    playerTurnLabel = new QLabel(gameFlowBox);
    playerTurnLabel->setObjectName(QStringLiteral("playerTurnLabel"));

    gameFlowLayout->addWidget(playerTurnLabel);

    verticalLayout_8->addLayout(gameFlowLayout);

    gamesideBarHLayout->addWidget(gameFlowBox);

    gamesideBarHLayout->setStretch(0, 1);
    gamesideBarHLayout->setStretch(1, 1);

    horizontalLayout_33->addWidget(inGameSidebar);

    gameBoardFrame = new QFrame(ingamePage);
    gameBoardFrame->setObjectName(QStringLiteral("gameBoardFrame"));
    sizePolicy9.setHeightForWidth(gameBoardFrame->sizePolicy().hasHeightForWidth());
    gameBoardFrame->setSizePolicy(sizePolicy9);
    gameBoardFrame->setStyleSheet(QLatin1String("QFrame#gameBoardFrame{\n"
                                                "	border: 2px solid rgb(85, 68, 58);\n"
                                                "	background-color: rgb(85, 68, 58);\n"
                                                "	/*background-color: rgb(66, 53, 45);*/\n"
                                                "	border-radius: 8px;\n"
                                                "}"));
    gameBoardFrame->setFrameShape(QFrame::StyledPanel);
    gameBoardFrame->setFrameShadow(QFrame::Raised);
    boardGrid = new QGridLayout(gameBoardFrame);
    boardGrid->setSpacing(0);
    boardGrid->setObjectName(QStringLiteral("boardGrid"));
    boardGrid->setSizeConstraint(QLayout::SetDefaultConstraint);
    boardGrid->setContentsMargins(20, 20, 20, 20);
    r0c0 = new QLabel(gameBoardFrame);
    r0c0->setObjectName(QStringLiteral("r0c0"));
    sizePolicy4.setHeightForWidth(r0c0->sizePolicy().hasHeightForWidth());
    r0c0->setSizePolicy(sizePolicy4);
    r0c0->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r0c0->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r0c0, 0, 0, 1, 1);

    r0c1 = new QLabel(gameBoardFrame);
    r0c1->setObjectName(QStringLiteral("r0c1"));
    sizePolicy2.setHeightForWidth(r0c1->sizePolicy().hasHeightForWidth());
    r0c1->setSizePolicy(sizePolicy2);
    r0c1->setMinimumSize(QSize(15, 0));
    r0c1->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r0c1, 0, 1, 1, 1);

    r0c2 = new QLabel(gameBoardFrame);
    r0c2->setObjectName(QStringLiteral("r0c2"));
    r0c2->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r0c2->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r0c2, 0, 2, 1, 1);

    r0c3 = new QLabel(gameBoardFrame);
    r0c3->setObjectName(QStringLiteral("r0c3"));
    sizePolicy2.setHeightForWidth(r0c3->sizePolicy().hasHeightForWidth());
    r0c3->setSizePolicy(sizePolicy2);
    r0c3->setMinimumSize(QSize(15, 0));
    r0c3->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r0c3, 0, 3, 1, 1);

    r0c4 = new QLabel(gameBoardFrame);
    r0c4->setObjectName(QStringLiteral("r0c4"));
    r0c4->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r0c4->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r0c4, 0, 4, 1, 1);

    r0c5 = new QLabel(gameBoardFrame);
    r0c5->setObjectName(QStringLiteral("r0c5"));
    sizePolicy2.setHeightForWidth(r0c5->sizePolicy().hasHeightForWidth());
    r0c5->setSizePolicy(sizePolicy2);
    r0c5->setMinimumSize(QSize(15, 0));
    r0c5->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r0c5, 0, 5, 1, 1);

    r0c6 = new QLabel(gameBoardFrame);
    r0c6->setObjectName(QStringLiteral("r0c6"));
    r0c6->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r0c6->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r0c6, 0, 6, 1, 1);

    r0c7 = new QLabel(gameBoardFrame);
    r0c7->setObjectName(QStringLiteral("r0c7"));
    sizePolicy2.setHeightForWidth(r0c7->sizePolicy().hasHeightForWidth());
    r0c7->setSizePolicy(sizePolicy2);
    r0c7->setMinimumSize(QSize(15, 0));
    r0c7->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r0c7, 0, 7, 1, 1);

    r0c8 = new QLabel(gameBoardFrame);
    r0c8->setObjectName(QStringLiteral("r0c8"));
    r0c8->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r0c8->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r0c8, 0, 8, 1, 1);

    r0c9 = new QLabel(gameBoardFrame);
    r0c9->setObjectName(QStringLiteral("r0c9"));
    sizePolicy2.setHeightForWidth(r0c9->sizePolicy().hasHeightForWidth());
    r0c9->setSizePolicy(sizePolicy2);
    r0c9->setMinimumSize(QSize(15, 0));
    r0c9->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r0c9, 0, 9, 1, 1);

    r0c10 = new QLabel(gameBoardFrame);
    r0c10->setObjectName(QStringLiteral("r0c10"));
    r0c10->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r0c10->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r0c10, 0, 10, 1, 1);

    r0c11 = new QLabel(gameBoardFrame);
    r0c11->setObjectName(QStringLiteral("r0c11"));
    sizePolicy2.setHeightForWidth(r0c11->sizePolicy().hasHeightForWidth());
    r0c11->setSizePolicy(sizePolicy2);
    r0c11->setMinimumSize(QSize(15, 0));
    r0c11->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r0c11, 0, 11, 1, 1);

    r0c12 = new QLabel(gameBoardFrame);
    r0c12->setObjectName(QStringLiteral("r0c12"));
    r0c12->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r0c12->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r0c12, 0, 12, 1, 1);

    r0c13 = new QLabel(gameBoardFrame);
    r0c13->setObjectName(QStringLiteral("r0c13"));
    sizePolicy2.setHeightForWidth(r0c13->sizePolicy().hasHeightForWidth());
    r0c13->setSizePolicy(sizePolicy2);
    r0c13->setMinimumSize(QSize(15, 0));
    r0c13->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r0c13, 0, 13, 1, 1);

    r0c14 = new QLabel(gameBoardFrame);
    r0c14->setObjectName(QStringLiteral("r0c14"));
    sizePolicy4.setHeightForWidth(r0c14->sizePolicy().hasHeightForWidth());
    r0c14->setSizePolicy(sizePolicy4);
    r0c14->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r0c14->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r0c14, 0, 14, 1, 1);

    r0c15 = new QLabel(gameBoardFrame);
    r0c15->setObjectName(QStringLiteral("r0c15"));
    sizePolicy2.setHeightForWidth(r0c15->sizePolicy().hasHeightForWidth());
    r0c15->setSizePolicy(sizePolicy2);
    r0c15->setMinimumSize(QSize(15, 0));
    r0c15->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r0c15, 0, 15, 1, 1);

    r0c16 = new QLabel(gameBoardFrame);
    r0c16->setObjectName(QStringLiteral("r0c16"));
    r0c16->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r0c16->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r0c16, 0, 16, 1, 1);

    r1c0 = new QLabel(gameBoardFrame);
    r1c0->setObjectName(QStringLiteral("r1c0"));
    r1c0->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c0, 1, 0, 1, 1);

    r1c1 = new QLabel(gameBoardFrame);
    r1c1->setObjectName(QStringLiteral("r1c1"));
    r1c1->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c1, 1, 1, 1, 1);

    r1c2 = new QLabel(gameBoardFrame);
    r1c2->setObjectName(QStringLiteral("r1c2"));
    r1c2->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c2, 1, 2, 1, 1);

    r1c3 = new QLabel(gameBoardFrame);
    r1c3->setObjectName(QStringLiteral("r1c3"));
    r1c3->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c3, 1, 3, 1, 1);

    r1c4 = new QLabel(gameBoardFrame);
    r1c4->setObjectName(QStringLiteral("r1c4"));
    r1c4->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c4, 1, 4, 1, 1);

    r1c5 = new QLabel(gameBoardFrame);
    r1c5->setObjectName(QStringLiteral("r1c5"));
    r1c5->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c5, 1, 5, 1, 1);

    r1c6 = new QLabel(gameBoardFrame);
    r1c6->setObjectName(QStringLiteral("r1c6"));
    r1c6->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c6, 1, 6, 1, 1);

    r1c7 = new QLabel(gameBoardFrame);
    r1c7->setObjectName(QStringLiteral("r1c7"));
    r1c7->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c7, 1, 7, 1, 1);

    r1c8 = new QLabel(gameBoardFrame);
    r1c8->setObjectName(QStringLiteral("r1c8"));
    r1c8->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c8, 1, 8, 1, 1);

    r1c9 = new QLabel(gameBoardFrame);
    r1c9->setObjectName(QStringLiteral("r1c9"));
    r1c9->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c9, 1, 9, 1, 1);

    r1c11 = new QLabel(gameBoardFrame);
    r1c11->setObjectName(QStringLiteral("r1c11"));
    r1c11->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c11, 1, 11, 1, 1);

    r1c12 = new QLabel(gameBoardFrame);
    r1c12->setObjectName(QStringLiteral("r1c12"));
    r1c12->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c12, 1, 12, 1, 1);

    r1c13 = new QLabel(gameBoardFrame);
    r1c13->setObjectName(QStringLiteral("r1c13"));
    r1c13->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c13, 1, 13, 1, 1);

    r1c14 = new QLabel(gameBoardFrame);
    r1c14->setObjectName(QStringLiteral("r1c14"));
    r1c14->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c14, 1, 14, 1, 1);

    r1c15 = new QLabel(gameBoardFrame);
    r1c15->setObjectName(QStringLiteral("r1c15"));
    r1c15->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c15, 1, 15, 1, 1);

    r1c16 = new QLabel(gameBoardFrame);
    r1c16->setObjectName(QStringLiteral("r1c16"));
    r1c16->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c16, 1, 16, 1, 1);

    r2c0 = new QLabel(gameBoardFrame);
    r2c0->setObjectName(QStringLiteral("r2c0"));
    r2c0->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r2c0->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r2c0, 2, 0, 1, 1);

    r2c1 = new QLabel(gameBoardFrame);
    r2c1->setObjectName(QStringLiteral("r2c1"));
    r2c1->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r2c1, 2, 1, 1, 1);

    r2c2 = new QLabel(gameBoardFrame);
    r2c2->setObjectName(QStringLiteral("r2c2"));
    r2c2->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r2c2->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r2c2, 2, 2, 1, 1);

    r2c3 = new QLabel(gameBoardFrame);
    r2c3->setObjectName(QStringLiteral("r2c3"));

    boardGrid->addWidget(r2c3, 2, 3, 1, 1);

    r2c4 = new QLabel(gameBoardFrame);
    r2c4->setObjectName(QStringLiteral("r2c4"));
    r2c4->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r2c4->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r2c4, 2, 4, 1, 1);

    r2c5 = new QLabel(gameBoardFrame);
    r2c5->setObjectName(QStringLiteral("r2c5"));

    boardGrid->addWidget(r2c5, 2, 5, 1, 1);

    r2c6 = new QLabel(gameBoardFrame);
    r2c6->setObjectName(QStringLiteral("r2c6"));
    r2c6->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r2c6->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r2c6, 2, 6, 1, 1);

    r2c7 = new QLabel(gameBoardFrame);
    r2c7->setObjectName(QStringLiteral("r2c7"));

    boardGrid->addWidget(r2c7, 2, 7, 1, 1);

    r2c8 = new QLabel(gameBoardFrame);
    r2c8->setObjectName(QStringLiteral("r2c8"));
    r2c8->setMouseTracking(false);
    r2c8->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r2c8->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r2c8, 2, 8, 1, 1);

    r2c9 = new QLabel(gameBoardFrame);
    r2c9->setObjectName(QStringLiteral("r2c9"));

    boardGrid->addWidget(r2c9, 2, 9, 1, 1);

    r2c10 = new QLabel(gameBoardFrame);
    r2c10->setObjectName(QStringLiteral("r2c10"));
    r2c10->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r2c10->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r2c10, 2, 10, 1, 1);

    r2c11 = new QLabel(gameBoardFrame);
    r2c11->setObjectName(QStringLiteral("r2c11"));

    boardGrid->addWidget(r2c11, 2, 11, 1, 1);

    r2c12 = new QLabel(gameBoardFrame);
    r2c12->setObjectName(QStringLiteral("r2c12"));
    r2c12->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r2c12->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r2c12, 2, 12, 1, 1);

    r2c13 = new QLabel(gameBoardFrame);
    r2c13->setObjectName(QStringLiteral("r2c13"));

    boardGrid->addWidget(r2c13, 2, 13, 1, 1);

    r2c14 = new QLabel(gameBoardFrame);
    r2c14->setObjectName(QStringLiteral("r2c14"));
    r2c14->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r2c14->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r2c14, 2, 14, 1, 1);

    r2c15 = new QLabel(gameBoardFrame);
    r2c15->setObjectName(QStringLiteral("r2c15"));

    boardGrid->addWidget(r2c15, 2, 15, 1, 1);

    r2c16 = new QLabel(gameBoardFrame);
    r2c16->setObjectName(QStringLiteral("r2c16"));
    r2c16->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r2c16->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r2c16, 2, 16, 1, 1);

    r3c0 = new QLabel(gameBoardFrame);
    r3c0->setObjectName(QStringLiteral("r3c0"));
    r3c0->setStyleSheet(QStringLiteral(""));
    r3c0->setFrameShape(QFrame::NoFrame);

    boardGrid->addWidget(r3c0, 3, 0, 1, 1);

    r3c1 = new QLabel(gameBoardFrame);
    r3c1->setObjectName(QStringLiteral("r3c1"));

    boardGrid->addWidget(r3c1, 3, 1, 1, 1);

    r3c2 = new QLabel(gameBoardFrame);
    r3c2->setObjectName(QStringLiteral("r3c2"));

    boardGrid->addWidget(r3c2, 3, 2, 1, 1);

    r3c3 = new QLabel(gameBoardFrame);
    r3c3->setObjectName(QStringLiteral("r3c3"));

    boardGrid->addWidget(r3c3, 3, 3, 1, 1);

    r3c4 = new QLabel(gameBoardFrame);
    r3c4->setObjectName(QStringLiteral("r3c4"));

    boardGrid->addWidget(r3c4, 3, 4, 1, 1);

    r3c5 = new QLabel(gameBoardFrame);
    r3c5->setObjectName(QStringLiteral("r3c5"));

    boardGrid->addWidget(r3c5, 3, 5, 1, 1);

    r3c6 = new QLabel(gameBoardFrame);
    r3c6->setObjectName(QStringLiteral("r3c6"));

    boardGrid->addWidget(r3c6, 3, 6, 1, 1);

    r3c7 = new QLabel(gameBoardFrame);
    r3c7->setObjectName(QStringLiteral("r3c7"));

    boardGrid->addWidget(r3c7, 3, 7, 1, 1);

    r3c8 = new QLabel(gameBoardFrame);
    r3c8->setObjectName(QStringLiteral("r3c8"));

    boardGrid->addWidget(r3c8, 3, 8, 1, 1);

    r3c9 = new QLabel(gameBoardFrame);
    r3c9->setObjectName(QStringLiteral("r3c9"));

    boardGrid->addWidget(r3c9, 3, 9, 1, 1);

    r3c10 = new QLabel(gameBoardFrame);
    r3c10->setObjectName(QStringLiteral("r3c10"));

    boardGrid->addWidget(r3c10, 3, 10, 1, 1);

    r3c11 = new QLabel(gameBoardFrame);
    r3c11->setObjectName(QStringLiteral("r3c11"));

    boardGrid->addWidget(r3c11, 3, 11, 1, 1);

    r3c12 = new QLabel(gameBoardFrame);
    r3c12->setObjectName(QStringLiteral("r3c12"));

    boardGrid->addWidget(r3c12, 3, 12, 1, 1);

    r3c13 = new QLabel(gameBoardFrame);
    r3c13->setObjectName(QStringLiteral("r3c13"));

    boardGrid->addWidget(r3c13, 3, 13, 1, 1);

    r3c14 = new QLabel(gameBoardFrame);
    r3c14->setObjectName(QStringLiteral("r3c14"));

    boardGrid->addWidget(r3c14, 3, 14, 1, 1);

    r3c15 = new QLabel(gameBoardFrame);
    r3c15->setObjectName(QStringLiteral("r3c15"));

    boardGrid->addWidget(r3c15, 3, 15, 1, 1);

    r3c16 = new QLabel(gameBoardFrame);
    r3c16->setObjectName(QStringLiteral("r3c16"));

    boardGrid->addWidget(r3c16, 3, 16, 1, 1);

    r4c0 = new QLabel(gameBoardFrame);
    r4c0->setObjectName(QStringLiteral("r4c0"));
    r4c0->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r4c0->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r4c0, 4, 0, 1, 1);

    r4c1 = new QLabel(gameBoardFrame);
    r4c1->setObjectName(QStringLiteral("r4c1"));

    boardGrid->addWidget(r4c1, 4, 1, 1, 1);

    r4c2 = new QLabel(gameBoardFrame);
    r4c2->setObjectName(QStringLiteral("r4c2"));
    r4c2->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r4c2->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r4c2, 4, 2, 1, 1);

    r4c3 = new QLabel(gameBoardFrame);
    r4c3->setObjectName(QStringLiteral("r4c3"));

    boardGrid->addWidget(r4c3, 4, 3, 1, 1);

    r4c4 = new QLabel(gameBoardFrame);
    r4c4->setObjectName(QStringLiteral("r4c4"));
    r4c4->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r4c4->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r4c4, 4, 4, 1, 1);

    r4c5 = new QLabel(gameBoardFrame);
    r4c5->setObjectName(QStringLiteral("r4c5"));

    boardGrid->addWidget(r4c5, 4, 5, 1, 1);

    r4c6 = new QLabel(gameBoardFrame);
    r4c6->setObjectName(QStringLiteral("r4c6"));
    r4c6->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r4c6->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r4c6, 4, 6, 1, 1);

    r4c7 = new QLabel(gameBoardFrame);
    r4c7->setObjectName(QStringLiteral("r4c7"));

    boardGrid->addWidget(r4c7, 4, 7, 1, 1);

    r4c8 = new QLabel(gameBoardFrame);
    r4c8->setObjectName(QStringLiteral("r4c8"));
    r4c8->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r4c8->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r4c8, 4, 8, 1, 1);

    r4c9 = new QLabel(gameBoardFrame);
    r4c9->setObjectName(QStringLiteral("r4c9"));

    boardGrid->addWidget(r4c9, 4, 9, 1, 1);

    r4c10 = new QLabel(gameBoardFrame);
    r4c10->setObjectName(QStringLiteral("r4c10"));
    r4c10->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r4c10->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r4c10, 4, 10, 1, 1);

    r4c11 = new QLabel(gameBoardFrame);
    r4c11->setObjectName(QStringLiteral("r4c11"));

    boardGrid->addWidget(r4c11, 4, 11, 1, 1);

    r4c12 = new QLabel(gameBoardFrame);
    r4c12->setObjectName(QStringLiteral("r4c12"));
    r4c12->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r4c12->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r4c12, 4, 12, 1, 1);

    r4c13 = new QLabel(gameBoardFrame);
    r4c13->setObjectName(QStringLiteral("r4c13"));

    boardGrid->addWidget(r4c13, 4, 13, 1, 1);

    r4c14 = new QLabel(gameBoardFrame);
    r4c14->setObjectName(QStringLiteral("r4c14"));
    r4c14->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r4c14->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r4c14, 4, 14, 1, 1);

    r4c15 = new QLabel(gameBoardFrame);
    r4c15->setObjectName(QStringLiteral("r4c15"));

    boardGrid->addWidget(r4c15, 4, 15, 1, 1);

    r4c16 = new QLabel(gameBoardFrame);
    r4c16->setObjectName(QStringLiteral("r4c16"));
    r4c16->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r4c16->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r4c16, 4, 16, 1, 1);

    r5c0 = new QLabel(gameBoardFrame);
    r5c0->setObjectName(QStringLiteral("r5c0"));
    r5c0->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r5c0, 5, 0, 1, 1);

    r5c1 = new QLabel(gameBoardFrame);
    r5c1->setObjectName(QStringLiteral("r5c1"));
    r5c1->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r5c1, 5, 1, 1, 1);

    r5c2 = new QLabel(gameBoardFrame);
    r5c2->setObjectName(QStringLiteral("r5c2"));
    r5c2->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r5c2, 5, 2, 1, 1);

    r5c3 = new QLabel(gameBoardFrame);
    r5c3->setObjectName(QStringLiteral("r5c3"));

    boardGrid->addWidget(r5c3, 5, 3, 1, 1);

    r5c4 = new QLabel(gameBoardFrame);
    r5c4->setObjectName(QStringLiteral("r5c4"));

    boardGrid->addWidget(r5c4, 5, 4, 1, 1);

    r5c5 = new QLabel(gameBoardFrame);
    r5c5->setObjectName(QStringLiteral("r5c5"));

    boardGrid->addWidget(r5c5, 5, 5, 1, 1);

    r5c6 = new QLabel(gameBoardFrame);
    r5c6->setObjectName(QStringLiteral("r5c6"));

    boardGrid->addWidget(r5c6, 5, 6, 1, 1);

    r5c7 = new QLabel(gameBoardFrame);
    r5c7->setObjectName(QStringLiteral("r5c7"));

    boardGrid->addWidget(r5c7, 5, 7, 1, 1);

    r5c8 = new QLabel(gameBoardFrame);
    r5c8->setObjectName(QStringLiteral("r5c8"));

    boardGrid->addWidget(r5c8, 5, 8, 1, 1);

    r5c9 = new QLabel(gameBoardFrame);
    r5c9->setObjectName(QStringLiteral("r5c9"));

    boardGrid->addWidget(r5c9, 5, 9, 1, 1);

    r5c10 = new QLabel(gameBoardFrame);
    r5c10->setObjectName(QStringLiteral("r5c10"));

    boardGrid->addWidget(r5c10, 5, 10, 1, 1);

    r5c11 = new QLabel(gameBoardFrame);
    r5c11->setObjectName(QStringLiteral("r5c11"));

    boardGrid->addWidget(r5c11, 5, 11, 1, 1);

    r5c12 = new QLabel(gameBoardFrame);
    r5c12->setObjectName(QStringLiteral("r5c12"));

    boardGrid->addWidget(r5c12, 5, 12, 1, 1);

    r5c13 = new QLabel(gameBoardFrame);
    r5c13->setObjectName(QStringLiteral("r5c13"));

    boardGrid->addWidget(r5c13, 5, 13, 1, 1);

    r5c14 = new QLabel(gameBoardFrame);
    r5c14->setObjectName(QStringLiteral("r5c14"));

    boardGrid->addWidget(r5c14, 5, 14, 1, 1);

    r5c15 = new QLabel(gameBoardFrame);
    r5c15->setObjectName(QStringLiteral("r5c15"));

    boardGrid->addWidget(r5c15, 5, 15, 1, 1);

    r5c16 = new QLabel(gameBoardFrame);
    r5c16->setObjectName(QStringLiteral("r5c16"));

    boardGrid->addWidget(r5c16, 5, 16, 1, 1);

    r6c0 = new QLabel(gameBoardFrame);
    r6c0->setObjectName(QStringLiteral("r6c0"));
    r6c0->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r6c0->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r6c0, 6, 0, 1, 1);

    r6c1 = new QLabel(gameBoardFrame);
    r6c1->setObjectName(QStringLiteral("r6c1"));

    boardGrid->addWidget(r6c1, 6, 1, 1, 1);

    r6c2 = new QLabel(gameBoardFrame);
    r6c2->setObjectName(QStringLiteral("r6c2"));
    r6c2->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r6c2->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r6c2, 6, 2, 1, 1);

    r6c3 = new QLabel(gameBoardFrame);
    r6c3->setObjectName(QStringLiteral("r6c3"));

    boardGrid->addWidget(r6c3, 6, 3, 1, 1);

    r6c4 = new QLabel(gameBoardFrame);
    r6c4->setObjectName(QStringLiteral("r6c4"));
    r6c4->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r6c4->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r6c4, 6, 4, 1, 1);

    r6c5 = new QLabel(gameBoardFrame);
    r6c5->setObjectName(QStringLiteral("r6c5"));

    boardGrid->addWidget(r6c5, 6, 5, 1, 1);

    r6c6 = new QLabel(gameBoardFrame);
    r6c6->setObjectName(QStringLiteral("r6c6"));
    r6c6->setEnabled(true);
    r6c6->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r6c6->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r6c6, 6, 6, 1, 1);

    r6c7 = new QLabel(gameBoardFrame);
    r6c7->setObjectName(QStringLiteral("r6c7"));

    boardGrid->addWidget(r6c7, 6, 7, 1, 1);

    r6c8 = new QLabel(gameBoardFrame);
    r6c8->setObjectName(QStringLiteral("r6c8"));
    r6c8->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r6c8->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r6c8, 6, 8, 1, 1);

    r6c9 = new QLabel(gameBoardFrame);
    r6c9->setObjectName(QStringLiteral("r6c9"));

    boardGrid->addWidget(r6c9, 6, 9, 1, 1);

    r6c10 = new QLabel(gameBoardFrame);
    r6c10->setObjectName(QStringLiteral("r6c10"));
    r6c10->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r6c10->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r6c10, 6, 10, 1, 1);

    r6c11 = new QLabel(gameBoardFrame);
    r6c11->setObjectName(QStringLiteral("r6c11"));

    boardGrid->addWidget(r6c11, 6, 11, 1, 1);

    r6c12 = new QLabel(gameBoardFrame);
    r6c12->setObjectName(QStringLiteral("r6c12"));
    r6c12->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r6c12->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r6c12, 6, 12, 1, 1);

    r6c13 = new QLabel(gameBoardFrame);
    r6c13->setObjectName(QStringLiteral("r6c13"));

    boardGrid->addWidget(r6c13, 6, 13, 1, 1);

    r6c14 = new QLabel(gameBoardFrame);
    r6c14->setObjectName(QStringLiteral("r6c14"));
    r6c14->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r6c14->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r6c14, 6, 14, 1, 1);

    r6c15 = new QLabel(gameBoardFrame);
    r6c15->setObjectName(QStringLiteral("r6c15"));

    boardGrid->addWidget(r6c15, 6, 15, 1, 1);

    r6c16 = new QLabel(gameBoardFrame);
    r6c16->setObjectName(QStringLiteral("r6c16"));
    r6c16->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r6c16->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r6c16, 6, 16, 1, 1);

    r7c0 = new QLabel(gameBoardFrame);
    r7c0->setObjectName(QStringLiteral("r7c0"));

    boardGrid->addWidget(r7c0, 7, 0, 1, 1);

    r7c1 = new QLabel(gameBoardFrame);
    r7c1->setObjectName(QStringLiteral("r7c1"));

    boardGrid->addWidget(r7c1, 7, 1, 1, 1);

    r7c2 = new QLabel(gameBoardFrame);
    r7c2->setObjectName(QStringLiteral("r7c2"));

    boardGrid->addWidget(r7c2, 7, 2, 1, 1);

    r7c3 = new QLabel(gameBoardFrame);
    r7c3->setObjectName(QStringLiteral("r7c3"));

    boardGrid->addWidget(r7c3, 7, 3, 1, 1);

    r74 = new QLabel(gameBoardFrame);
    r74->setObjectName(QStringLiteral("r74"));

    boardGrid->addWidget(r74, 7, 4, 1, 1);

    r7c5 = new QLabel(gameBoardFrame);
    r7c5->setObjectName(QStringLiteral("r7c5"));

    boardGrid->addWidget(r7c5, 7, 5, 1, 1);

    r7c6 = new QLabel(gameBoardFrame);
    r7c6->setObjectName(QStringLiteral("r7c6"));

    boardGrid->addWidget(r7c6, 7, 6, 1, 1);

    r7c7 = new QLabel(gameBoardFrame);
    r7c7->setObjectName(QStringLiteral("r7c7"));

    boardGrid->addWidget(r7c7, 7, 7, 1, 1);

    r7c8 = new QLabel(gameBoardFrame);
    r7c8->setObjectName(QStringLiteral("r7c8"));

    boardGrid->addWidget(r7c8, 7, 8, 1, 1);

    r7c9 = new QLabel(gameBoardFrame);
    r7c9->setObjectName(QStringLiteral("r7c9"));

    boardGrid->addWidget(r7c9, 7, 9, 1, 1);

    r7c10 = new QLabel(gameBoardFrame);
    r7c10->setObjectName(QStringLiteral("r7c10"));

    boardGrid->addWidget(r7c10, 7, 10, 1, 1);

    r7c11 = new QLabel(gameBoardFrame);
    r7c11->setObjectName(QStringLiteral("r7c11"));

    boardGrid->addWidget(r7c11, 7, 11, 1, 1);

    r7c12 = new QLabel(gameBoardFrame);
    r7c12->setObjectName(QStringLiteral("r7c12"));

    boardGrid->addWidget(r7c12, 7, 12, 1, 1);

    rc13 = new QLabel(gameBoardFrame);
    rc13->setObjectName(QStringLiteral("rc13"));

    boardGrid->addWidget(rc13, 7, 13, 1, 1);

    r7c14 = new QLabel(gameBoardFrame);
    r7c14->setObjectName(QStringLiteral("r7c14"));

    boardGrid->addWidget(r7c14, 7, 14, 1, 1);

    r7c15 = new QLabel(gameBoardFrame);
    r7c15->setObjectName(QStringLiteral("r7c15"));

    boardGrid->addWidget(r7c15, 7, 15, 1, 1);

    r7c16 = new QLabel(gameBoardFrame);
    r7c16->setObjectName(QStringLiteral("r7c16"));

    boardGrid->addWidget(r7c16, 7, 16, 1, 1);

    r8c0 = new QLabel(gameBoardFrame);
    r8c0->setObjectName(QStringLiteral("r8c0"));
    r8c0->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r8c0->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r8c0, 8, 0, 1, 1);

    r8c1 = new QLabel(gameBoardFrame);
    r8c1->setObjectName(QStringLiteral("r8c1"));

    boardGrid->addWidget(r8c1, 8, 1, 1, 1);

    r8c2 = new QLabel(gameBoardFrame);
    r8c2->setObjectName(QStringLiteral("r8c2"));
    r8c2->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r8c2->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r8c2, 8, 2, 1, 1);

    r8c3 = new QLabel(gameBoardFrame);
    r8c3->setObjectName(QStringLiteral("r8c3"));

    boardGrid->addWidget(r8c3, 8, 3, 1, 1);

    r8c4 = new QLabel(gameBoardFrame);
    r8c4->setObjectName(QStringLiteral("r8c4"));
    r8c4->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r8c4->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r8c4, 8, 4, 1, 1);

    r8c5 = new QLabel(gameBoardFrame);
    r8c5->setObjectName(QStringLiteral("r8c5"));

    boardGrid->addWidget(r8c5, 8, 5, 1, 1);

    r8c6 = new QLabel(gameBoardFrame);
    r8c6->setObjectName(QStringLiteral("r8c6"));
    r8c6->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r8c6->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r8c6, 8, 6, 1, 1);

    r8c7 = new QLabel(gameBoardFrame);
    r8c7->setObjectName(QStringLiteral("r8c7"));

    boardGrid->addWidget(r8c7, 8, 7, 1, 1);

    r8c8 = new QLabel(gameBoardFrame);
    r8c8->setObjectName(QStringLiteral("r8c8"));
    r8c8->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r8c8->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r8c8, 8, 8, 1, 1);

    r8c9 = new QLabel(gameBoardFrame);
    r8c9->setObjectName(QStringLiteral("r8c9"));

    boardGrid->addWidget(r8c9, 8, 9, 1, 1);

    r8c10 = new QLabel(gameBoardFrame);
    r8c10->setObjectName(QStringLiteral("r8c10"));
    r8c10->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r8c10->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r8c10, 8, 10, 1, 1);

    r8c11 = new QLabel(gameBoardFrame);
    r8c11->setObjectName(QStringLiteral("r8c11"));

    boardGrid->addWidget(r8c11, 8, 11, 1, 1);

    r8c12 = new QLabel(gameBoardFrame);
    r8c12->setObjectName(QStringLiteral("r8c12"));
    r8c12->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r8c12->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r8c12, 8, 12, 1, 1);

    r8c13 = new QLabel(gameBoardFrame);
    r8c13->setObjectName(QStringLiteral("r8c13"));

    boardGrid->addWidget(r8c13, 8, 13, 1, 1);

    r8c14 = new QLabel(gameBoardFrame);
    r8c14->setObjectName(QStringLiteral("r8c14"));
    r8c14->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r8c14->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r8c14, 8, 14, 1, 1);

    r8c15 = new QLabel(gameBoardFrame);
    r8c15->setObjectName(QStringLiteral("r8c15"));

    boardGrid->addWidget(r8c15, 8, 15, 1, 1);

    r8c16 = new QLabel(gameBoardFrame);
    r8c16->setObjectName(QStringLiteral("r8c16"));
    r8c16->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r8c16->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r8c16, 8, 16, 1, 1);

    r9c0 = new QLabel(gameBoardFrame);
    r9c0->setObjectName(QStringLiteral("r9c0"));

    boardGrid->addWidget(r9c0, 9, 0, 1, 1);

    r9c1 = new QLabel(gameBoardFrame);
    r9c1->setObjectName(QStringLiteral("r9c1"));

    boardGrid->addWidget(r9c1, 9, 1, 1, 1);

    r9c2 = new QLabel(gameBoardFrame);
    r9c2->setObjectName(QStringLiteral("r9c2"));

    boardGrid->addWidget(r9c2, 9, 2, 1, 1);

    r9c3 = new QLabel(gameBoardFrame);
    r9c3->setObjectName(QStringLiteral("r9c3"));

    boardGrid->addWidget(r9c3, 9, 3, 1, 1);

    r9c4 = new QLabel(gameBoardFrame);
    r9c4->setObjectName(QStringLiteral("r9c4"));

    boardGrid->addWidget(r9c4, 9, 4, 1, 1);

    r9c5 = new QLabel(gameBoardFrame);
    r9c5->setObjectName(QStringLiteral("r9c5"));

    boardGrid->addWidget(r9c5, 9, 5, 1, 1);

    r9c6 = new QLabel(gameBoardFrame);
    r9c6->setObjectName(QStringLiteral("r9c6"));

    boardGrid->addWidget(r9c6, 9, 6, 1, 1);

    r9c7 = new QLabel(gameBoardFrame);
    r9c7->setObjectName(QStringLiteral("r9c7"));

    boardGrid->addWidget(r9c7, 9, 7, 1, 1);

    r9c8 = new QLabel(gameBoardFrame);
    r9c8->setObjectName(QStringLiteral("r9c8"));

    boardGrid->addWidget(r9c8, 9, 8, 1, 1);

    r9c9 = new QLabel(gameBoardFrame);
    r9c9->setObjectName(QStringLiteral("r9c9"));

    boardGrid->addWidget(r9c9, 9, 9, 1, 1);

    r9c10 = new QLabel(gameBoardFrame);
    r9c10->setObjectName(QStringLiteral("r9c10"));

    boardGrid->addWidget(r9c10, 9, 10, 1, 1);

    r9c11 = new QLabel(gameBoardFrame);
    r9c11->setObjectName(QStringLiteral("r9c11"));

    boardGrid->addWidget(r9c11, 9, 11, 1, 1);

    r9c12 = new QLabel(gameBoardFrame);
    r9c12->setObjectName(QStringLiteral("r9c12"));

    boardGrid->addWidget(r9c12, 9, 12, 1, 1);

    r9c14 = new QLabel(gameBoardFrame);
    r9c14->setObjectName(QStringLiteral("r9c14"));

    boardGrid->addWidget(r9c14, 9, 13, 1, 1);

    r9c16_2 = new QLabel(gameBoardFrame);
    r9c16_2->setObjectName(QStringLiteral("r9c16_2"));

    boardGrid->addWidget(r9c16_2, 9, 14, 1, 1);

    r9c15 = new QLabel(gameBoardFrame);
    r9c15->setObjectName(QStringLiteral("r9c15"));

    boardGrid->addWidget(r9c15, 9, 15, 1, 1);

    r9c16 = new QLabel(gameBoardFrame);
    r9c16->setObjectName(QStringLiteral("r9c16"));

    boardGrid->addWidget(r9c16, 9, 16, 1, 1);

    r10c0 = new QLabel(gameBoardFrame);
    r10c0->setObjectName(QStringLiteral("r10c0"));
    r10c0->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r10c0->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r10c0, 10, 0, 1, 1);

    r10c1 = new QLabel(gameBoardFrame);
    r10c1->setObjectName(QStringLiteral("r10c1"));

    boardGrid->addWidget(r10c1, 10, 1, 1, 1);

    r10c2 = new QLabel(gameBoardFrame);
    r10c2->setObjectName(QStringLiteral("r10c2"));
    r10c2->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r10c2->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r10c2, 10, 2, 1, 1);

    r10c3 = new QLabel(gameBoardFrame);
    r10c3->setObjectName(QStringLiteral("r10c3"));

    boardGrid->addWidget(r10c3, 10, 3, 1, 1);

    r10c4 = new QLabel(gameBoardFrame);
    r10c4->setObjectName(QStringLiteral("r10c4"));
    r10c4->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r10c4->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r10c4, 10, 4, 1, 1);

    r10c5 = new QLabel(gameBoardFrame);
    r10c5->setObjectName(QStringLiteral("r10c5"));

    boardGrid->addWidget(r10c5, 10, 5, 1, 1);

    r10c6 = new QLabel(gameBoardFrame);
    r10c6->setObjectName(QStringLiteral("r10c6"));
    r10c6->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r10c6->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r10c6, 10, 6, 1, 1);

    r10c7 = new QLabel(gameBoardFrame);
    r10c7->setObjectName(QStringLiteral("r10c7"));

    boardGrid->addWidget(r10c7, 10, 7, 1, 1);

    r10c8 = new QLabel(gameBoardFrame);
    r10c8->setObjectName(QStringLiteral("r10c8"));
    r10c8->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r10c8->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r10c8, 10, 8, 1, 1);

    r10c9 = new QLabel(gameBoardFrame);
    r10c9->setObjectName(QStringLiteral("r10c9"));

    boardGrid->addWidget(r10c9, 10, 9, 1, 1);

    r10c10 = new QLabel(gameBoardFrame);
    r10c10->setObjectName(QStringLiteral("r10c10"));
    r10c10->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r10c10->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r10c10, 10, 10, 1, 1);

    r10c11 = new QLabel(gameBoardFrame);
    r10c11->setObjectName(QStringLiteral("r10c11"));

    boardGrid->addWidget(r10c11, 10, 11, 1, 1);

    r10c12 = new QLabel(gameBoardFrame);
    r10c12->setObjectName(QStringLiteral("r10c12"));
    r10c12->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r10c12->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r10c12, 10, 12, 1, 1);

    r10c13 = new QLabel(gameBoardFrame);
    r10c13->setObjectName(QStringLiteral("r10c13"));

    boardGrid->addWidget(r10c13, 10, 13, 1, 1);

    r10c14 = new QLabel(gameBoardFrame);
    r10c14->setObjectName(QStringLiteral("r10c14"));
    r10c14->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r10c14->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r10c14, 10, 14, 1, 1);

    r10c15 = new QLabel(gameBoardFrame);
    r10c15->setObjectName(QStringLiteral("r10c15"));

    boardGrid->addWidget(r10c15, 10, 15, 1, 1);

    r10c16 = new QLabel(gameBoardFrame);
    r10c16->setObjectName(QStringLiteral("r10c16"));
    r10c16->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r10c16->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r10c16, 10, 16, 1, 1);

    r11c0 = new QLabel(gameBoardFrame);
    r11c0->setObjectName(QStringLiteral("r11c0"));

    boardGrid->addWidget(r11c0, 11, 0, 1, 1);

    r11c1 = new QLabel(gameBoardFrame);
    r11c1->setObjectName(QStringLiteral("r11c1"));

    boardGrid->addWidget(r11c1, 11, 1, 1, 1);

    r11c2 = new QLabel(gameBoardFrame);
    r11c2->setObjectName(QStringLiteral("r11c2"));

    boardGrid->addWidget(r11c2, 11, 2, 1, 1);

    r11c3 = new QLabel(gameBoardFrame);
    r11c3->setObjectName(QStringLiteral("r11c3"));

    boardGrid->addWidget(r11c3, 11, 3, 1, 1);

    r11c4 = new QLabel(gameBoardFrame);
    r11c4->setObjectName(QStringLiteral("r11c4"));

    boardGrid->addWidget(r11c4, 11, 4, 1, 1);

    r11c5 = new QLabel(gameBoardFrame);
    r11c5->setObjectName(QStringLiteral("r11c5"));

    boardGrid->addWidget(r11c5, 11, 5, 1, 1);

    r11c6 = new QLabel(gameBoardFrame);
    r11c6->setObjectName(QStringLiteral("r11c6"));

    boardGrid->addWidget(r11c6, 11, 6, 1, 1);

    r11c7 = new QLabel(gameBoardFrame);
    r11c7->setObjectName(QStringLiteral("r11c7"));

    boardGrid->addWidget(r11c7, 11, 7, 1, 1);

    r11c8 = new QLabel(gameBoardFrame);
    r11c8->setObjectName(QStringLiteral("r11c8"));

    boardGrid->addWidget(r11c8, 11, 8, 1, 1);

    r11c9 = new QLabel(gameBoardFrame);
    r11c9->setObjectName(QStringLiteral("r11c9"));

    boardGrid->addWidget(r11c9, 11, 9, 1, 1);

    r11c10 = new QLabel(gameBoardFrame);
    r11c10->setObjectName(QStringLiteral("r11c10"));

    boardGrid->addWidget(r11c10, 11, 10, 1, 1);

    r11c12 = new QLabel(gameBoardFrame);
    r11c12->setObjectName(QStringLiteral("r11c12"));

    boardGrid->addWidget(r11c12, 11, 12, 1, 1);

    r11c13 = new QLabel(gameBoardFrame);
    r11c13->setObjectName(QStringLiteral("r11c13"));

    boardGrid->addWidget(r11c13, 11, 13, 1, 1);

    r11c14 = new QLabel(gameBoardFrame);
    r11c14->setObjectName(QStringLiteral("r11c14"));

    boardGrid->addWidget(r11c14, 11, 14, 1, 1);

    r11c15 = new QLabel(gameBoardFrame);
    r11c15->setObjectName(QStringLiteral("r11c15"));

    boardGrid->addWidget(r11c15, 11, 15, 1, 1);

    r11c16 = new QLabel(gameBoardFrame);
    r11c16->setObjectName(QStringLiteral("r11c16"));

    boardGrid->addWidget(r11c16, 11, 16, 1, 1);

    r12c0 = new QLabel(gameBoardFrame);
    r12c0->setObjectName(QStringLiteral("r12c0"));
    r12c0->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r12c0->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r12c0, 12, 0, 1, 1);

    r12c1 = new QLabel(gameBoardFrame);
    r12c1->setObjectName(QStringLiteral("r12c1"));

    boardGrid->addWidget(r12c1, 12, 1, 1, 1);

    r12c2 = new QLabel(gameBoardFrame);
    r12c2->setObjectName(QStringLiteral("r12c2"));
    r12c2->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r12c2->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r12c2, 12, 2, 1, 1);

    r12c3 = new QLabel(gameBoardFrame);
    r12c3->setObjectName(QStringLiteral("r12c3"));

    boardGrid->addWidget(r12c3, 12, 3, 1, 1);

    r12c4 = new QLabel(gameBoardFrame);
    r12c4->setObjectName(QStringLiteral("r12c4"));
    r12c4->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r12c4->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r12c4, 12, 4, 1, 1);

    r12c5 = new QLabel(gameBoardFrame);
    r12c5->setObjectName(QStringLiteral("r12c5"));

    boardGrid->addWidget(r12c5, 12, 5, 1, 1);

    r12c6 = new QLabel(gameBoardFrame);
    r12c6->setObjectName(QStringLiteral("r12c6"));
    r12c6->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r12c6->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r12c6, 12, 6, 1, 1);

    r12c8 = new QLabel(gameBoardFrame);
    r12c8->setObjectName(QStringLiteral("r12c8"));
    r12c8->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r12c8->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r12c8, 12, 8, 1, 1);

    r12c9 = new QLabel(gameBoardFrame);
    r12c9->setObjectName(QStringLiteral("r12c9"));

    boardGrid->addWidget(r12c9, 12, 9, 1, 1);

    r12c10 = new QLabel(gameBoardFrame);
    r12c10->setObjectName(QStringLiteral("r12c10"));
    r12c10->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r12c10->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r12c10, 12, 10, 1, 1);

    r12c11 = new QLabel(gameBoardFrame);
    r12c11->setObjectName(QStringLiteral("r12c11"));

    boardGrid->addWidget(r12c11, 12, 11, 1, 1);

    r12c12 = new QLabel(gameBoardFrame);
    r12c12->setObjectName(QStringLiteral("r12c12"));
    r12c12->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r12c12->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r12c12, 12, 12, 1, 1);

    r12c13 = new QLabel(gameBoardFrame);
    r12c13->setObjectName(QStringLiteral("r12c13"));

    boardGrid->addWidget(r12c13, 12, 13, 1, 1);

    r12c14 = new QLabel(gameBoardFrame);
    r12c14->setObjectName(QStringLiteral("r12c14"));
    r12c14->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r12c14->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r12c14, 12, 14, 1, 1);

    r12c15 = new QLabel(gameBoardFrame);
    r12c15->setObjectName(QStringLiteral("r12c15"));

    boardGrid->addWidget(r12c15, 12, 15, 1, 1);

    r12c16 = new QLabel(gameBoardFrame);
    r12c16->setObjectName(QStringLiteral("r12c16"));
    r12c16->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r12c16->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r12c16, 12, 16, 1, 1);

    r13c0 = new QLabel(gameBoardFrame);
    r13c0->setObjectName(QStringLiteral("r13c0"));

    boardGrid->addWidget(r13c0, 13, 0, 1, 1);

    r13c1 = new QLabel(gameBoardFrame);
    r13c1->setObjectName(QStringLiteral("r13c1"));

    boardGrid->addWidget(r13c1, 13, 1, 1, 1);

    r13c2 = new QLabel(gameBoardFrame);
    r13c2->setObjectName(QStringLiteral("r13c2"));

    boardGrid->addWidget(r13c2, 13, 2, 1, 1);

    r13c3 = new QLabel(gameBoardFrame);
    r13c3->setObjectName(QStringLiteral("r13c3"));

    boardGrid->addWidget(r13c3, 13, 3, 1, 1);

    r13c4 = new QLabel(gameBoardFrame);
    r13c4->setObjectName(QStringLiteral("r13c4"));

    boardGrid->addWidget(r13c4, 13, 4, 1, 1);

    r13c5 = new QLabel(gameBoardFrame);
    r13c5->setObjectName(QStringLiteral("r13c5"));

    boardGrid->addWidget(r13c5, 13, 5, 1, 1);

    r13c6 = new QLabel(gameBoardFrame);
    r13c6->setObjectName(QStringLiteral("r13c6"));

    boardGrid->addWidget(r13c6, 13, 6, 1, 1);

    r13c7 = new QLabel(gameBoardFrame);
    r13c7->setObjectName(QStringLiteral("r13c7"));

    boardGrid->addWidget(r13c7, 13, 7, 1, 1);

    r13c8 = new QLabel(gameBoardFrame);
    r13c8->setObjectName(QStringLiteral("r13c8"));

    boardGrid->addWidget(r13c8, 13, 8, 1, 1);

    r13c9 = new QLabel(gameBoardFrame);
    r13c9->setObjectName(QStringLiteral("r13c9"));

    boardGrid->addWidget(r13c9, 13, 9, 1, 1);

    r13c10 = new QLabel(gameBoardFrame);
    r13c10->setObjectName(QStringLiteral("r13c10"));

    boardGrid->addWidget(r13c10, 13, 10, 1, 1);

    r13c11 = new QLabel(gameBoardFrame);
    r13c11->setObjectName(QStringLiteral("r13c11"));

    boardGrid->addWidget(r13c11, 13, 11, 1, 1);

    r13c12 = new QLabel(gameBoardFrame);
    r13c12->setObjectName(QStringLiteral("r13c12"));

    boardGrid->addWidget(r13c12, 13, 12, 1, 1);

    r13c13 = new QLabel(gameBoardFrame);
    r13c13->setObjectName(QStringLiteral("r13c13"));

    boardGrid->addWidget(r13c13, 13, 13, 1, 1);

    r13c14 = new QLabel(gameBoardFrame);
    r13c14->setObjectName(QStringLiteral("r13c14"));

    boardGrid->addWidget(r13c14, 13, 14, 1, 1);

    r13c15 = new QLabel(gameBoardFrame);
    r13c15->setObjectName(QStringLiteral("r13c15"));

    boardGrid->addWidget(r13c15, 13, 15, 1, 1);

    r13c16 = new QLabel(gameBoardFrame);
    r13c16->setObjectName(QStringLiteral("r13c16"));

    boardGrid->addWidget(r13c16, 13, 16, 1, 1);

    r14c0 = new QLabel(gameBoardFrame);
    r14c0->setObjectName(QStringLiteral("r14c0"));
    r14c0->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r14c0->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r14c0, 14, 0, 1, 1);

    r14c1 = new QLabel(gameBoardFrame);
    r14c1->setObjectName(QStringLiteral("r14c1"));

    boardGrid->addWidget(r14c1, 14, 1, 1, 1);

    r14c2 = new QLabel(gameBoardFrame);
    r14c2->setObjectName(QStringLiteral("r14c2"));
    r14c2->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r14c2->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r14c2, 14, 2, 1, 1);

    r14c3 = new QLabel(gameBoardFrame);
    r14c3->setObjectName(QStringLiteral("r14c3"));

    boardGrid->addWidget(r14c3, 14, 3, 1, 1);

    r14c4 = new QLabel(gameBoardFrame);
    r14c4->setObjectName(QStringLiteral("r14c4"));
    r14c4->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r14c4->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r14c4, 14, 4, 1, 1);

    r14c5 = new QLabel(gameBoardFrame);
    r14c5->setObjectName(QStringLiteral("r14c5"));

    boardGrid->addWidget(r14c5, 14, 5, 1, 1);

    r14c6 = new QLabel(gameBoardFrame);
    r14c6->setObjectName(QStringLiteral("r14c6"));
    r14c6->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r14c6->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r14c6, 14, 6, 1, 1);

    r14c7 = new QLabel(gameBoardFrame);
    r14c7->setObjectName(QStringLiteral("r14c7"));

    boardGrid->addWidget(r14c7, 14, 7, 1, 1);

    r14c8 = new QLabel(gameBoardFrame);
    r14c8->setObjectName(QStringLiteral("r14c8"));
    r14c8->setStyleSheet(QLatin1String("background-color: rgb(118, 95, 80);\n"
                                       "\n"
                                       ""));
    r14c8->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r14c8, 14, 8, 1, 1);

    r14c9 = new QLabel(gameBoardFrame);
    r14c9->setObjectName(QStringLiteral("r14c9"));

    boardGrid->addWidget(r14c9, 14, 9, 1, 1);

    r14c10 = new QLabel(gameBoardFrame);
    r14c10->setObjectName(QStringLiteral("r14c10"));
    r14c10->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r14c10->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r14c10, 14, 10, 1, 1);

    r14c11 = new QLabel(gameBoardFrame);
    r14c11->setObjectName(QStringLiteral("r14c11"));

    boardGrid->addWidget(r14c11, 14, 11, 1, 1);

    r14c12 = new QLabel(gameBoardFrame);
    r14c12->setObjectName(QStringLiteral("r14c12"));
    r14c12->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r14c12->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r14c12, 14, 12, 1, 1);

    r14c13 = new QLabel(gameBoardFrame);
    r14c13->setObjectName(QStringLiteral("r14c13"));

    boardGrid->addWidget(r14c13, 14, 13, 1, 1);

    r14c14 = new QLabel(gameBoardFrame);
    r14c14->setObjectName(QStringLiteral("r14c14"));
    r14c14->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r14c14->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r14c14, 14, 14, 1, 1);

    r14c15 = new QLabel(gameBoardFrame);
    r14c15->setObjectName(QStringLiteral("r14c15"));

    boardGrid->addWidget(r14c15, 14, 15, 1, 1);

    r14c16 = new QLabel(gameBoardFrame);
    r14c16->setObjectName(QStringLiteral("r14c16"));
    r14c16->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r14c16->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r14c16, 14, 16, 1, 1);

    r15c0 = new QLabel(gameBoardFrame);
    r15c0->setObjectName(QStringLiteral("r15c0"));

    boardGrid->addWidget(r15c0, 15, 0, 1, 1);

    r15c1 = new QLabel(gameBoardFrame);
    r15c1->setObjectName(QStringLiteral("r15c1"));

    boardGrid->addWidget(r15c1, 15, 1, 1, 1);

    r15c2 = new QLabel(gameBoardFrame);
    r15c2->setObjectName(QStringLiteral("r15c2"));

    boardGrid->addWidget(r15c2, 15, 2, 1, 1);

    r15c3 = new QLabel(gameBoardFrame);
    r15c3->setObjectName(QStringLiteral("r15c3"));

    boardGrid->addWidget(r15c3, 15, 3, 1, 1);

    r15c4 = new QLabel(gameBoardFrame);
    r15c4->setObjectName(QStringLiteral("r15c4"));

    boardGrid->addWidget(r15c4, 15, 4, 1, 1);

    r15c5 = new QLabel(gameBoardFrame);
    r15c5->setObjectName(QStringLiteral("r15c5"));

    boardGrid->addWidget(r15c5, 15, 5, 1, 1);

    r15c6 = new QLabel(gameBoardFrame);
    r15c6->setObjectName(QStringLiteral("r15c6"));

    boardGrid->addWidget(r15c6, 15, 6, 1, 1);

    r15c7 = new QLabel(gameBoardFrame);
    r15c7->setObjectName(QStringLiteral("r15c7"));

    boardGrid->addWidget(r15c7, 15, 7, 1, 1);

    r15c8 = new QLabel(gameBoardFrame);
    r15c8->setObjectName(QStringLiteral("r15c8"));

    boardGrid->addWidget(r15c8, 15, 8, 1, 1);

    r15c9 = new QLabel(gameBoardFrame);
    r15c9->setObjectName(QStringLiteral("r15c9"));

    boardGrid->addWidget(r15c9, 15, 9, 1, 1);

    r15c10 = new QLabel(gameBoardFrame);
    r15c10->setObjectName(QStringLiteral("r15c10"));

    boardGrid->addWidget(r15c10, 15, 10, 1, 1);

    r15c11 = new QLabel(gameBoardFrame);
    r15c11->setObjectName(QStringLiteral("r15c11"));

    boardGrid->addWidget(r15c11, 15, 11, 1, 1);

    r15c12 = new QLabel(gameBoardFrame);
    r15c12->setObjectName(QStringLiteral("r15c12"));

    boardGrid->addWidget(r15c12, 15, 12, 1, 1);

    r15c13 = new QLabel(gameBoardFrame);
    r15c13->setObjectName(QStringLiteral("r15c13"));

    boardGrid->addWidget(r15c13, 15, 13, 1, 1);

    r15c14 = new QLabel(gameBoardFrame);
    r15c14->setObjectName(QStringLiteral("r15c14"));

    boardGrid->addWidget(r15c14, 15, 14, 1, 1);

    r15c15 = new QLabel(gameBoardFrame);
    r15c15->setObjectName(QStringLiteral("r15c15"));

    boardGrid->addWidget(r15c15, 15, 15, 1, 1);

    r15c16 = new QLabel(gameBoardFrame);
    r15c16->setObjectName(QStringLiteral("r15c16"));

    boardGrid->addWidget(r15c16, 15, 16, 1, 1);

    r16c0 = new QLabel(gameBoardFrame);
    r16c0->setObjectName(QStringLiteral("r16c0"));
    r16c0->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r16c0->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r16c0, 16, 0, 1, 1);

    r16c1 = new QLabel(gameBoardFrame);
    r16c1->setObjectName(QStringLiteral("r16c1"));

    boardGrid->addWidget(r16c1, 16, 1, 1, 1);

    r16c2 = new QLabel(gameBoardFrame);
    r16c2->setObjectName(QStringLiteral("r16c2"));
    r16c2->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r16c2->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r16c2, 16, 2, 1, 1);

    r16c3 = new QLabel(gameBoardFrame);
    r16c3->setObjectName(QStringLiteral("r16c3"));

    boardGrid->addWidget(r16c3, 16, 3, 1, 1);

    r16c4 = new QLabel(gameBoardFrame);
    r16c4->setObjectName(QStringLiteral("r16c4"));
    r16c4->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r16c4->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r16c4, 16, 4, 1, 1);

    r16c5 = new QLabel(gameBoardFrame);
    r16c5->setObjectName(QStringLiteral("r16c5"));

    boardGrid->addWidget(r16c5, 16, 5, 1, 1);

    r16c6 = new QLabel(gameBoardFrame);
    r16c6->setObjectName(QStringLiteral("r16c6"));
    r16c6->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r16c6->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r16c6, 16, 6, 1, 1);

    r16c7_2 = new QLabel(gameBoardFrame);
    r16c7_2->setObjectName(QStringLiteral("r16c7_2"));

    boardGrid->addWidget(r16c7_2, 16, 7, 1, 1);

    r16c8_2 = new QLabel(gameBoardFrame);
    r16c8_2->setObjectName(QStringLiteral("r16c8_2"));
    r16c8_2->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r16c8_2->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r16c8_2, 16, 8, 1, 1);

    r16c9_2 = new QLabel(gameBoardFrame);
    r16c9_2->setObjectName(QStringLiteral("r16c9_2"));

    boardGrid->addWidget(r16c9_2, 16, 9, 1, 1);

    r16c10 = new QLabel(gameBoardFrame);
    r16c10->setObjectName(QStringLiteral("r16c10"));
    r16c10->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r16c10->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r16c10, 16, 10, 1, 1);

    r16c11 = new QLabel(gameBoardFrame);
    r16c11->setObjectName(QStringLiteral("r16c11"));

    boardGrid->addWidget(r16c11, 16, 11, 1, 1);

    r16c12 = new QLabel(gameBoardFrame);
    r16c12->setObjectName(QStringLiteral("r16c12"));
    r16c12->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r16c12->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r16c12, 16, 12, 1, 1);

    r16c13 = new QLabel(gameBoardFrame);
    r16c13->setObjectName(QStringLiteral("r16c13"));

    boardGrid->addWidget(r16c13, 16, 13, 1, 1);

    r16c14 = new QLabel(gameBoardFrame);
    r16c14->setObjectName(QStringLiteral("r16c14"));
    r16c14->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r16c14->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r16c14, 16, 14, 1, 1);

    r16c15 = new QLabel(gameBoardFrame);
    r16c15->setObjectName(QStringLiteral("r16c15"));

    boardGrid->addWidget(r16c15, 16, 15, 1, 1);

    r16c16 = new QLabel(gameBoardFrame);
    r16c16->setObjectName(QStringLiteral("r16c16"));
    r16c16->setStyleSheet(QStringLiteral("background-color: rgb(118, 95, 80);"));
    r16c16->setAlignment(Qt::AlignCenter);

    boardGrid->addWidget(r16c16, 16, 16, 1, 1);

    r1c10 = new QLabel(gameBoardFrame);
    r1c10->setObjectName(QStringLiteral("r1c10"));
    r1c10->setStyleSheet(QStringLiteral(""));

    boardGrid->addWidget(r1c10, 1, 10, 1, 1);

    r12c7 = new QLabel(gameBoardFrame);
    r12c7->setObjectName(QStringLiteral("r12c7"));

    boardGrid->addWidget(r12c7, 12, 7, 1, 1);

    r11c11 = new QLabel(gameBoardFrame);
    r11c11->setObjectName(QStringLiteral("r11c11"));

    boardGrid->addWidget(r11c11, 11, 11, 1, 1);

    boardGrid->setRowStretch(0, 1);
    boardGrid->setRowStretch(2, 1);
    boardGrid->setRowStretch(4, 1);
    boardGrid->setRowStretch(6, 1);
    boardGrid->setRowStretch(8, 1);
    boardGrid->setRowStretch(10, 1);
    boardGrid->setRowStretch(12, 1);
    boardGrid->setRowStretch(14, 1);
    boardGrid->setRowStretch(16, 1);

    horizontalLayout_33->addWidget(gameBoardFrame);

    gameChatFrame = new QFrame(ingamePage);
    gameChatFrame->setObjectName(QStringLiteral("gameChatFrame"));
    sizePolicy6.setHeightForWidth(gameChatFrame->sizePolicy().hasHeightForWidth());
    gameChatFrame->setSizePolicy(sizePolicy6);
    gameChatFrame->setStyleSheet(QLatin1String("QFrame#gameChatFrame{\n"
                                               "	border: none;\n"
                                               "	background-color: rgb(196, 207, 218);\n"
                                               "}"));
    gameChatFrame->setFrameShape(QFrame::StyledPanel);
    gameChatFrame->setFrameShadow(QFrame::Raised);
    verticalLayout_11 = new QVBoxLayout(gameChatFrame);
    verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
    inGameChatBox = new QGroupBox(gameChatFrame);
    inGameChatBox->setObjectName(QStringLiteral("inGameChatBox"));
    sizePolicy9.setHeightForWidth(inGameChatBox->sizePolicy().hasHeightForWidth());
    inGameChatBox->setSizePolicy(sizePolicy9);
    inGameChatBox->setStyleSheet(QLatin1String("QGroupBox#friendsChatBox2{\n"
                                               "	border: 1px solid rgb(8,76,102);\n"
                                               "	border-radius: 5px;\n"
                                               "}"));
    chatVLayout_2 = new QVBoxLayout(inGameChatBox);
    chatVLayout_2->setSpacing(8);
    chatVLayout_2->setObjectName(QStringLiteral("chatVLayout_2"));
    chatVLayout_2->setContentsMargins(-1, 9, -1, -1);
    inGameMessageContainerBox = new QGroupBox(inGameChatBox);
    inGameMessageContainerBox->setObjectName(QStringLiteral("inGameMessageContainerBox"));
    sizePolicy4.setHeightForWidth(inGameMessageContainerBox->sizePolicy().hasHeightForWidth());
    inGameMessageContainerBox->setSizePolicy(sizePolicy4);
    inGameMessageContainerBox->setStyleSheet(QLatin1String("QGroupBox#messagecontainerBox2{\n"
                                                           "	border: 1px solid rgb(8, 76, 102);\n"
                                                           "}"));
    messagesVLayout_2 = new QVBoxLayout(inGameMessageContainerBox);
    messagesVLayout_2->setObjectName(QStringLiteral("messagesVLayout_2"));
    messagesVLayout_2->setContentsMargins(0, 9, 9, 9);
    inGameMessageScrollArea = new QScrollArea(inGameMessageContainerBox);
    inGameMessageScrollArea->setObjectName(QStringLiteral("inGameMessageScrollArea"));
    QSizePolicy sizePolicy11(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy11.setHorizontalStretch(0);
    sizePolicy11.setVerticalStretch(0);
    sizePolicy11.setHeightForWidth(inGameMessageScrollArea->sizePolicy().hasHeightForWidth());
    inGameMessageScrollArea->setSizePolicy(sizePolicy11);
    inGameMessageScrollArea->setMinimumSize(QSize(0, 0));
    inGameMessageScrollArea->setStyleSheet(QStringLiteral("background-color: transparent;"));
    inGameMessageScrollArea->setFrameShape(QFrame::NoFrame);
    inGameMessageScrollArea->setWidgetResizable(true);
    inGameScrollAreaWidgetContents = new QWidget();
    inGameScrollAreaWidgetContents->setObjectName(QStringLiteral("inGameScrollAreaWidgetContents"));
    inGameScrollAreaWidgetContents->setGeometry(QRect(0, 0, 217, 327));
    verticalLayout_20 = new QVBoxLayout(inGameScrollAreaWidgetContents);
    verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
    inGameMessageScrollArea->setWidget(inGameScrollAreaWidgetContents);

    messagesVLayout_2->addWidget(inGameMessageScrollArea);

    chatVLayout_2->addWidget(inGameMessageContainerBox);

    inGameWritingLayout = new QHBoxLayout();
    inGameWritingLayout->setSpacing(6);
    inGameWritingLayout->setObjectName(QStringLiteral("inGameWritingLayout"));
    inGameTextInput = new QLineEdit(inGameChatBox);
    inGameTextInput->setObjectName(QStringLiteral("inGameTextInput"));
    sizePolicy4.setHeightForWidth(inGameTextInput->sizePolicy().hasHeightForWidth());
    inGameTextInput->setSizePolicy(sizePolicy4);
    inGameTextInput->setStyleSheet(QLatin1String("QLineEdit#inGameTextInput{\n"
                                                 "	color: rgb(20, 125, 164);\n"
                                                 "	border: 1px solid rgb(8,76,102);\n"
                                                 "	border-radius: 5px;\n"
                                                 "	background-color: transparent;\n"
                                                 "}\n"
                                                 "\n"
                                                 "QLineEdit:focus#inGameTextInput{\n"
                                                 "	border: 1px solid rgb(20, 125, 164);\n"
                                                 "	/*background-color: rgb(222, 234, 247);*/\n"
                                                 "}"));
    inGameTextInput->setInputMask(QStringLiteral(""));
    inGameTextInput->setMaxLength(32767);
    inGameTextInput->setEchoMode(QLineEdit::Normal);
    inGameTextInput->setDragEnabled(false);
    inGameTextInput->setReadOnly(false);
    inGameTextInput->setCursorMoveStyle(Qt::LogicalMoveStyle);
    inGameTextInput->setClearButtonEnabled(true);

    inGameWritingLayout->addWidget(inGameTextInput);

    inGameSendMessageButton = new QPushButton(inGameChatBox);
    inGameSendMessageButton->setObjectName(QStringLiteral("inGameSendMessageButton"));
    sizePolicy5.setHeightForWidth(inGameSendMessageButton->sizePolicy().hasHeightForWidth());
    inGameSendMessageButton->setSizePolicy(sizePolicy5);
    inGameSendMessageButton->setMinimumSize(QSize(51, 31));
    inGameSendMessageButton->setStyleSheet(QLatin1String("QPushButton#inGameSendMessageButton{\n"
                                                         "	\n"
                                                         "	font: 12pt \"MS Shell Dlg 2\";\n"
                                                         "	background-color: rgb(20,125,164);\n"
                                                         "	border: 1px solid rgb(20,125,164);\n"
                                                         "	color: rgb(255, 255, 255);\n"
                                                         "	border-radius: 10px;\n"
                                                         "}\n"
                                                         "\n"
                                                         "QPushButton:hover#inGameSendMessageButton {\n"
                                                         "	background-color: rgb(8, 76, 102);\n"
                                                         "	border: 1px solid rgb(8, 76, 102);\n"
                                                         "}\n"
                                                         "\n"
                                                         "QPushButton:pressed#inGameSendMessageButton {\n"
                                                         "	border: 4px solid;\n"
                                                         "	border-top-color: rgb(9, 87, 116);\n"
                                                         "	border-left-color: rgb(8, 87, 116);\n"
                                                         "	border-bottom-color: rgb(7, 69, 91);\n"
                                                         "	border-right-color: rgb(7, 69, 91);\n"
                                                         "\n"
                                                         "}"));

    inGameWritingLayout->addWidget(inGameSendMessageButton);

    chatVLayout_2->addLayout(inGameWritingLayout);

    chatVLayout_2->setStretch(0, 1);

    verticalLayout_11->addWidget(inGameChatBox);

    horizontalLayout_33->addWidget(gameChatFrame);

    mainStacked->addWidget(ingamePage);
    friendsPage = new QWidget();
    friendsPage->setObjectName(QStringLiteral("friendsPage"));
    sizePolicy4.setHeightForWidth(friendsPage->sizePolicy().hasHeightForWidth());
    friendsPage->setSizePolicy(sizePolicy4);
    horizontalLayout_8 = new QHBoxLayout(friendsPage);
    horizontalLayout_8->setSpacing(10);
    horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
    horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
    friendsSidebar = new QFrame(friendsPage);
    friendsSidebar->setObjectName(QStringLiteral("friendsSidebar"));
    sizePolicy6.setHeightForWidth(friendsSidebar->sizePolicy().hasHeightForWidth());
    friendsSidebar->setSizePolicy(sizePolicy6);
    friendsSidebar->setStyleSheet(QLatin1String("QFrame{\n"
                                                "	background-color: rgb(196, 207, 218);\n"
                                                "}"));
    friendsSidebar->setFrameShape(QFrame::StyledPanel);
    friendsSidebar->setFrameShadow(QFrame::Raised);
    verticalLayout_7 = new QVBoxLayout(friendsSidebar);
    verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
    addFriendContainer = new QVBoxLayout();
    addFriendContainer->setSpacing(10);
    addFriendContainer->setObjectName(QStringLiteral("addFriendContainer"));
    addFriendLabel = new QLabel(friendsSidebar);
    addFriendLabel->setObjectName(QStringLiteral("addFriendLabel"));
    addFriendLabel->setStyleSheet(QLatin1String("QLabel#addFriendLabel{\n"
                                                "	font: 10pt \"MS Shell Dlg 2\";\n"
                                                "	color: rgb(7, 39, 51);\n"
                                                "}"));

    addFriendContainer->addWidget(addFriendLabel);

    addFriendLayout = new QHBoxLayout();
    addFriendLayout->setSpacing(8);
    addFriendLayout->setObjectName(QStringLiteral("addFriendLayout"));
    addFriendLayout->setContentsMargins(-1, -1, 1, -1);
    addFriendTextInput = new QLineEdit(friendsSidebar);
    addFriendTextInput->setObjectName(QStringLiteral("addFriendTextInput"));
    sizePolicy7.setHeightForWidth(addFriendTextInput->sizePolicy().hasHeightForWidth());
    addFriendTextInput->setSizePolicy(sizePolicy7);
    addFriendTextInput->setMinimumSize(QSize(0, 32));
    addFriendTextInput->setStyleSheet(QLatin1String("QLineEdit{\n"
                                                    "	border: 1px solid rgb(8,76,102);\n"
                                                    "	background-color: rgb(196, 207, 218);\n"
                                                    "	border-radius: 2px;\n"
                                                    "}\n"
                                                    "\n"
                                                    "QLineEdit:focus#addFriendTextInput{\n"
                                                    "	color: rgb(90, 129, 91);\n"
                                                    "	border: 1px solid rgb(111, 159, 113);\n"
                                                    "}"));

    addFriendLayout->addWidget(addFriendTextInput);

    addFriendButton = new QPushButton(friendsSidebar);
    addFriendButton->setObjectName(QStringLiteral("addFriendButton"));
    sizePolicy5.setHeightForWidth(addFriendButton->sizePolicy().hasHeightForWidth());
    addFriendButton->setSizePolicy(sizePolicy5);
    addFriendButton->setMinimumSize(QSize(31, 31));
    addFriendButton->setStyleSheet(QLatin1String("QPushButton#addFriendButton{\n"
                                                 "	background-color: rgb(111, 159, 113);\n"
                                                 "	color: rgb(255, 255, 255);\n"
                                                 "	border-radius: 15px;\n"
                                                 "}\n"
                                                 "\n"
                                                 "QPushButton:hover#addFriendButton{\n"
                                                 "	background-color: rgb(90, 129, 91);\n"
                                                 "}\n"
                                                 "\n"
                                                 "QPushButton:pressed#addFriendButton{\n"
                                                 "	border: 3px solid;\n"
                                                 "	border-top-color: rgb(96, 138, 97);\n"
                                                 "	border-left-color: rgb(96, 138, 97);\n"
                                                 "	border-bottom-color: rgb(82, 118, 83);\n"
                                                 "	border-right-color: rgb(82, 118, 83);\n"
                                                 "}"));

    addFriendLayout->addWidget(addFriendButton);

    addFriendContainer->addLayout(addFriendLayout);

    verticalLayout_7->addLayout(addFriendContainer);

    friendsLayout = new QVBoxLayout();
    friendsLayout->setSpacing(0);
    friendsLayout->setObjectName(QStringLiteral("friendsLayout"));
    friendsListLabel = new QLabel(friendsSidebar);
    friendsListLabel->setObjectName(QStringLiteral("friendsListLabel"));
    friendsListLabel->setStyleSheet(QLatin1String("QLabel#friendsListLabel{\n"
                                                  "	font: 10pt \"MS Shell Dlg 2\";\n"
                                                  "	color: rgb(7, 39, 51);\n"
                                                  "}"));

    friendsLayout->addWidget(friendsListLabel);

    friendsScrollArea = new QScrollArea(friendsSidebar);
    friendsScrollArea->setObjectName(QStringLiteral("friendsScrollArea"));
    sizePolicy11.setHeightForWidth(friendsScrollArea->sizePolicy().hasHeightForWidth());
    friendsScrollArea->setSizePolicy(sizePolicy11);
    friendsScrollArea->setStyleSheet(QLatin1String("border:none;\n"
                                                   "background-color: rgb(196, 207, 218);"));
    friendsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    friendsScrollArea->setWidgetResizable(true);
    friendsScrollAreaWidgetContents = new QWidget();
    friendsScrollAreaWidgetContents->setObjectName(QStringLiteral("friendsScrollAreaWidgetContents"));
    friendsScrollAreaWidgetContents->setGeometry(QRect(0, 0, 245, 69));
    verticalLayout_13 = new QVBoxLayout(friendsScrollAreaWidgetContents);
    verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
    friendsScrollArea->setWidget(friendsScrollAreaWidgetContents);

    friendsLayout->addWidget(friendsScrollArea, 0, Qt::AlignTop);

    friendsLayout->setStretch(1, 1);

    verticalLayout_7->addLayout(friendsLayout);

    horizontalLayout_8->addWidget(friendsSidebar);

    friendsChatBox = new QGroupBox(friendsPage);
    friendsChatBox->setObjectName(QStringLiteral("friendsChatBox"));
    sizePolicy9.setHeightForWidth(friendsChatBox->sizePolicy().hasHeightForWidth());
    friendsChatBox->setSizePolicy(sizePolicy9);
    friendsChatBox->setStyleSheet(QLatin1String("QGroupBox#friendsChatBox{\n"
                                                "	border: 1px solid rgb(8,76,102);\n"
                                                "	border-radius: 5px;\n"
                                                "}"));
    chatVLayout = new QVBoxLayout(friendsChatBox);
    chatVLayout->setSpacing(8);
    chatVLayout->setObjectName(QStringLiteral("chatVLayout"));
    chatVLayout->setContentsMargins(-1, 9, -1, -1);
    friendsMessageContainerBox = new QGroupBox(friendsChatBox);
    friendsMessageContainerBox->setObjectName(QStringLiteral("friendsMessageContainerBox"));
    sizePolicy4.setHeightForWidth(friendsMessageContainerBox->sizePolicy().hasHeightForWidth());
    friendsMessageContainerBox->setSizePolicy(sizePolicy4);
    friendsMessageContainerBox->setStyleSheet(QLatin1String("QGroupBox#friendsMessageContainerBox{\n"
                                                            "	border: 1px solid rgb(8, 76, 102);\n"
                                                            "}"));
    messagesVLayout = new QVBoxLayout(friendsMessageContainerBox);
    messagesVLayout->setObjectName(QStringLiteral("messagesVLayout"));
    messagesVLayout->setContentsMargins(0, 9, 9, 9);
    friendsMessageScrollArea = new QScrollArea(friendsMessageContainerBox);
    friendsMessageScrollArea->setObjectName(QStringLiteral("friendsMessageScrollArea"));
    sizePolicy11.setHeightForWidth(friendsMessageScrollArea->sizePolicy().hasHeightForWidth());
    friendsMessageScrollArea->setSizePolicy(sizePolicy11);
    friendsMessageScrollArea->setStyleSheet(QStringLiteral("background-color: transparent;"));
    friendsMessageScrollArea->setFrameShape(QFrame::NoFrame);
    friendsMessageScrollArea->setWidgetResizable(true);
    friendsMessageScrollAreaWidgetContents = new QWidget();
    friendsMessageScrollAreaWidgetContents->setObjectName(QStringLiteral("friendsMessageScrollAreaWidgetContents"));
    friendsMessageScrollAreaWidgetContents->setGeometry(QRect(0, 0, 502, 69));
    verticalLayout_19 = new QVBoxLayout(friendsMessageScrollAreaWidgetContents);
    verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
    friendsMessageScrollArea->setWidget(friendsMessageScrollAreaWidgetContents);

    messagesVLayout->addWidget(friendsMessageScrollArea, 0, Qt::AlignBottom);

    chatVLayout->addWidget(friendsMessageContainerBox);

    friendsWritingLayout = new QHBoxLayout();
    friendsWritingLayout->setSpacing(6);
    friendsWritingLayout->setObjectName(QStringLiteral("friendsWritingLayout"));
    friendsTextInput = new QLineEdit(friendsChatBox);
    friendsTextInput->setObjectName(QStringLiteral("friendsTextInput"));
    sizePolicy4.setHeightForWidth(friendsTextInput->sizePolicy().hasHeightForWidth());
    friendsTextInput->setSizePolicy(sizePolicy4);
    friendsTextInput->setStyleSheet(QLatin1String("QLineEdit#friendsTextInput{\n"
                                                  "	color: rgb(20, 125, 164);\n"
                                                  "	border: 1px solid rgb(8,76,102);\n"
                                                  "	border-radius: 5px;\n"
                                                  "	background-color: transparent;\n"
                                                  "}\n"
                                                  "\n"
                                                  "QLineEdit:focus#friendsTextInput{\n"
                                                  "	border: 1px solid rgb(20, 125, 164);\n"
                                                  "	/*background-color: rgb(222, 234, 247);*/\n"
                                                  "}"));
    friendsTextInput->setInputMask(QStringLiteral(""));
    friendsTextInput->setMaxLength(32767);
    friendsTextInput->setEchoMode(QLineEdit::Normal);
    friendsTextInput->setDragEnabled(false);
    friendsTextInput->setReadOnly(false);
    friendsTextInput->setCursorMoveStyle(Qt::LogicalMoveStyle);
    friendsTextInput->setClearButtonEnabled(true);

    friendsWritingLayout->addWidget(friendsTextInput);

    friendsSendMessageButton = new QPushButton(friendsChatBox);
    friendsSendMessageButton->setObjectName(QStringLiteral("friendsSendMessageButton"));
    sizePolicy5.setHeightForWidth(friendsSendMessageButton->sizePolicy().hasHeightForWidth());
    friendsSendMessageButton->setSizePolicy(sizePolicy5);
    friendsSendMessageButton->setMinimumSize(QSize(51, 31));
    friendsSendMessageButton->setStyleSheet(QLatin1String("QPushButton#friendsSendMessageButton{\n"
                                                          "	\n"
                                                          "	font: 12pt \"MS Shell Dlg 2\";\n"
                                                          "	background-color: rgb(20,125,164);\n"
                                                          "	border: 1px solid rgb(20,125,164);\n"
                                                          "	color: rgb(255, 255, 255);\n"
                                                          "	border-radius: 10px;\n"
                                                          "}\n"
                                                          "\n"
                                                          "QPushButton:hover#friendsSendMessageButton{\n"
                                                          "	background-color: rgb(8, 76, 102);\n"
                                                          "	border: 1px solid rgb(8, 76, 102);\n"
                                                          "}\n"
                                                          "\n"
                                                          "QPushButton:pressed#friendsSendMessageButton {\n"
                                                          "	border: 4px solid;\n"
                                                          "	border-top-color: rgb(9, 87, 116);\n"
                                                          "	border-left-color: rgb(8, 87, 116);\n"
                                                          "	border-bottom-color: rgb(7, 69, 91);\n"
                                                          "	border-right-color: rgb(7, 69, 91);\n"
                                                          "\n"
                                                          "}"));

    friendsWritingLayout->addWidget(friendsSendMessageButton);

    chatVLayout->addLayout(friendsWritingLayout);

    chatVLayout->setStretch(0, 1);

    horizontalLayout_8->addWidget(friendsChatBox);

    friendsNotifications = new QFrame(friendsPage);
    friendsNotifications->setObjectName(QStringLiteral("friendsNotifications"));
    sizePolicy6.setHeightForWidth(friendsNotifications->sizePolicy().hasHeightForWidth());
    friendsNotifications->setSizePolicy(sizePolicy6);
    friendsNotifications->setStyleSheet(QLatin1String("QFrame{\n"
                                                      "	background-color: rgb(196, 207, 218);\n"
                                                      "}"));
    friendsNotifications->setFrameShape(QFrame::StyledPanel);
    friendsNotifications->setFrameShadow(QFrame::Raised);
    notificationsVLayout = new QVBoxLayout(friendsNotifications);
    notificationsVLayout->setObjectName(QStringLiteral("notificationsVLayout"));
    notificationsLabel = new QLabel(friendsNotifications);
    notificationsLabel->setObjectName(QStringLiteral("notificationsLabel"));
    notificationsLabel->setStyleSheet(QLatin1String("QLabel#notificationsLabel{\n"
                                                    "	font: 10pt \"MS Shell Dlg 2\";\n"
                                                    "	color: rgb(7, 39, 51);\n"
                                                    "}"));

    notificationsVLayout->addWidget(notificationsLabel);

    notificationsScrollArea = new QScrollArea(friendsNotifications);
    notificationsScrollArea->setObjectName(QStringLiteral("notificationsScrollArea"));
    notificationsScrollArea->setMinimumSize(QSize(0, 0));
    notificationsScrollArea->setStyleSheet(QLatin1String("background-color: rgb(196, 207, 218);\n"
                                                         "border: none;"));
    notificationsScrollArea->setWidgetResizable(true);
    notificationsScrollAreaWidgetContents = new QWidget();
    notificationsScrollAreaWidgetContents->setObjectName(QStringLiteral("notificationsScrollAreaWidgetContents"));
    notificationsScrollAreaWidgetContents->setGeometry(QRect(0, 0, 246, 69));
    sizePolicy4.setHeightForWidth(notificationsScrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
    notificationsScrollAreaWidgetContents->setSizePolicy(sizePolicy4);
    notificationsScrollAreaWidgetContents->setMinimumSize(QSize(0, 0));
    verticalLayout_10 = new QVBoxLayout(notificationsScrollAreaWidgetContents);
    verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
    notificationsScrollArea->setWidget(notificationsScrollAreaWidgetContents);

    notificationsVLayout->addWidget(notificationsScrollArea, 0, Qt::AlignTop);

    notificationsVLayout->setStretch(1, 1);

    horizontalLayout_8->addWidget(friendsNotifications);

    mainStacked->addWidget(friendsPage);
    leaderboardPage = new QWidget();
    leaderboardPage->setObjectName(QStringLiteral("leaderboardPage"));
    horizontalLayout_7 = new QHBoxLayout(leaderboardPage);
    horizontalLayout_7->setSpacing(0);
    horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
    horizontalLayout_7->setContentsMargins(0, 0, 0, 10);
    leaderboardLeftSpacer = new QWidget(leaderboardPage);
    leaderboardLeftSpacer->setObjectName(QStringLiteral("leaderboardLeftSpacer"));
    sizePolicy6.setHeightForWidth(leaderboardLeftSpacer->sizePolicy().hasHeightForWidth());
    leaderboardLeftSpacer->setSizePolicy(sizePolicy6);

    horizontalLayout_7->addWidget(leaderboardLeftSpacer);

    leaderboardCenter = new QWidget(leaderboardPage);
    leaderboardCenter->setObjectName(QStringLiteral("leaderboardCenter"));
    QSizePolicy sizePolicy12(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy12.setHorizontalStretch(6);
    sizePolicy12.setVerticalStretch(0);
    sizePolicy12.setHeightForWidth(leaderboardCenter->sizePolicy().hasHeightForWidth());
    leaderboardCenter->setSizePolicy(sizePolicy12);
    LeaderBoardVLayout = new QVBoxLayout(leaderboardCenter);
    LeaderBoardVLayout->setSpacing(10);
    LeaderBoardVLayout->setObjectName(QStringLiteral("LeaderBoardVLayout"));
    LeaderBoardVLayout->setContentsMargins(0, 0, 0, 0);
    leaderboardPlayersBox = new QGroupBox(leaderboardCenter);
    leaderboardPlayersBox->setObjectName(QStringLiteral("leaderboardPlayersBox"));
    QSizePolicy sizePolicy13(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy13.setHorizontalStretch(0);
    sizePolicy13.setVerticalStretch(4);
    sizePolicy13.setHeightForWidth(leaderboardPlayersBox->sizePolicy().hasHeightForWidth());
    leaderboardPlayersBox->setSizePolicy(sizePolicy13);
    leaderboardPlayersBox->setMinimumSize(QSize(0, 0));
    leaderboardPlayersBox->setStyleSheet(QLatin1String("QGroupBox#leaderboardPlayersBox{\n"
                                                       "	border: none;\n"
                                                       "}"));
    leaderboardPlayersBox->setInputMethodHints(Qt::ImhNone);
    leaderboardPlayersBox->setAlignment(Qt::AlignCenter);
    leaderboardPlayersBox->setFlat(false);
    bestplayersVLayout = new QVBoxLayout(leaderboardPlayersBox);
    bestplayersVLayout->setSpacing(0);
    bestplayersVLayout->setObjectName(QStringLiteral("bestplayersVLayout"));
    bestplayersVLayout->setContentsMargins(-1, 40, -1, -1);
    LBGroupBox = new QGroupBox(leaderboardPlayersBox);
    LBGroupBox->setObjectName(QStringLiteral("LBGroupBox"));
    LBGroupBox->setStyleSheet(QLatin1String("QGroupBox{\n"
                                            "	/*border: 1px solid rgb(8,76,102);*/\n"
                                            "	border: none;\n"
                                            "}"));
    RUSHLayout = new QHBoxLayout(LBGroupBox);
    RUSHLayout->setObjectName(QStringLiteral("RUSHLayout"));
    RUSHLayout->setContentsMargins(-1, 4, -1, 4);
    rankLBLabel = new QLabel(LBGroupBox);
    rankLBLabel->setObjectName(QStringLiteral("rankLBLabel"));
    rankLBLabel->setStyleSheet(QLatin1String("QLabel#rankLBLabel{\n"
                                             "	color: rgb(8,76,102);\n"
                                             "}"));
    rankLBLabel->setAlignment(Qt::AlignCenter);

    RUSHLayout->addWidget(rankLBLabel);

    usernameLBLabel = new QLabel(LBGroupBox);
    usernameLBLabel->setObjectName(QStringLiteral("usernameLBLabel"));
    usernameLBLabel->setStyleSheet(QLatin1String("QLabel#usernameLBLabel{\n"
                                                 "	color: rgb(8,76,102);\n"
                                                 "}"));
    usernameLBLabel->setAlignment(Qt::AlignCenter);

    RUSHLayout->addWidget(usernameLBLabel);

    scoreLBLabel = new QLabel(LBGroupBox);
    scoreLBLabel->setObjectName(QStringLiteral("scoreLBLabel"));
    scoreLBLabel->setStyleSheet(QLatin1String("QLabel#scoreLBLabel{\n"
                                              "	color: rgb(8,76,102);\n"
                                              "}"));
    scoreLBLabel->setAlignment(Qt::AlignCenter);

    RUSHLayout->addWidget(scoreLBLabel);

    bestplayersVLayout->addWidget(LBGroupBox);

    leaderBoardScrollArea = new QScrollArea(leaderboardPlayersBox);
    leaderBoardScrollArea->setObjectName(QStringLiteral("leaderBoardScrollArea"));
    leaderBoardScrollArea->setMinimumSize(QSize(0, 0));
    // leaderBoardScrollArea->setMaximumSize(QSize(16777215, 69));
    leaderBoardScrollArea->setFrameShape(QFrame::NoFrame);
    leaderBoardScrollArea->setFrameShadow(QFrame::Raised);
    leaderBoardScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    leaderBoardScrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    leaderBoardScrollArea->setWidgetResizable(true);
    leaderboardScrollAreaWidgetContents = new QWidget();
    leaderboardScrollAreaWidgetContents->setObjectName(QStringLiteral("leaderboardScrollAreaWidgetContents"));
    // leaderboardScrollAreaWidgetContents->setGeometry(QRect(0, 0, 796, 69));
    leaderboardScrollAreaWidgetContentsLayout = new QVBoxLayout(leaderboardScrollAreaWidgetContents);
    leaderboardScrollAreaWidgetContentsLayout->setObjectName(QStringLiteral("leaderboardScrollAreaWidgetContentsLayout"));
    leaderBoardScrollArea->setWidget(leaderboardScrollAreaWidgetContents);

    bestplayersVLayout->addWidget(leaderBoardScrollArea, 0, Qt::AlignTop);

    bestplayersVLayout->setStretch(1, 1);

    LeaderBoardVLayout->addWidget(leaderboardPlayersBox);

    myLeaderboardBox = new QGroupBox(leaderboardCenter);
    myLeaderboardBox->setObjectName(QStringLiteral("myLeaderboardBox"));
    QSizePolicy sizePolicy14(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy14.setHorizontalStretch(0);
    sizePolicy14.setVerticalStretch(1);
    sizePolicy14.setHeightForWidth(myLeaderboardBox->sizePolicy().hasHeightForWidth());
    myLeaderboardBox->setSizePolicy(sizePolicy14);
    myLeaderboardBox->setStyleSheet(QStringLiteral("border:none;"));
    myLeaderboardBox->setAlignment(Qt::AlignCenter);
    myLeaderboardBox->setFlat(false);
    myLeaderboardBox->setCheckable(false);
    yourscoreVLayout = new QHBoxLayout(myLeaderboardBox);
    yourscoreVLayout->setObjectName(QStringLiteral("yourscoreVLayout"));
    yourscoreVLayout->setContentsMargins(-1, 30, -1, -1);
    myBoxLeftSpacer = new QSpacerItem(7, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    yourscoreVLayout->addItem(myBoxLeftSpacer);

    myScoreBox = new QGroupBox(myLeaderboardBox);
    myScoreBox->setObjectName(QStringLiteral("myScoreBox"));
    myScoreBox->setStyleSheet(QLatin1String("QGroupBox#myScoreBox{\n"
                                            "	background-color: rgb(142, 173, 185);\n"
                                            "	border: none;\n"
                                            "}"));
    myscoreHLayout = new QHBoxLayout(myScoreBox);
    myscoreHLayout->setObjectName(QStringLiteral("myscoreHLayout"));
    myscoreHLayout->setContentsMargins(14, -1, 14, -1);
    myRankLabel = new QLabel(myScoreBox);
    myRankLabel->setObjectName(QStringLiteral("myRankLabel"));

    myscoreHLayout->addWidget(myRankLabel);

    myLabel = new QLabel(myScoreBox);
    myLabel->setObjectName(QStringLiteral("myLabel"));

    myscoreHLayout->addWidget(myLabel);

    myScoreLabel = new QLabel(myScoreBox);
    myScoreLabel->setObjectName(QStringLiteral("myScoreLabel"));
    myScoreLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    myscoreHLayout->addWidget(myScoreLabel);

    yourscoreVLayout->addWidget(myScoreBox);

    myBoxRightSpacer = new QSpacerItem(7, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    yourscoreVLayout->addItem(myBoxRightSpacer);

    LeaderBoardVLayout->addWidget(myLeaderboardBox);

    horizontalLayout_7->addWidget(leaderboardCenter);

    leaderboardRightSpacer = new QWidget(leaderboardPage);
    leaderboardRightSpacer->setObjectName(QStringLiteral("leaderboardRightSpacer"));
    sizePolicy6.setHeightForWidth(leaderboardRightSpacer->sizePolicy().hasHeightForWidth());
    leaderboardRightSpacer->setSizePolicy(sizePolicy6);

    horizontalLayout_7->addWidget(leaderboardRightSpacer);

    mainStacked->addWidget(leaderboardPage);

    verticalLayout->addWidget(mainStacked);

    gameButton->setDefault(false);
    mainStacked->setCurrentIndex(0);
    gameMainStacked->setCurrentIndex(1);
    filtersNumberChoices->setCurrentIndex(0);
    filtersModeChoices->setCurrentIndex(0);

    QMetaObject::connectSlotsByName(gameMainWidget);

    gameButton->setText("Game");
    friendsButton->setText("Friends");
    leaderboardButton->setText("Leaderboard");
    usernameLabel->setText("Bob l'Eponge");
    eloLabel->setText("42069");
    logoutButton->setText("LOG OUT");
    createGameButton->setText("+ Create a Game");
    joinGameButton->setText("Join a Game");
    gameConfigurationBox->setTitle(QString());
    gameConfigurationLabel->setText("Game Configuration");
    playerNumberLabel->setText("Player number");
    twoPlayersChoice->setText("2");
    fourPlayersChoice->setText("4");
    gameModeLabel->setText("Game Mode");
    originalModeChoice->setText("Original");
    quotetrisModeChoice->setText("QuoTetris");
    timerModeChoice->setText("Timer");
    trainingModeChoice->setText("Training");
#ifndef QT_NO_ACCESSIBILITY
    startButton->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
    startButton->setText("START");
    inviteFriendsBox->setTitle(QString());
    inviteGroupBox->setTitle(QString());
    inviteFriendsLabel->setText("Invite friends");
    livesGamesLabel->setText("Lives Games");
    usernameUMPLabel->setText("Username");
    modeUMPLabel->setText("Mode");
    playerNumberUMPLabel->setText("Player");
    filtersGroupBox->setTitle(QString());
    filtersPlayerNumberLabel->setText("Player number");
    filtersNumberChoices->setItemText(0, "2");
    filtersNumberChoices->setItemText(1, "4");

    filtersNumberChoices->setCurrentText(QString());
    filterModeLabel->setText("Game Mode");
    filtersModeChoices->setItemText(0, "Original");
    filtersModeChoices->setItemText(1, "QuoTetris");
    filtersModeChoices->setItemText(2, "Timer");
    filtersModeChoices->setItemText(3, "Training");

    quitButton->setText("QUIT");
    gameFlowBox->setTitle(QString());
    gameStatusLabel->setText("Game Status");
    playerTurnLabel->setText("Turn : 0");
    r0c0->setText(QString());
    r0c1->setText(QString());
    r0c2->setText(QString());
    r0c3->setText(QString());
    r0c4->setText(QString());
    r0c5->setText(QString());
    r0c6->setText(QString());
    r0c7->setText(QString());
    r0c8->setText(QString());
    r0c9->setText(QString());
    r0c10->setText(QString());
    r0c11->setText(QString());
    r0c12->setText(QString());
    r0c13->setText(QString());
    r0c14->setText(QString());
    r0c15->setText(QString());
    r0c16->setText(QString());
    r1c0->setText(QString());
    r1c1->setText(QString());
    r1c2->setText(QString());
    r1c3->setText(QString());
    r1c4->setText(QString());
    r1c5->setText(QString());
    r1c6->setText(QString());
    r1c7->setText(QString());
    r1c8->setText(QString());
    r1c9->setText(QString());
    r1c11->setText(QString());
    r1c12->setText(QString());
    r1c13->setText(QString());
    r1c14->setText(QString());
    r1c15->setText(QString());
    r1c16->setText(QString());
    r2c0->setText(QString());
    r2c1->setText(QString());
    r2c2->setText(QString());
    r2c3->setText(QString());
    r2c4->setText(QString());
    r2c5->setText(QString());
    r2c6->setText(QString());
    r2c7->setText(QString());
    r2c8->setText(QString());
    r2c9->setText(QString());
    r2c10->setText(QString());
    r2c11->setText(QString());
    r2c12->setText(QString());
    r2c13->setText(QString());
    r2c14->setText(QString());
    r2c15->setText(QString());
    r2c16->setText(QString());
    r3c0->setText(QString());
    r3c1->setText(QString());
    r3c2->setText(QString());
    r3c3->setText(QString());
    r3c4->setText(QString());
    r3c5->setText(QString());
    r3c6->setText(QString());
    r3c7->setText(QString());
    r3c8->setText(QString());
    r3c9->setText(QString());
    r3c10->setText(QString());
    r3c11->setText(QString());
    r3c12->setText(QString());
    r3c13->setText(QString());
    r3c14->setText(QString());
    r3c15->setText(QString());
    r3c16->setText(QString());
    r4c0->setText(QString());
    r4c1->setText(QString());
    r4c2->setText(QString());
    r4c3->setText(QString());
    r4c4->setText(QString());
    r4c5->setText(QString());
    r4c6->setText(QString());
    r4c7->setText(QString());
    r4c8->setText(QString());
    r4c9->setText(QString());
    r4c10->setText(QString());
    r4c11->setText(QString());
    r4c12->setText(QString());
    r4c13->setText(QString());
    r4c14->setText(QString());
    r4c15->setText(QString());
    r4c16->setText(QString());
    r5c0->setText(QString());
    r5c1->setText(QString());
    r5c2->setText(QString());
    r5c3->setText(QString());
    r5c4->setText(QString());
    r5c5->setText(QString());
    r5c6->setText(QString());
    r5c7->setText(QString());
    r5c8->setText(QString());
    r5c9->setText(QString());
    r5c10->setText(QString());
    r5c11->setText(QString());
    r5c12->setText(QString());
    r5c13->setText(QString());
    r5c14->setText(QString());
    r5c15->setText(QString());
    r5c16->setText(QString());
    r6c0->setText(QString());
    r6c1->setText(QString());
    r6c2->setText(QString());
    r6c3->setText(QString());
    r6c4->setText(QString());
    r6c5->setText(QString());
    r6c6->setText(QString());
    r6c7->setText(QString());
    r6c8->setText(QString());
    r6c9->setText(QString());
    r6c10->setText(QString());
    r6c11->setText(QString());
    r6c12->setText(QString());
    r6c13->setText(QString());
    r6c14->setText(QString());
    r6c15->setText(QString());
    r6c16->setText(QString());
    r7c0->setText(QString());
    r7c1->setText(QString());
    r7c2->setText(QString());
    r7c3->setText(QString());
    r74->setText(QString());
    r7c5->setText(QString());
    r7c6->setText(QString());
    r7c7->setText(QString());
    r7c8->setText(QString());
    r7c9->setText(QString());
    r7c10->setText(QString());
    r7c11->setText(QString());
    r7c12->setText(QString());
    rc13->setText(QString());
    r7c14->setText(QString());
    r7c15->setText(QString());
    r7c16->setText(QString());
    r8c0->setText(QString());
    r8c1->setText(QString());
    r8c2->setText(QString());
    r8c3->setText(QString());
    r8c4->setText(QString());
    r8c5->setText(QString());
    r8c6->setText(QString());
    r8c7->setText(QString());
    r8c8->setText(QString());
    r8c9->setText(QString());
    r8c10->setText(QString());
    r8c11->setText(QString());
    r8c12->setText(QString());
    r8c13->setText(QString());
    r8c14->setText(QString());
    r8c15->setText(QString());
    r8c16->setText(QString());
    r9c0->setText(QString());
    r9c1->setText(QString());
    r9c2->setText(QString());
    r9c3->setText(QString());
    r9c4->setText(QString());
    r9c5->setText(QString());
    r9c6->setText(QString());
    r9c7->setText(QString());
    r9c8->setText(QString());
    r9c9->setText(QString());
    r9c10->setText(QString());
    r9c11->setText(QString());
    r9c12->setText(QString());
    r9c14->setText(QString());
    r9c16_2->setText(QString());
    r9c15->setText(QString());
    r9c16->setText(QString());
    r10c0->setText(QString());
    r10c1->setText(QString());
    r10c2->setText(QString());
    r10c3->setText(QString());
    r10c4->setText(QString());
    r10c5->setText(QString());
    r10c6->setText(QString());
    r10c7->setText(QString());
    r10c8->setText(QString());
    r10c9->setText(QString());
    r10c10->setText(QString());
    r10c11->setText(QString());
    r10c12->setText(QString());
    r10c13->setText(QString());
    r10c14->setText(QString());
    r10c15->setText(QString());
    r10c16->setText(QString());
    r11c0->setText(QString());
    r11c1->setText(QString());
    r11c2->setText(QString());
    r11c3->setText(QString());
    r11c4->setText(QString());
    r11c5->setText(QString());
    r11c6->setText(QString());
    r11c7->setText(QString());
    r11c8->setText(QString());
    r11c9->setText(QString());
    r11c10->setText(QString());
    r11c12->setText(QString());
    r11c13->setText(QString());
    r11c14->setText(QString());
    r11c15->setText(QString());
    r11c16->setText(QString());
    r12c0->setText(QString());
    r12c1->setText(QString());
    r12c2->setText(QString());
    r12c3->setText(QString());
    r12c4->setText(QString());
    r12c5->setText(QString());
    r12c6->setText(QString());
    r12c8->setText(QString());
    r12c9->setText(QString());
    r12c10->setText(QString());
    r12c11->setText(QString());
    r12c12->setText(QString());
    r12c13->setText(QString());
    r12c14->setText(QString());
    r12c15->setText(QString());
    r12c16->setText(QString());
    r13c0->setText(QString());
    r13c1->setText(QString());
    r13c2->setText(QString());
    r13c3->setText(QString());
    r13c4->setText(QString());
    r13c5->setText(QString());
    r13c6->setText(QString());
    r13c7->setText(QString());
    r13c8->setText(QString());
    r13c9->setText(QString());
    r13c10->setText(QString());
    r13c11->setText(QString());
    r13c12->setText(QString());
    r13c13->setText(QString());
    r13c14->setText(QString());
    r13c15->setText(QString());
    r13c16->setText(QString());
    r14c0->setText(QString());
    r14c1->setText(QString());
    r14c2->setText(QString());
    r14c3->setText(QString());
    r14c4->setText(QString());
    r14c5->setText(QString());
    r14c6->setText(QString());
    r14c7->setText(QString());
    r14c8->setText(QString());
    r14c9->setText(QString());
    r14c10->setText(QString());
    r14c11->setText(QString());
    r14c12->setText(QString());
    r14c13->setText(QString());
    r14c14->setText(QString());
    r14c15->setText(QString());
    r14c16->setText(QString());
    r15c0->setText(QString());
    r15c1->setText(QString());
    r15c2->setText(QString());
    r15c3->setText(QString());
    r15c4->setText(QString());
    r15c5->setText(QString());
    r15c6->setText(QString());
    r15c7->setText(QString());
    r15c8->setText(QString());
    r15c9->setText(QString());
    r15c10->setText(QString());
    r15c11->setText(QString());
    r15c12->setText(QString());
    r15c13->setText(QString());
    r15c14->setText(QString());
    r15c15->setText(QString());
    r15c16->setText(QString());
    r16c0->setText(QString());
    r16c1->setText(QString());
    r16c2->setText(QString());
    r16c3->setText(QString());
    r16c4->setText(QString());
    r16c5->setText(QString());
    r16c6->setText(QString());
    r16c7_2->setText(QString());
    r16c8_2->setText(QString());
    r16c9_2->setText(QString());
    r16c10->setText(QString());
    r16c11->setText(QString());
    r16c12->setText(QString());
    r16c13->setText(QString());
    r16c14->setText(QString());
    r16c15->setText(QString());
    r16c16->setText(QString());
    r1c10->setText(QString());
    r12c7->setText(QString());
    r11c11->setText(QString());
    inGameChatBox->setTitle(QString());
    inGameMessageContainerBox->setTitle(QString());
    inGameTextInput->setText(QString());
    inGameSendMessageButton->setText("\360\237\226\211");
    addFriendLabel->setText("Add a friend");
    addFriendButton->setText("+");
    friendsListLabel->setText("Friends");
    friendsChatBox->setTitle(QString());
    friendsMessageContainerBox->setTitle(QString());
    friendsTextInput->setText(QString());
    friendsSendMessageButton->setText("\360\237\226\211");
    notificationsLabel->setText("Notifications");
    leaderboardPlayersBox->setTitle("Best players of the moment");
    rankLBLabel->setText("Rank");
    usernameLBLabel->setText("Username");
    scoreLBLabel->setText("Score");
    myLeaderboardBox->setTitle("Your score");
    myRankLabel->setText("65");
    myLabel->setText("Me");
    myScoreLabel->setText("42069");
    Q_UNUSED(gameMainWidget);


    QObject::connect(gameButton, &QPushButton::clicked, [this]() { this->gameButtonPressed(); });
    QObject::connect(createGameButton, &QPushButton::clicked, [this]() { this->createGameButtonPressed(); });
    QObject::connect(joinGameButton, &QPushButton::clicked, [this]() { this->joinGameButtonPressed(); });

    QObject::connect(friendsButton, &QPushButton::clicked, [this]() { this->friendsButtonPressed(); });
    QObject::connect(leaderboardButton, &QPushButton::clicked, [this]() { this->leaderboardButtonPressed(); });

    QObject::connect(logoutButton, &QPushButton::clicked, [this]() { this->logoutButtonPressed(); });
}

void QtVue::gotoRegisterWindow()
{
    appMainStacked->setCurrentIndex(0);
}

void QtVue::gotoLoginWindow()
{
    appMainStacked->setCurrentIndex(1);
}

void QtVue::gotoGameWindow()
{
    serverController->fetchData();

    appMainStacked->setCurrentIndex(2);
    usernameLabel->setText(QString::fromStdString(*mainModel->getUsername()));
    eloLabel->setText(QString::fromStdString(std::to_string(*mainModel->getELO())));
}

void QtVue::updateLeaderboard()
{
    auto leaderboard = mainModel->getLeaderboard();

    // qDeleteAll(leaderboardScrollAreaWidgetContentsLayout->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
    while (QWidget *w = leaderboardScrollAreaWidgetContentsLayout->findChild<QWidget *>())
        delete w;

    if (!leaderboard->empty()) {
        int i = 1;
        for (auto &leader : *leaderboard) {
            auto w = createLeaderboardBox(leaderboardScrollAreaWidgetContents, i++, leader.first, (int)leader.second);
            leaderboardScrollAreaWidgetContentsLayout->addWidget(w);
        }
    }
}

QWidget *QtVue::createLeaderboardBox(QWidget *parent, int rank, std::string username, int score)
{
    auto leadBox = new QGroupBox(parent);
    leadBox->setObjectName(QStringLiteral("leadBox"));
    leadBox->setGeometry(QRect(100, 120, 625, 32));

    if (rank <= 1)
        leadBox->setStyleSheet(QLatin1String("background-color: rgb(255, 236, 168);\n"
                                             "border: none;"));
    else if (rank == 2)
        leadBox->setStyleSheet(QLatin1String("background-color: rgb(212, 224, 236);\n"
                                             "border:none;\n"));
    else if (rank == 3)
        leadBox->setStyleSheet(QLatin1String("background-color: rgb(232, 183, 158);"
                                             "border: none;\n"));
    else
        leadBox->setStyleSheet(QStringLiteral("border:none;"));

    auto horizontalLayout_20 = new QHBoxLayout(leadBox);
    horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
    auto leadRankLabel = new QLabel(leadBox);
    leadRankLabel->setObjectName(QStringLiteral("leadRankLabel"));

    horizontalLayout_20->addWidget(leadRankLabel);

    auto leadUserLabel = new QLabel(leadBox);
    leadUserLabel->setObjectName(QStringLiteral("leadUserLabel"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(leadUserLabel->sizePolicy().hasHeightForWidth());
    leadUserLabel->setSizePolicy(sizePolicy1);

    horizontalLayout_20->addWidget(leadUserLabel);

    auto leadScoreLabel = new QLabel(leadBox);
    leadScoreLabel->setObjectName(QStringLiteral("leadScoreLabel"));
    leadScoreLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    horizontalLayout_20->addWidget(leadScoreLabel);

    leadRankLabel->setText(QString::fromStdString(std::to_string(rank)));
    leadUserLabel->setText(QString::fromStdString(username));
    leadScoreLabel->setText(QString::fromStdString(std::to_string(score)));

    return leadBox;
}

void QtVue::loginButtonPressed()
{
    auto username = usernameLineEditLogin->text().toStdString();
    auto password = passwordLineEditLogin->text().toStdString();
    
    if (username.length() <= 0) {
        messageLabelLogin->setText("Username cannot be empty");
        messageLabelLogin->show();
        return;
    }

    if (password.length() <= 0) {
        messageLabelLogin->setText("Password cannot be empty");
        messageLabelLogin->show();
        return;
    }

    if (!serverController->login(username, password)) {
        messageLabelLogin->setText("Wrong username or password");
        messageLabelLogin->show();
        return;
    }

    // Reset fields for next time we come back to login
    usernameLineEditLogin->setText("");
    passwordLineEditLogin->setText("");
    messageLabelLogin->hide();
    
    gotoGameWindow();
}

void QtVue::registerButtonPressed()
{
    auto username = usernameLineEditRegister->text().toStdString();
    auto password = passwordLineEditRegister->text().toStdString();
    auto confirmPassword = confirmPasswordLineEdit->text().toStdString();
    
    if (username.length() <= 0) {
        messageLabelRegister->setText("Username cannot be empty");
        messageLabelRegister->show();
        return;
    }

    if (password.length() <= 0) {
        messageLabelRegister->setText("Password cannot be empty");
        messageLabelRegister->show();
        return;
    }

    if (password != confirmPassword) {
        messageLabelRegister->setText("Passwords do not match");
        messageLabelRegister->show();
        return;
    }

    if (!serverController->registerUser(username, password)) {
        messageLabelRegister->setText("Error creating account. Username probably already exists");
        messageLabelRegister->show();
        return;
    }

    // Reset fields for next time we come back to register
    usernameLineEditRegister->setText("");
    passwordLineEditRegister->setText("");
    confirmPasswordLineEdit->setText("");
    messageLabelRegister->hide();

    messageLabelLogin->setText("Successfully registered. You can now log in.");
    messageLabelLogin->show();
    usernameLineEditLogin->setText(QString::fromStdString(username));
    gotoLoginWindow();
}

void QtVue::logoutButtonPressed()
{
    gotoLoginWindow();
}

void QtVue::gameButtonPressed() //
{
    // if ( bool == true){mainStacked->setCurrentIndex(1); gameMainStacked->setCurrentIndex(0);} //ingame indices
    // else 
    mainStacked->setCurrentIndex(0);
}

void QtVue::joinGameButtonPressed()
{
    gameMainStacked->setCurrentIndex(1);
}

void QtVue::createGameButtonPressed()
{
    gameMainStacked->setCurrentIndex(0);
}

void QtVue::friendsButtonPressed()
{
    mainStacked->setCurrentIndex(2);
}

void QtVue::leaderboardButtonPressed()
{
    mainStacked->setCurrentIndex(3);
    updateLeaderboard();
}