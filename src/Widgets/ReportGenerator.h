#pragma once

#include "Shared.h"
#include "Global.h"

#include "ui_ReportGenerator.h"

#include <QtNetwork/QTcpSocket>
#include <QtGui/QDialog>

class WIDGETS_EXPORT ReportGenerator: public QDialog, Ui::ReportGenerator
{
    Q_OBJECT

    public:
        explicit ReportGenerator(QWidget* parent = 0);
    ~ReportGenerator();

    private:
        bool primaryup, buddyup;
        QTcpSocket *reportsock, *auxsock;
        QList<QString> reporttag, auxreporttag;
        void refreshReport();
        QString targetdate;

        Q_SLOT void SendReportRequestToBuddy();
        Q_SLOT void GetBuddyReport();
        Q_SLOT void MarkBuddyDisconnected();
        Q_SLOT void DisplayErrorBuddy();

        Q_SLOT void SendReportRequest();
        Q_SLOT void GetServerReport();
        Q_SLOT void setConnected();
        Q_SLOT void MarkPrimaryDisconnected();
        Q_SLOT void GetReport();
        Q_SLOT void DisplayError();
        Q_SLOT void ExportReport();
};
