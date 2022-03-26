
#include "QtVue.h"

#include <QPushButton>
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

    usernameLabelRegister->setText("Username");
    usernameLineEditRegister->setText("");
    passwordLabelRegister->setText("Password");
    passwordLineEditRegister->setText("");
    confirmPasswordLabel->setText("Confirm password");
    confirmPasswordLineEdit->setText("");
    registerButton->setText("REGISTER");
    
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

    usernameLabelLogin->setText("Username");
    usernameLineEditLogin->setInputMask(QString());
    usernameLineEditLogin->setText("");
    passwordLabelLogin->setText("Password");
    passwordLineEditLogin->setText("");
    loginButton->setText("LOGIN");
    registerLabel->setText("Not registered yet ?");
    registerButtonLogin->setText("REGISTER");

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
    gameButton->setStyleSheet(QLatin1String("QPushButton#gameButton{\n"
                                            "	font: 10pt \"MS Shell Dlg 2\";\n"
                                            "	color: rgb(8,76,102);\n"
                                            "	background-color: rgb(196, 207, 218);\n"
                                            "	border: 3px solid rgb(196, 207, 218);\n"
                                            "	border-radius: 7px;\n"
                                            "	padding: 15px;\n"
                                            "}\n"
                                            "\n"
                                            "QPushButton:hover#gameButton {\n"
                                            "	color: rgb(20,125,164);\n"
                                            "	border-color: rgb(20,125,164);\n"
                                            "}\n"
                                            ""));

    horizontalLayout_2->addWidget(gameButton);

    friendsButton = new QPushButton(topBarButtons);
    friendsButton->setObjectName(QStringLiteral("friendsButton"));
    sizePolicy2.setHeightForWidth(friendsButton->sizePolicy().hasHeightForWidth());
    friendsButton->setSizePolicy(sizePolicy2);
    friendsButton->setMinimumSize(QSize(0, 0));
    friendsButton->setStyleSheet(QLatin1String("QPushButton#friendsButton{\n"
                                               "	font: 10pt \"MS Shell Dlg 2\";\n"
                                               "	color: rgb(8,76,102);\n"
                                               "	background-color: rgb(196, 207, 218);\n"
                                               "	border: 3px solid rgb(196, 207, 218);\n"
                                               "	border-radius: 7px;\n"
                                               "	padding: 12px;\n"
                                               "}\n"
                                               "\n"
                                               "QPushButton:hover#friendsButton {\n"
                                               "	color: rgb(20,125,164);\n"
                                               "	border-color: rgb(20,125,164);\n"
                                               "}\n"
                                               ""));

    horizontalLayout_2->addWidget(friendsButton);

    leaderboardButton = new QPushButton(topBarButtons);
    leaderboardButton->setObjectName(QStringLiteral("leaderboardButton"));
    sizePolicy2.setHeightForWidth(leaderboardButton->sizePolicy().hasHeightForWidth());
    leaderboardButton->setSizePolicy(sizePolicy2);
    leaderboardButton->setMinimumSize(QSize(0, 0));
    leaderboardButton->setStyleSheet(QLatin1String("QPushButton#leaderboardButton{\n"
                                                   "	font: 10pt \"MS Shell Dlg 2\";\n"
                                                   "	color: rgb(8,76,102);\n"
                                                   "	background-color: rgb(196, 207, 218);\n"
                                                   "	border: 3px solid rgb(196, 207, 218);\n"
                                                   "	border-radius: 7px;\n"
                                                   "	padding: 12px;\n"
                                                   "}\n"
                                                   "\n"
                                                   "QPushButton:hover#leaderboardButton {\n"
                                                   "	color: rgb(20,125,164);\n"
                                                   "	border-color: rgb(20,125,164);\n"
                                                   "\n"
                                                   "}\n"
                                                   ""));

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

    logOutButton = new QPushButton(topBarUser);
    logOutButton->setObjectName(QStringLiteral("logOutButton"));
    QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(logOutButton->sizePolicy().hasHeightForWidth());
    logOutButton->setSizePolicy(sizePolicy5);
    logOutButton->setMinimumSize(QSize(55, 35));
    logOutButton->setMaximumSize(QSize(0, 16777215));
    logOutButton->setCursor(QCursor(Qt::ArrowCursor));
    logOutButton->setStyleSheet(QLatin1String("QPushButton#logOutButton{\n"
                                              "	font: 7pt \"MS Shell Dlg 2\";\n"
                                              "	color: rgb(255, 255, 255);\n"
                                              "	background-color: rgb(179,38,30);\n"
                                              "	border: 3px solid rgb(179,38,30);\n"
                                              "	border-radius: 15px;\n"
                                              "}\n"
                                              "\n"
                                              "QPushButton:hover#logOutButton{\n"
                                              "	background-color: rgb(148, 31, 25);\n"
                                              "	border-color: rgb(148, 31,25);\n"
                                              "}\n"
                                              "\n"
                                              "QPushButton:pressed#logOutButton{\n"
                                              "	border-top-color: rgb(167, 33, 28);\n"
                                              "	border-left-color: rgb(167, 33, 28);\n"
                                              "	border-bottom-color: rgb(127, 25, 21);\n"
                                              "	border-right-color: rgb(127, 25, 21);\n"
                                              "}"));

    horizontalLayout_3->addWidget(logOutButton);

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
                                                  "QPushButton:pressed#createGameButton{\n"
                                                  "	background-color: rgb(8, 76, 102);\n"
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
                                                "QPushButton:pressed#joinGameButton{\n"
                                                "	background-color: rgb(8, 76, 102);\n"
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

    LivesGamesLabel = new QLabel(liveGamesFrame);
    LivesGamesLabel->setObjectName(QStringLiteral("LivesGamesLabel"));
    sizePolicy7.setHeightForWidth(LivesGamesLabel->sizePolicy().hasHeightForWidth());
    LivesGamesLabel->setSizePolicy(sizePolicy7);
    LivesGamesLabel->setMinimumSize(QSize(0, 20));
    LivesGamesLabel->setStyleSheet(QLatin1String("QLabel#LivesGamesLabel{\n"
                                                 "	font: 10pt \"MS Shell Dlg 2\";\n"
                                                 "	color: rgb(7, 39, 51);\n"
                                                 "}"));
    LivesGamesLabel->setAlignment(Qt::AlignCenter);

    livesgamesVLayout->addWidget(LivesGamesLabel);

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

    GameBoardFrame = new QFrame(ingamePage);
    GameBoardFrame->setObjectName(QStringLiteral("GameBoardFrame"));
    sizePolicy9.setHeightForWidth(GameBoardFrame->sizePolicy().hasHeightForWidth());
    GameBoardFrame->setSizePolicy(sizePolicy9);
    GameBoardFrame->setStyleSheet(QLatin1String("QFrame#GameBoardFrame{\n"
                                                "	border: 2px solid rgb(159, 128, 107);\n"
                                                "	background-color: rgb(159, 128, 107);\n"
                                                "	border-radius: 5px;\n"
                                                "}"));
    GameBoardFrame->setFrameShape(QFrame::StyledPanel);
    GameBoardFrame->setFrameShadow(QFrame::Raised);

    horizontalLayout_33->addWidget(GameBoardFrame);

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
    inGameTextInput->setStyleSheet(QLatin1String("QLineEdit#messageLineEdit2 {\n"
                                                 "	color: rgb(20, 125, 164);\n"
                                                 "	border: 1px solid rgb(8,76,102);\n"
                                                 "	border-radius: 5px;\n"
                                                 "	background-color: transparent;\n"
                                                 "}\n"
                                                 "\n"
                                                 "QLineEdit:focus#messageLineEdit2{\n"
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
    inGameSendMessageButton->setStyleSheet(QLatin1String("QPushButton#sendmessageButton2{\n"
                                                         "	\n"
                                                         "	font: 12pt \"MS Shell Dlg 2\";\n"
                                                         "	background-color: rgb(20,125,164);\n"
                                                         "	border: 1px solid rgb(20,125,164);\n"
                                                         "	color: rgb(255, 255, 255);\n"
                                                         "	border-radius: 10px;\n"
                                                         "}\n"
                                                         "\n"
                                                         "QPushButton:hover#sendmessageButton2 {\n"
                                                         "	background-color: rgb(8, 76, 102);\n"
                                                         "	border: 1px solid rgb(8, 76, 102);\n"
                                                         "}\n"
                                                         "\n"
                                                         "QPushButton:pressed#sendmessageButton2 {\n"
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
    addFriendLabel->setStyleSheet(QLatin1String("QLabel#addfriendLabel{\n"
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
                                                    "QLineEdit:focus#addfriendLineEdit{\n"
                                                    "	color: rgb(90, 129, 91);\n"
                                                    "	border: 1px solid rgb(111, 159, 113);\n"
                                                    "}"));

    addFriendLayout->addWidget(addFriendTextInput);

    addFriendButton = new QPushButton(friendsSidebar);
    addFriendButton->setObjectName(QStringLiteral("addFriendButton"));
    sizePolicy5.setHeightForWidth(addFriendButton->sizePolicy().hasHeightForWidth());
    addFriendButton->setSizePolicy(sizePolicy5);
    addFriendButton->setMinimumSize(QSize(31, 31));
    addFriendButton->setStyleSheet(QLatin1String("QPushButton#addfriendButton{\n"
                                                 "	background-color: rgb(111, 159, 113);\n"
                                                 "	color: rgb(255, 255, 255);\n"
                                                 "	border-radius: 15px;\n"
                                                 "}\n"
                                                 "\n"
                                                 "QPushButton:hover#addfriendButton{\n"
                                                 "	background-color: rgb(90, 129, 91);\n"
                                                 "}\n"
                                                 "\n"
                                                 "QPushButton:pressed#addfriendButton{\n"
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
    friendsListLabel->setStyleSheet(QLatin1String("QLabel#friendslistLabel{\n"
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
    friendsMessageContainerBox->setStyleSheet(QLatin1String("QGroupBox#messagecontainerBox{\n"
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
    friendsTextInput->setStyleSheet(QLatin1String("QLineEdit#messageLineEdit {\n"
                                                  "	color: rgb(20, 125, 164);\n"
                                                  "	border: 1px solid rgb(8,76,102);\n"
                                                  "	border-radius: 5px;\n"
                                                  "	background-color: transparent;\n"
                                                  "}\n"
                                                  "\n"
                                                  "QLineEdit:focus#messageLineEdit {\n"
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
    friendsSendMessageButton->setStyleSheet(QLatin1String("QPushButton#sendmessageButton{\n"
                                                          "	\n"
                                                          "	font: 12pt \"MS Shell Dlg 2\";\n"
                                                          "	background-color: rgb(20,125,164);\n"
                                                          "	border: 1px solid rgb(20,125,164);\n"
                                                          "	color: rgb(255, 255, 255);\n"
                                                          "	border-radius: 10px;\n"
                                                          "}\n"
                                                          "\n"
                                                          "QPushButton:hover#sendmessageButton {\n"
                                                          "	background-color: rgb(8, 76, 102);\n"
                                                          "	border: 1px solid rgb(8, 76, 102);\n"
                                                          "}\n"
                                                          "\n"
                                                          "QPushButton:pressed#sendmessageButton {\n"
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
    rankLBLabel->setStyleSheet(QLatin1String("QLabel#rankLabel{\n"
                                             "	color: rgb(8,76,102);\n"
                                             "}"));
    rankLBLabel->setAlignment(Qt::AlignCenter);

    RUSHLayout->addWidget(rankLBLabel);

    usernameLBLabel = new QLabel(LBGroupBox);
    usernameLBLabel->setObjectName(QStringLiteral("usernameLBLabel"));
    usernameLBLabel->setStyleSheet(QLatin1String("QLabel#usernameLLabel{\n"
                                                 "	color: rgb(8,76,102);\n"
                                                 "}"));
    usernameLBLabel->setAlignment(Qt::AlignCenter);

    RUSHLayout->addWidget(usernameLBLabel);

    scoreLBLabel = new QLabel(LBGroupBox);
    scoreLBLabel->setObjectName(QStringLiteral("scoreLBLabel"));
    scoreLBLabel->setStyleSheet(QLatin1String("QLabel#scoreLabel{\n"
                                              "	color: rgb(8,76,102);\n"
                                              "}"));
    scoreLBLabel->setAlignment(Qt::AlignCenter);

    RUSHLayout->addWidget(scoreLBLabel);

    bestplayersVLayout->addWidget(LBGroupBox);

    leaderBoardScrollArea = new QScrollArea(leaderboardPlayersBox);
    leaderBoardScrollArea->setObjectName(QStringLiteral("leaderBoardScrollArea"));
    leaderBoardScrollArea->setMinimumSize(QSize(0, 0));
    leaderBoardScrollArea->setMaximumSize(QSize(16777215, 69));
    leaderBoardScrollArea->setFrameShape(QFrame::NoFrame);
    leaderBoardScrollArea->setFrameShadow(QFrame::Raised);
    leaderBoardScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    leaderBoardScrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
    leaderBoardScrollArea->setWidgetResizable(true);
    leaderboardScrollAreaWidgetContents = new QWidget();
    leaderboardScrollAreaWidgetContents->setObjectName(QStringLiteral("leaderboardScrollAreaWidgetContents"));
    leaderboardScrollAreaWidgetContents->setGeometry(QRect(0, 0, 796, 69));
    verticalLayout_12 = new QVBoxLayout(leaderboardScrollAreaWidgetContents);
    verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
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
    myScoreBox->setStyleSheet(QLatin1String("QGroupBox#myscoreBox{\n"
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

    mainStacked->setCurrentIndex(0);
    gameMainStacked->setCurrentIndex(1);
    filtersNumberChoices->setCurrentIndex(1);
    filtersModeChoices->setCurrentIndex(0);

    QMetaObject::connectSlotsByName(gameMainWidget);

    gameButton->setText("Game");
    friendsButton->setText("Friends");
    leaderboardButton->setText("Leaderboard");
    usernameLabel->setText("Bob l'Eponge");
    eloLabel->setText("42069");
    logOutButton->setText("LOG OUT");
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
    LivesGamesLabel->setText("Lives Games");
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
} // setupUi

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
    appMainStacked->setCurrentIndex(2);
}



void QtVue::loginButtonPressed()
{
    std::cout << "login pressed!" << std::endl;
}

void QtVue::registerButtonPressed()
{
    std::cout << "register pressed!" << std::endl;
}

void QtVue::loginFieldsUpdated()
{
}

void QtVue::registerFieldsUpdated()
{
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
}