#include "client.h"
#include "debug.h"

#include <iostream>
#include <QDebug>
#include <QHostAddress>

Client::Client(QWidget *parent) : QWidget(parent), _socket(this)
{
    _socket.connectToHost(QHostAddress("127.0.0.1"), 4242);
//    _socket.setCurrentReadChannel(1);
//    _socket.setCurrentWriteChannel(1);
//#ifdef DEBUG_H
//    std::cout << "socket address: " << &_socket << std::endl;
//#endif
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
#ifdef DEBUG_H
    std::cout << "client signal readyRead connected" << std::endl;
#endif
}

Client::~Client()
{

}

void Client::onReadyRead()
{
#ifdef DEBUG_H
    std::cout << "client got signal readyRead" << std::endl;
#endif
    QByteArray datas = _socket.readAll();
//    qDebug() << datas;
#ifdef DEBUG_H
    std::cout << "client got data: " << datas.toStdString() << std::endl;
#endif
    if(datas.toStdString() == "connected\n")
    {
        _socket.write(QByteArray("ok\n"));
#ifdef DEBUG_H
        std::cout << "Connected to server" << std::endl;
#endif
    }
    if(datas.toStdString() == "array\n")
    {
        rows = _socket.readAll().toUInt();
        cols = _socket.readAll().toUInt();
#ifdef DEBUG_H
        std::cout << "rows = " << rows << ", cols = " << cols << std::endl;
#endif
    }
}
