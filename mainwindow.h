#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "popdragdropbrowsewidget.h"
#include <QNetworkSession>
#include <QTcpSocket>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void requestConnection();
    void closeConnection();

private slots:
    void on_UploadNewFileButton_clicked();

    void firstConnect();

    void on_ConnectButton_clicked();

    void readyRead();

    void disconnected();

    void showMessage(QString msg);

private:
    Ui::MainWindow *ui;
    PopDragDropBrowseWidget *pop;

    bool buttonConnectState;

    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;

    QTimer *timer;

    QNetworkSession *networkSession;

};

#endif // MAINWINDOW_H
