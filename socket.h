#ifndef SOCKET_H
#define SOCKET_H

#include <QString>
#include <QHostInfo>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

class Socket
{
public:
    Socket();
    ~Socket();
    void Connect();
    void Send(QString message);
    QString Recv(int bufSize);
    void Close();
private:
    int fd;
    struct sockaddr_in addr;
    bool isConnect = false;
};

class SocketException
{
public:
    SocketException(QString m = ""):message(m){}
    QString message;
};

#endif // SOCKET_H
