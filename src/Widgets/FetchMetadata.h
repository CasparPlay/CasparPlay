#pragma once

#include "Shared.h"
#include "Global.h"
#include "ui_FetchMetadata.h"

#include <QNetworkAccessManager>
#include <QtGui/QDialog>
#include <QtNetwork/QUdpSocket>

class WIDGETS_EXPORT FetchMetadata: public QDialog, Ui::FetchMetadata
{
    Q_OBJECT

    public:
        explicit FetchMetadata(QWidget* parent = 0);
    ~FetchMetadata();

        void SetupMetadataTable(QString fname, QString info, QString desc);
        void SendRequest(const QString& url, const QString& data);
        void GetFileName();

        QNetworkAccessManager *manager;
        QList<QString> VideoItems;
        QMap<QString, QString> VideoPathList;
        QUdpSocket *sock;

    private:
        Q_SLOT void HandleReply(QNetworkReply*);
        Q_SLOT void HandleConfirm();
        QString apikey;
};
