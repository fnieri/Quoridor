/********************************************************************************
** Form generated from reading UI file 'QtVue.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTVUE_H
#define UI_QTVUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtVue
{
public:

    void setupUi(QWidget *QtVue)
    {
        if (QtVue->objectName().isEmpty())
            QtVue->setObjectName(QString::fromUtf8("Quoridor"));
        QtVue->resize(1000, 1000);

        retranslateUi(QtVue);

        QMetaObject::connectSlotsByName(QtVue);
    } // setupUi

    void retranslateUi(QWidget *QtVue)
    {
        QtVue->setWindowTitle(QCoreApplication::translate("Quoridor", "Quoridor", nullptr));
    } // retranslateUi

};

namespace Ui {
class QtVue: public Ui_QtVue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTVUE_H