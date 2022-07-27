#include "server.h"
#include "debug.h"

#include <iostream>
#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>

Server::Server(QWidget *parent) : QWidget(parent), _server(this)
{

}

Server::~Server()
{

}

void Server::sendArray(unsigned int *array, unsigned int rows, unsigned int cols)
{
#ifdef DEBUG_H
    std::cout << "Sending Array" << std::endl;
#endif
    _socket->write(QByteArray("array\n"));
    _socket->write(QByteArray("%1\n", rows));
    _socket->write(QByteArray("%1\n", cols));
    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            _socket->write(QByteArray("%1¨\n", array[cols * i + j]));
        }
    }
#ifdef DEBUG_H
    std::cout << "Array sended" << std::endl;
#endif
}

void Server::waitForClient()
{
#ifdef DEBUG_H
    std::cout << "Waiting for client" << std::endl;
#endif
    _server.listen(QHostAddress::Any, 4242);
    connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
//    QByteArray datas;
    QMessageBox::information(this, tr("Waiting"), tr("After clicking 'OK' will be waiting 10 s for client"));
    if(!_server.waitForNewConnection(10000))
    {
        throw bool(0);
#ifdef DEBUG_H
    std::cout << "Throwing exception - client not connected" << std::endl;
#endif
    }
#ifdef DEBUG_H
    std::cout << "Client connected" << std::endl;
#endif
}

void Server::onNewConnection()
{
#ifdef DEBUG_H
    std::cout << "connecting" << std::endl;
#endif

//    QTcpSocket *clientSocket = _server.nextPendingConnection();
//    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
//    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
#ifdef DEBUG_H
    std::cout << "socket address: " << _socket << std::endl;
#endif
    _socket = _server.nextPendingConnection();
//    _socket->setCurrentReadChannel(1);
//    _socket->setCurrentWriteChannel(1);
#ifdef DEBUG_H
    std::cout << "socket address: " << _socket << std::endl;
#endif
    connect(_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

//    _sockets.push_back(clientSocket);
//    for (QTcpSocket* socket : _sockets)
//    {
//        socket->write(QByteArray("connected\n"));
//    }
    std:: cout << _socket->write(QByteArray("connected\n")) << std::endl;
#ifdef DEBUG_H
    std::cout << "client connected" << std::endl;
#endif
}

void Server::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
//        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
//        _sockets.removeOne(sender);
    }
}

void Server::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();
//    for (QTcpSocket* socket : _sockets) {
//        if (socket != sender)
//            socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + datas.toStdString()));
//    }
}
