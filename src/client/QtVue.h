//
// Created by louis on 3/30/22.
//

#pragma once
#include <iostream>

#include <QCheckBox>
#include <QLabel>
#include <QTabWidget>
#include <QToolBox>
#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui
{
class QtVue;
}
QT_END_NAMESPACE

class QtVue : public QWidget
{
    Q_OBJECT

public:
    explicit QtVue(QWidget *parent = nullptr);
    ~QtVue() override;

private slots:
//    void handleLoginTabChanged(int index);
    void handleLoginButtonClicked();

private:
    Ui::QtVue *ui;
    QTabWidget *loginTabBar;

    void createLoginAndRegister();
};
