/********************************************************************************
** Form generated from reading UI file 'Razuna.ui'
**
** Created: Sun Jan 11 15:15:36 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAZUNA_H
#define UI_RAZUNA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *labelName;
    QLabel *labelApi;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonCancel;
    QLineEdit *lineEditName;
    QLineEdit *lineEditApi;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(293, 163);
        labelName = new QLabel(Form);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setGeometry(QRect(20, 30, 50, 15));
        labelApi = new QLabel(Form);
        labelApi->setObjectName(QString::fromUtf8("labelApi"));
        labelApi->setGeometry(QRect(20, 70, 50, 15));
        pushButtonOk = new QPushButton(Form);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));
        pushButtonOk->setGeometry(QRect(200, 120, 84, 26));
        pushButtonCancel = new QPushButton(Form);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(110, 120, 84, 26));
        lineEditName = new QLineEdit(Form);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setGeometry(QRect(80, 26, 180, 25));
        lineEditApi = new QLineEdit(Form);
        lineEditApi->setObjectName(QString::fromUtf8("lineEditApi"));
        lineEditApi->setGeometry(QRect(80, 64, 180, 25));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        labelName->setText(QApplication::translate("Form", "Name:", 0, QApplication::UnicodeUTF8));
        labelApi->setText(QApplication::translate("Form", "Api Key:", 0, QApplication::UnicodeUTF8));
        pushButtonOk->setText(QApplication::translate("Form", "Ok", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("Form", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAZUNA_H
