#include "socket.h"

Socket::Socket()
{
    fd = socket(AF_INET , SOCK_STREAM , 0);
    if (fd == -1){
        throw SocketException("Fail to create a socket.");
    }
}

void Socket::Connect()
{

    QHostInfo info = QHostInfo::fromName( "mysyu.ddns.net" );

    if(info.addresses().isEmpty())
        throw SocketException("Fail to recognize the IP address");
    bzero(&addr,sizeof(addr));
    addr.sin_family = PF_INET;
    addr.sin_addr.s_addr = inet_addr(info.addresses().first().toString().toStdString().c_str());
    addr.sin_port = htons(981);

    int err = connect(fd,(struct sockaddr *)&addr,sizeof(addr));
    qDebug()<<err;

    if( err == -1){
        throw SocketException("Fail to Connect");
    }

    isConnect = true;
}

void Socket::Send(QString message)
{
    send(fd,message.toStdString().c_str(),message.length(),0);
}

QString Socket::Recv(int bufSize)
{
    char* buf = new char[bufSize]{};
    recv(fd,buf,bufSize,0);
    QString message(buf);
    delete[] buf;
    return message;
}

void Socket::Close()
{
    if(isConnect)
    {
        close(fd);
        isConnect = false;
    }
}

Socket::~Socket()
{
    Close();
}
