#include "RazunaDialog.h"
#include "DatabaseManager.h"

RazunaDialog::RazunaDialog(QWidget* parent):QDialog(parent)
{
    setupUi(this);

    QObject::connect(this->pushButtonOk, SIGNAL(clicked()), this, SLOT(okHandler()));
    QObject::connect(this->pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancelHandler()));
}

const QString RazunaDialog::getname() const
{
    return this->lineEditName->text();
}

const QString RazunaDialog::getApiKey() const
{
    return this->lineEditApi->text();
}

void RazunaDialog::okHandler()
{
    DatabaseManager::getInstance().insertRazuna(RazunaModel(0, this->lineEditName->text(), this->lineEditApi->text()));
}

void RazunaDialog::cancelHandler()
{
    this->close();
}
