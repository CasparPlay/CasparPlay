#pragma once

#include "Shared.h"
#include "ui_TextScroller.h"

#include "Global.h"

#include <QtGui/QDialog>
#include <QtGui/QWidget>
#include <QtNetwork/QUdpSocket>

class WIDGETS_EXPORT TextScroller : public QDialog, Ui::TextScroller
{
    Q_OBJECT

    public:
        explicit TextScroller(QWidget* parent = 0);
        int cgstatus = 0;

    private:
        QUdpSocket *socket;
        Q_SLOT void SendButtonHandler();
        Q_SLOT void clearButtonHandler();
        void GetStatus();
        void PrepareScrollText();
};
