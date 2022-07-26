#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>

class Client : public QWidget
{
    Q_OBJECT

    unsigned int cols;
    unsigned int rows;
    unsigned int *mix;

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

public slots:
    void onReadyRead();

private:
    QTcpSocket _socket;
};

#endif // CLIENT_H
