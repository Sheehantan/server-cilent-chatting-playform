//#include <stdio.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>  // for inet_ntop()
//#pragma comment(lib,"ws2_32.lib")
//
//int main(int argc, char* argv[])
//{
//    //��ʼ��WSA
//    WORD sockVersion = MAKEWORD(2, 2);
//    WSADATA wsaData;
//    if (WSAStartup(sockVersion, &wsaData) != 0)
//    {
//        return 0;
//    }
//    //�����׽��� (Windows Socket API )
//    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//    if (slisten == INVALID_SOCKET)
//    {
//        printf("socket error !");
//        return 0;
//    }
//    //��IP�Ͷ˿�
//    sockaddr_in sin;
//    sin.sin_family = AF_INET;
//    sin.sin_port = htons(2046);
//    sin.sin_addr.S_un.S_addr = INADDR_ANY;
//    if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
//    {
//        printf("bind error !");
//    }
//    //��ʼ����
//    if (listen(slisten, 5) == SOCKET_ERROR)
//    {
//        printf("listen error !");
//        return 0;
//    }
//    //ѭ����������
//    SOCKET sClient;
//    sockaddr_in remoteAddr;
//    int nAddrlen = sizeof(remoteAddr);
//    char revData[255];
//    char clientIP[INET_ADDRSTRLEN];  // �洢�ͻ���IP��ַ
//
//    while (true)
//    {
//        printf("�ȴ�����...\n");
//        sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
//        if (sClient == INVALID_SOCKET)
//        {
//            printf("accept error !");
//            continue;
//        }
//        // ʹ�� inet_ntop() ��� inet_ntoa()
//        inet_ntop(AF_INET, &remoteAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
//        printf("���ܵ�һ�����ӣ�%s \r\n", clientIP);
//
//        //��������
//        int ret = recv(sClient, revData, 255, 0);
//        if (ret > 0)
//        {
//            revData[ret] = 0x00;
//            printf(revData);
//            printf("\n");
//        }
//        //��������
//        const char* sendData = "��ã�TCP�ͻ��ˣ�\n";
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
    // ��ʼ��WSA
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0)
    {
        return 0;
    }

    // �����׽��� (Windows Socket API)
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (slisten == INVALID_SOCKET)
    {
        printf("socket error !");
        return 0;
    }

    // ��IP�Ͷ˿�
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(2046);  // ʹ������Ҫ�Ķ˿ں�
    sin.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        printf("bind error !");
    }

    // ��ʼ����
    if (listen(slisten, 5) == SOCKET_ERROR)
    {
        printf("listen error !");
        return 0;
    }

    // ѭ����������
    SOCKET sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[255];
    char clientIP[INET_ADDRSTRLEN];  // �洢�ͻ���IP��ַ

    while (true)
    {
        printf("�ȴ�����...\n");
        sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
        if (sClient == INVALID_SOCKET)
        {
            printf("accept error !");
            continue;
        }

        // ʹ�� inet_ntop() ��� inet_ntoa()
        inet_ntop(AF_INET, &remoteAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
        printf("���ܵ�һ�����ӣ�%s \r\n", clientIP);

        // ��������
        int ret = recv(sClient, revData, 255, 0);
        if (ret > 0)
        {
            revData[ret] = 0x00;  // �����ֹ��
            printf("�ͻ��˷��͵���Ϣ: %s\n", revData);

            // ���ͻ�Ӧ���ݸ��ͻ���
            printf("������Ҫ���͸��ͻ��˵���Ϣ: ");
            char sendData[255];
            fgets(sendData, 255, stdin);  // �ӱ�׼�����ȡ��������
            sendData[strcspn(sendData, "\n")] = 0;  // ȥ�����з�

            // �����û��������Ϣ���ͻ���
            send(sClient, sendData, strlen(sendData), 0);
        }

        // �رտͻ�������
        closesocket(sClient);
    }

    // �رռ����׽���
    closesocket(slisten);
    WSACleanup();
    return 0;
}
