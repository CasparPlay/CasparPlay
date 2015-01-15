#include "TextScroller.h"
#include "DatabaseManager.h"
#include <Qt/qmessagebox.h>

TextScroller::TextScroller(QWidget* parent)
    : QDialog(parent)
{
    setupUi(this);
    this->PrepareScrollText();
    QObject::connect(this->SendButton, SIGNAL(clicked()), this, SLOT(SendButtonHandler()));
    QObject::connect(this->clearButton, SIGNAL(clicked()), this, SLOT(clearButtonHandler()));
}

void TextScroller::PrepareScrollText()
{
    QString text = DatabaseManager::getInstance().GetScrollerText();

    this->textEdit->setText(text);
}

void TextScroller::clearButtonHandler()
{
    QHostAddress primaryhost = QHostAddress(DatabaseManager::getInstance().GetServerIp(0));
    QHostAddress secondaryhost = QHostAddress(DatabaseManager::getInstance().GetServerIp(1));

    QByteArray command = "clearcg";

    DatabaseManager::getInstance().ScrollerTextDel();

    qDebug() << "Sending Clear Command to server\n";

    this->socket = new QUdpSocket();
    int ret = this->socket->writeDatagram(command, primaryhost, 8000);
    if (ret == -1) {
        QMessageBox msgbox;
        msgbox.setText("Unable to Clear Scroll. Make sure server1 is open\n");
        msgbox.exec();
    }
    this->socket->close();
    free(this->socket);

    this->socket = new QUdpSocket();
    ret = this->socket->writeDatagram(command, secondaryhost, 8000);
    if (ret == -1) {
        QMessageBox msgbox;
        msgbox.setText("Unable to Clear Scroll. Make sure server2 is open\n");
        msgbox.exec();
    }
    this->socket->close();
    free(this->socket);

    this->textEdit->clear();
}

void TextScroller::SendButtonHandler()
{
    // Utilize secondaryhost later
    QHostAddress primaryhost = QHostAddress(DatabaseManager::getInstance().GetServerIp(0));
    QHostAddress secondaryhost = QHostAddress(DatabaseManager::getInstance().GetServerIp(1));
    qint64 ret = 0, total = 0, size = this->textEdit->toPlainText().size();

    if (size == 0)
        return;

    DatabaseManager::getInstance().ScrollerTextInsert(this->textEdit->toPlainText());

    QString data = "<?xml version=\"1.0\" encoding=\"utf-16\" standalone=\"yes\"?>\n";
    data = data + "<NewScrollData>\n";
    data = data + "<ScrollData>\n";
    data = data + "<Story>\n";
    data = data + this->textEdit->toPlainText();
    data = data + "</Story>\n";
    data = data + "</ScrollData>\n";
    data = data + "</NewScrollData>\n";

    //qDebug() << "You have typed: =>" << data;
    QByteArray dg = data.toUtf8();

    this->socket = new QUdpSocket();
    do {
        ret = this->socket->writeDatagram(dg, primaryhost, 8000);
        qDebug()<<"RET IS FROM HOST1: " << ret;

        if (ret == -1) {
            QMessageBox msgbox;
            msgbox.setText("Unable to Sent Text For Playout. Make sure server1 is open\n");
            msgbox.exec();
            break;
        }
        total =+ ret;
    } while (total <= size);

    this->socket->close();
    free(this->socket);

    this->socket = new QUdpSocket();
    total = 0;
    do {
        ret = this->socket->writeDatagram(dg, secondaryhost, 8000);
        qDebug()<<"RET IS FROM secondaryhost: " << ret;
        if (ret == -1) {
            QMessageBox msgbox;
            msgbox.setText("Unable to Sent Text For Playout. Make sure server2 is open\n");
            msgbox.exec();
            break;
        }
        total = total + ret;
    } while (total <= size);

    this->socket->close();
    this->textEdit->clear();
    free(this->socket);
    this->clearButton->setEnabled(true);
}
