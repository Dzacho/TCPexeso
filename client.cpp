#include "client.h"

#include <iostream>
#include <QDebug>
#include <QHostAddress>

Client::Client(QWidget *parent) : QWidget(parent), _socket(this)
{
    _socket.connectToHost(QHostAddress("127.0.0.1"), 4242);
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

Client::~Client()
{

}

void Client::onReadyRead()
{
    QByteArray datas = _socket.readAll();
    qDebug() << datas;
    std::cout << datas.toStdString() << std::endl;
    _socket.write(QByteArray("ok !\n"));
}
