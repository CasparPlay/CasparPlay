#include "FetchMetadata.h"
#include "DatabaseManager.h"

#include <QUrl>
#include <QNetworkReply>
#include <Qt/qfile.h>
#include <Qt/qfiledialog.h>

// http://localhost:8080/razuna/global/api2/asset.cfc?method=getasset
//&api_key=95EBA00386A14431A14F99CF17583561&assetid=0A62F1BAD90A46C79698718B98C5E95E&assettype=vid
FetchMetadata::FetchMetadata(QWidget *parent): QDialog(parent)
{
    setupUi(this);
    this->manager = new QNetworkAccessManager(this);
    connect(this->manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(HandleReply(QNetworkReply*)));
    connect(this->confirmButton, SIGNAL(clicked()), this, SLOT(HandleConfirm()));
    this->GetFileName();
}

void FetchMetadata::GetFileName()
{
    QString path = "", apikey;
    path = QFileDialog::getOpenFileName(this, "Open File", "", "*.txt");
    if (path.size() > 0) {
        qDebug() << "You have entered " << path;
    } else
        return;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    apikey = DatabaseManager::getInstance().GetRazunaApiKey();

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        this->VideoItems.append(QString(line));
        QString request = "method=searchassets&api_key=";
        request = request + apikey; //95EBA00386A14431A14F99CF17583561";
        request = request + "&searchfor=";
        request = request + "\"" + QString(line) + "\"";
        this->SendRequest(QString("http://localhost:8080/razuna/global/api2/search.cfc"), request);
    }

    file.close();
}

void FetchMetadata::SendRequest(const QString& url, const QString& data)
{
    QString request = url + "?" + data;
    this->manager->get(QNetworkRequest(QUrl(request)));
}

void FetchMetadata::HandleConfirm()
{
    QHostAddress host("127.0.0.1");
    this->sock = new QUdpSocket();
    QByteArray command;

    QMap<QString, QString>::const_iterator i = this->VideoPathList.constBegin();
    while (i != this->VideoPathList.constEnd()) {
        command.append("copy:");
        command.append(i.key());
        command.append(",directory:");
        command.append(i.value());
        this->sock->writeDatagram(command, host, 5060);
        ++i;
        command.clear();
    }
}

void FetchMetadata::HandleReply(QNetworkReply *reply)
{
    QStringList strlist, desc;
    QString data = QString::fromUtf8(reply->readAll());
    strlist = data.split("\"DATA\"");

    desc = strlist[0].split(":");
    if (desc[1].split(",")[10] == "\"cloud_url_org\"")
    {
        QString param, url, header;
        // We need to extract id and need to get metadata
        url = "http://localhost:8080/razuna/global/api2/asset.cfc";
        strlist = strlist[1].split(",");
        param = strlist[0].remove(0, 3);
        param = param.remove(0, 1);
        param = param.remove(param.length()-1,1);
        header = QString("method=getasset&api_key=95EBA00386A14431A14F99CF17583561&assetid=");
        header = header + param + QString("&assettype=vid");
        this->SendRequest(url, header);
    } else {
        QString keywords, info, filename, path;
        QStringList tmpdesc;
        desc = strlist[1].split(":");
        tmpdesc = desc[1].split(",");
        keywords = tmpdesc[10];
        info = tmpdesc[11];
        filename = tmpdesc[1];
        int ret = data.indexOf("Directory :");
        if (ret != -1) {
            data = data.remove(0, ret+11);
            ret = data.indexOf("File Size :");
            if (ret != -1) {
                path = data.remove(ret,data.length());
                path.chop(4);
                path.append("/");
                this->VideoPathList.insert(filename, path);
            }
        }

        this->SetupMetadataTable(filename, info, keywords);
    }
    reply->deleteLater();
}

void FetchMetadata::SetupMetadataTable(QString fname, QString desc, QString keywords)
{
    int rowno = this->tableMetadata->rowCount();
    QTableWidgetItem *item1, *item2, *item3;

    this->tableMetadata->insertRow(rowno);
    item1 = new QTableWidgetItem(fname);
    this->tableMetadata->setItem(rowno, 0, item1);

    item2 = new QTableWidgetItem(desc);
    this->tableMetadata->setItem(rowno, 2, item2);

    item3 = new QTableWidgetItem(keywords);
    this->tableMetadata->setItem(rowno, 1, item3);
}

FetchMetadata::~FetchMetadata()
{
    this->manager->deleteLater();
}
