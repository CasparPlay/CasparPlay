#pragma once

#include "Shared.h"
#include "ui_CGPlayout.h"

#include "Global.h"

#include <QtGui/QDialog>
#include <QtNetwork/QUdpSocket>

class WIDGETS_EXPORT CGPlayout : public QDialog, Ui::CGPlayout
{
    Q_OBJECT

    public:
        explicit CGPlayout(QWidget* parent = 0);

    private:
        QUdpSocket *cgsocket;
        Q_SLOT int SendCGCmd(void);
};
