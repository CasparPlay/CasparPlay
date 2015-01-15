#pragma once

#include "Shared.h"
#include "Global.h"

#include "ui_RazunaDialog.h"

#include <QtGui/QDialog>
#include <QtGui/QWidget>


class WIDGETS_EXPORT RazunaDialog: public QDialog, Ui::RazunaDialog
{
    Q_OBJECT

    public:
        explicit RazunaDialog(QWidget* parent = 0);

        const QString getname() const;
        const QString getApiKey() const;
    private:
        Q_SLOT void okHandler();
        Q_SLOT void cancelHandler();
};
