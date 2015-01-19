#include <CGPlayout.h>
#include <Qt/qmessagebox.h>

CGPlayout::CGPlayout(QWidget *parent): QDialog(parent)
{
    setupUi(this);
    QObject::connect(this->CGButton, SIGNAL(clicked()), this, SLOT(SendCGCmd()));
}

int CGPlayout::SendCGCmd(void)
{
    qDebug() << "Ready To Send CG Cmd\n";
    QHostAddress host("192.168.152.22"), host2("192.168.152.8");
    this->cgsocket = new QUdpSocket();
    QByteArray command = "squzee";
    int ret = this->cgsocket->writeDatagram(command, host, 8000);
    if (ret == -1) {
        QMessageBox msgbox;
        msgbox.setText("Failed to enable lower third on server\n");
        msgbox.exec();
    }

    ret = this->cgsocket->writeDatagram(command, host2, 8000);
    if (ret == -1) {
        QMessageBox msgbox;
        msgbox.setText("Failed to enable lower third on server2\n");
        msgbox.exec();
    }
    return 0;
}
