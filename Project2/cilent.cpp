#include<WINSOCK2.H>
#include<STDIO.H>
#include<iostream>
#include<cstring>
#include <WS2tcpip.h> 
using namespace std;
#pragma comment(lib, "ws2_32.lib")
int main()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
	while (true) {
		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sclient == INVALID_SOCKET)
		{
			printf("invalid socket!");
			return 0;
		}

		// ���÷�������ַ�Ͷ˿�
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(2046);  // �����������Ķ˿�

		// ʹ�� inet_pton ��� inet_addr ������IP��ַ
		if (inet_pton(AF_INET, "172.27.63.154", &serAddr.sin_addr) <= 0)  // �滻Ϊ�������ľ�����IP
		{
			printf("Invalid address / Address not supported\n");
			return 0;
		}
		if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{ //����ʧ��
			printf("connect error !");
			closesocket(sclient);
			return 0;
		}
		string data;
		printf("���͸�����������Ϣ:");
		cin >> data;
		const char* sendData;
		sendData = data.c_str(); //stringתconst char*
		//char * sendData = "��ã�TCP����ˣ����ǿͻ���\n";
		send(sclient, sendData, strlen(sendData), 0);
		//send()������������ָ����socket�����Է�����
	   //int send(int s, const void * msg, int len, unsigned int flags)
		//sΪ�ѽ��������ӵ�socket��msgָ���������ݣ�len��Ϊ���ݳ��ȣ�����flagsһ����0
		//�ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ���-1������ԭ�����error
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0) {
			recData[ret] = 0x00;
			printf("�յ��ķ�������Ϣ: %s \n",recData);
		}
		closesocket(sclient);
	}
	WSACleanup();
	return 0;
}