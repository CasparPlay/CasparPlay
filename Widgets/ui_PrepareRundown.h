/********************************************************************************
** Form generated from reading UI file 'PrepareRundown.ui'
**
** Created: Thu Dec 11 13:12:02 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREPARERUNDOWN_H
#define UI_PREPARERUNDOWN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrepareRundown
{
public:

    void setupUi(QWidget *PrepareRundown)
    {
        if (PrepareRundown->objectName().isEmpty())
            PrepareRundown->setObjectName(QString::fromUtf8("PrepareRundown"));
        PrepareRundown->resize(400, 300);

        retranslateUi(PrepareRundown);

        QMetaObject::connectSlotsByName(PrepareRundown);
    } // setupUi

    void retranslateUi(QWidget *PrepareRundown)
    {
        PrepareRundown->setWindowTitle(QApplication::translate("PrepareRundown", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PrepareRundown: public Ui_PrepareRundown {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREPARERUNDOWN_H
