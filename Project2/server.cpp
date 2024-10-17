//#include <stdio.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>  // for inet_ntop()
//#pragma comment(lib,"ws2_32.lib")
//
//int main(int argc, char* argv[])
//{
//    //初始化WSA
//    WORD sockVersion = MAKEWORD(2, 2);
//    WSADATA wsaData;
//    if (WSAStartup(sockVersion, &wsaData) != 0)
//    {
//        return 0;
//    }
//    //创建套接字 (Windows Socket API )
//    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//    if (slisten == INVALID_SOCKET)
//    {
//        printf("socket error !");
//        return 0;
//    }
//    //绑定IP和端口
//    sockaddr_in sin;
//    sin.sin_family = AF_INET;
//    sin.sin_port = htons(2046);
//    sin.sin_addr.S_un.S_addr = INADDR_ANY;
//    if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
//    {
//        printf("bind error !");
//    }
//    //开始监听
//    if (listen(slisten, 5) == SOCKET_ERROR)
//    {
//        printf("listen error !");
//        return 0;
//    }
//    //循环接收数据
//    SOCKET sClient;
//    sockaddr_in remoteAddr;
//    int nAddrlen = sizeof(remoteAddr);
//    char revData[255];
//    char clientIP[INET_ADDRSTRLEN];  // 存储客户端IP地址
//
//    while (true)
//    {
//        printf("等待连接...\n");
//        sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
//        if (sClient == INVALID_SOCKET)
//        {
//            printf("accept error !");
//            continue;
//        }
//        // 使用 inet_ntop() 替代 inet_ntoa()
//        inet_ntop(AF_INET, &remoteAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
//        printf("接受到一个连接：%s \r\n", clientIP);
//
//        //接收数据
//        int ret = recv(sClient, revData, 255, 0);
//        if (ret > 0)
//        {
//            revData[ret] = 0x00;
//            printf(revData);
//            printf("\n");
//        }
//        //发送数据
//        const char* sendData = "你好，TCP客户端！\n";
//        send(sClient, sendData, strlen(sendData), 0);
//        closesocket(sClient);
//    }
//    closesocket(slisten);
//    WSACleanup();
//    return 0;
//}

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>  // for inet_ntop()
#include <string.h>
#pragma comment(lib,"ws2_32.lib")

int main(int argc, char* argv[])
{
    // 初始化WSA
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0)
    {
        return 0;
    }

    // 创建套接字 (Windows Socket API)
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (slisten == INVALID_SOCKET)
    {
        printf("socket error !");
        return 0;
    }

    // 绑定IP和端口
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(2046);  // 使用你想要的端口号
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        printf("bind error !");
    }

    // 开始监听
    if (listen(slisten, 5) == SOCKET_ERROR)
    {
        printf("listen error !");
        return 0;
    }

    // 循环接收数据
    SOCKET sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[255];
    char clientIP[INET_ADDRSTRLEN];  // 存储客户端IP地址

    while (true)
    {
        printf("等待连接...\n");
        sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
        if (sClient == INVALID_SOCKET)
        {
            printf("accept error !");
            continue;
        }

        // 使用 inet_ntop() 替代 inet_ntoa()
        inet_ntop(AF_INET, &remoteAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
        printf("接受到一个连接：%s \r\n", clientIP);

        // 接收数据
        int ret = recv(sClient, revData, 255, 0);
        if (ret > 0)
        {
            revData[ret] = 0x00;  // 添加终止符
            printf("客户端发送的消息: %s\n", revData);

            // 发送回应数据给客户端
            printf("请输入要发送给客户端的消息: ");
            char sendData[255];
            fgets(sendData, 255, stdin);  // 从标准输入读取发送数据
            sendData[strcspn(sendData, "\n")] = 0;  // 去掉换行符

            // 发送用户输入的消息给客户端
            send(sClient, sendData, strlen(sendData), 0);
        }

        // 关闭客户端连接
        closesocket(sClient);
    }

    // 关闭监听套接字
    closesocket(slisten);
    WSACleanup();
    return 0;
}
