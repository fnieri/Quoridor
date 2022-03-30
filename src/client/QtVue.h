//
// Created by louis on 3/30/22.
//

#pragma once

#include <QWidget>

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

private:
    Ui::QtVue *ui;

};
