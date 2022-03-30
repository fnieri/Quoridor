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
    loginTabBar = new QTabWidget(this);
    createLoginAndRegister();
}

QtVue::~QtVue()
{
    delete ui;
}

void QtVue::handleLoginButtonClicked()
{
    std::cout << "Login button clicked" << std::endl;
}

void QtVue::createLoginAndRegister()
{
    auto *loginBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    auto *loginTextEntry = new QLineEdit(this);
    loginTextEntry->setPlaceholderText("Login");
    loginBoxLayout->addWidget(loginTextEntry);

    auto *passwordTextEntry = new QLineEdit(this);
    passwordTextEntry->setPlaceholderText("Password");
    passwordTextEntry->setEchoMode(QLineEdit::Password);
    loginBoxLayout->addWidget(passwordTextEntry);

    auto *loginButton = new QPushButton("Login", this);
    connect(loginButton, &QPushButton::clicked, this, &QtVue::handleLoginButtonClicked);
    loginBoxLayout->addWidget(loginButton);

    auto *loginBox = new QWidget(this);
    loginBox->setLayout(loginBoxLayout);

    loginTabBar->addTab(loginBox, "Login");
    loginTabBar->addTab(new QWidget(), "Register");
}
