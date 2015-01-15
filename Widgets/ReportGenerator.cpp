#include "ReportGenerator.h"
#include "DatabaseManager.h"

#include <Qt/qmessagebox.h>
#include <QtXml/QXmlStreamReader>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

ReportGenerator::ReportGenerator(QWidget *parent): QDialog(parent)
{
    setupUi(this);

    this->primaryup = false;
    this->buddyup = false;

    QString host = DatabaseManager::getInstance().GetServerIp(0);
    QString host2 = DatabaseManager::getInstance().GetServerIp(1);

    this->auxsock = new QTcpSocket();
    this->auxsock->connectToHost(host2, 9000, QIODevice::WriteOnly|QIODevice::ReadOnly|QIODevice::Text);

    QObject::connect(this->generateButton, SIGNAL(clicked()), this, SLOT(GetBuddyReport()));
    QObject::connect(this->auxsock, SIGNAL(disconnected()), this, SLOT(MarkBuddyDisconnected()));
    QObject::connect(this->auxsock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(DisplayErrorBuddy()));

    this->reportsock = new QTcpSocket();
    this->reportsock->connectToHost(host, 9000, QIODevice::WriteOnly|QIODevice::ReadOnly|QIODevice::Text);

    QObject::connect(this->generateButton, SIGNAL(clicked()), this, SLOT(GetServerReport()));
    QObject::connect(this->reportsock, SIGNAL(disconnected()), this, SLOT(MarkPrimaryDisconnected()));
    QObject::connect(this->reportsock, SIGNAL(hostFound()), this, SLOT(GetReport()));
    QObject::connect(this->reportsock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(DisplayError()));

    QObject::connect(this->exportButton, SIGNAL(clicked()), this, SLOT(ExportReport()));

    this->fromDateEdit->setDate(QDate::currentDate());
    this->toDateEdit->setDate(QDate::currentDate());
}

ReportGenerator::~ReportGenerator()
{
    if (this->primaryup)
    {
        this->reporttag.clear();
        this->reportsock->disconnectFromHost();
        this->reportsock->close();
    }

    if (this->buddyup)
    {
        this->auxreporttag.clear();
        this->auxsock->disconnectFromHost();
        this->auxsock->close();
    }
}

void ReportGenerator::ExportReport()
{
    /*QByteArray data;
    QXmlStreamWriter *writer = new QXmlStreamWriter(&data);

    int nrow = this->reportTable->rowCount(), ncol = this->reportTable->columnCount();
    for (int i = 0; i < nrow; i++)
    {
        for (int j = 0; j < ncol; j++)
        {
            QTableWidgetItem *item;
            item = this->reportTable->itemAt(nrow, ncol);
            writer->writeTextElement("Commercial Name", item->text());
            j++;
            item = this->reportTable->itemAt(nrow, ++ncol);
            writer->writeTextElement("Start Time", item->text());
        }
    }*/
}

void ReportGenerator::refreshReport()
{
    bool dbopen = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","reportmysql-conn");
    QString val, dbprimary = DatabaseManager::getInstance().GetServerIp(0);

    qDebug() << "Db primary is: " << dbprimary;

    db.setHostName(dbprimary);
    db.setDatabaseName("casparcg");
    db.setUserName("root");
    db.setPassword("password");

    if (!db.open()) {
        qDebug() << "Database1 error occurred";
        dbopen = false;
        return;
    } else
        dbopen = true;

    int rowno = this->reportTable->rowCount();

    while (rowno > 0) {
        this->reportTable->removeRow(0);
        rowno--;
    }

    foreach (QString line, this->reporttag)
    {
        QString sqlQuery("SELECT pushtime FROM playlist WHERE state=2 AND name=\'");
        QTableWidgetItem *item1, *item2;
        QStringList linelist, videoname;
        QSqlQuery query(db);

        linelist = line.split("|");

        videoname = linelist[1].split(".");
        sqlQuery.append(videoname[0]);
        sqlQuery.append(QString("\'"));
        sqlQuery.append(" AND commercial=1");

        qDebug() << "Prepared Query " << sqlQuery;

        query.exec(sqlQuery);

        while (query.next()) {
            val = query.value(0).toString().split("T")[0];
            qDebug() << "tmp => " << query.value(0).toString().split("T")[0];
        }

        if (QString::compare(val, this->targetdate))
                continue;

        val.clear();
        rowno = this->reportTable->rowCount();

        this->reportTable->insertRow(rowno);
        item1 = new QTableWidgetItem(linelist[1]);
        this->reportTable->setItem(rowno, 0, item1);

        item2 = new QTableWidgetItem(linelist[0]);
        this->reportTable->setItem(rowno, 1, item2);
        query.clear();
    }

    if (dbopen)
        db.close();
    this->reporttag.clear();
}

void ReportGenerator::GetBuddyReport()
{
    QString thisline;
    qint64 ret;
    char buf[1024];

    if (this->buddyup == false)
        return;

    while (this->auxsock->bytesAvailable()) {
        ret = this->auxsock->readLine(buf,1024);
        if (ret > 0) {
            thisline = QString(buf);
            qDebug() << "Got from server" << thisline;
        }

        this->auxreporttag.append(thisline);
    }

    if (this->primaryup || this->buddyup)
        this->refreshReport();
}

void ReportGenerator::SendReportRequestToBuddy()
{
    this->buddyup = true;
    QMessageBox msgbox;
    qint64 ret;

    ret = this->auxsock->write("GETREPORT");
    this->auxsock->flush();
    if (ret >= 9) {
        qDebug() << "Command Sent To Remote Host";
    } else {
        msgbox.setText("Failed To Send Command To Buddy...");
        msgbox.exec();
    }
}

void ReportGenerator::GetReport()
{
}

void ReportGenerator::DisplayError()
{
    QMessageBox msgbox;

    msgbox.setWindowTitle("Warning!");
    msgbox.setText("Failed To Generate Report. Check your network connection");
    msgbox.exec();
}

void ReportGenerator::DisplayErrorBuddy()
{
    QMessageBox msgbox;

    msgbox.setWindowTitle("Warning!");
    msgbox.setText("Failed To Generate Report. Check buddy network connection");
    msgbox.exec();
}

void ReportGenerator::SendReportRequest()
{
}

void ReportGenerator::GetServerReport()
{
    QString thisline;
    qint64 ret;
    char buf[1024];

    this->targetdate = this->fromDateEdit->date().toString(Qt::ISODate);

    qDebug() << "TargetDate => " << this->targetdate;
    this->setConnected();

    while (this->reportsock->bytesAvailable()) {
        ret = this->reportsock->readLine(buf,1024);
        if (ret > 0) {
            thisline = QString(buf);
            qDebug() << "Got from server" << thisline;
        }

        this->reporttag.append(thisline);
    }

    if (this->primaryup || this->buddyup)
        this->refreshReport();
}

void ReportGenerator::setConnected()
{
    this->primaryup = true;
    QMessageBox msgbox;
    qint64 ret;
    QString command = QString("GETREPORT ") + QString(this->fromDateEdit->date().toString(Qt::ISODate)) + QString(":") + \
            QString(this->toDateEdit->date().toString(Qt::ISODate));
    qDebug() << command.toAscii();

    ret = this->reportsock->write(command.toAscii()); // GETREPORT
    this->reportsock->flush();
    if (ret >= 9) {
        qDebug() << "Command Sent To Remote Host";
    } else {
        msgbox.setText("Failed To Send Command To Remote Host...");
        msgbox.exec();
    }
}

void ReportGenerator::MarkPrimaryDisconnected()
{
    this->primaryup = false;
}

void ReportGenerator::MarkBuddyDisconnected()
{
    this->buddyup = false;
}
