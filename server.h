#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();
//    friend class Pexeso;
    void sendArray(unsigned int *array, unsigned int rows, unsigned int cols);
    void waitForClient();

public slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();

private:
    QTcpServer  _server;
    QTcpSocket *_socket = nullptr;
    QList<QTcpSocket*>  _sockets;
};

#endif // SERVER_H
