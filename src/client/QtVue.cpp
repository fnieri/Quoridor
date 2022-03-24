
#include "QtVue.h"

#include <QPushButton>

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

    // registerMainWidget->show();
    loginMainWidget->show();
    return app->exec();
}

/* === Register Window === */
void QtVue::setupRegisterUI()
{
    registerMainWidget = new QWidget();
    registerMainWidget->setObjectName(QStringLiteral("registerMainWidget"));
    registerMainWidget->resize(1280, 720);
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
}

/* === Login Window === */
void QtVue::setupLoginUI()
{
    loginMainWidget = new QWidget();
    loginMainWidget->setObjectName(QStringLiteral("loginMainWidget"));
    loginMainWidget->resize(1280, 720);
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
}

/* === Game Window === */
void QtVue::setupGameUI()
{
}