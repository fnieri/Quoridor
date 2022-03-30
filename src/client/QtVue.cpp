//
// Created by louis on 3/30/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QtVue.h" resolved

#include <QCheckBox>
#include "QtVue.h"
#include "ui_QtVue.h"

QtVue::QtVue(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QtVue)
{
    ui->setupUi(this);
}

QtVue::~QtVue()
{
    delete ui;
}
