#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "popdragdropbrowsewidget.h"
#include <QDir>
#include <QTcpSocket>
#include <QNetworkConfigurationManager>
#include <QSettings>
#include <QTimer>
#include <QDebug>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!QDir("Data").exists())
    {
        QDir().mkdir("Data");
    }

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
    {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
        networkSession->open();
    }
    tcpSocket=new QTcpSocket;
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(firstConnect()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    timer= new QTimer;
    buttonConnectState=true;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_UploadNewFileButton_clicked()
{
    pop=new PopDragDropBrowseWidget;
    pop->setCopyDir(QString("Data"));

    if(pop->exec())
    {

    }
}

void MainWindow::requestConnection()
{
    if(tcpSocket->state()==QAbstractSocket::ConnectedState)
    {
        showMessage("Already connected to "+ui->IpAddressBar->text()+"::"+ui->PortName->text());
        return ;
    }
    //ui->ConnectButton->setEnabled(false);
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(ui->IpAddressBar->text(),
                             ui->PortName->text().toInt());
    ui->IpAddressBar->setReadOnly(true);
    ui->PortName->setReadOnly(true);
    showMessage("Requesting Connection to "+ui->IpAddressBar->text()+"::"+ui->PortName->text());

    ui->ConnectButton->setText("Disconnect");
    buttonConnectState=false;
}

void MainWindow::closeConnection()
{
    ui->IpAddressBar->setReadOnly(true);
    ui->PortName->setReadOnly(true);
    tcpSocket->abort();
    showMessage("Abort Connection From to "+ui->IpAddressBar->text()+"::"+ui->PortName->text());

    ui->IpAddressBar->setReadOnly(false);
    ui->PortName->setReadOnly(false);

    ui->ConnectButton->setText("Connect");
    buttonConnectState=true;
}

void MainWindow::firstConnect()
{
    QString x=ui->StudentIdEdit->text();

    tcpSocket->write(x.toLatin1());

    ui->ConnectButton->setEnabled(true);
    showMessage("Connected to "+ui->IpAddressBar->text()+"::"+ui->PortName->text());

}

void MainWindow::readyRead()
{
    QByteArray data=tcpSocket->readAll();
    showMessage(QString(data));
}

void MainWindow::on_ConnectButton_clicked()
{
    if(buttonConnectState)
    {
        requestConnection();
    }
    else
    {
        closeConnection();
    }
}

void MainWindow::showMessage(QString msg)
{
    ui->MessageCenter->appendPlainText(QDateTime::currentDateTime().toString("dd-MMM-yy h:mm ap - ")+msg);
}

void MainWindow::disconnected()
{
    ui->ConnectButton->setText("Connect");
    buttonConnectState=true;
    showMessage("Server Lost: No server listenning to "+ui->IpAddressBar->text()+"::"+ui->PortName->text());
}
