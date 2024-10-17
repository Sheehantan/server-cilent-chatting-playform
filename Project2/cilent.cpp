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

		// 配置服务器地址和端口
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(2046);  // 服务器监听的端口

		// 使用 inet_pton 替代 inet_addr 来解析IP地址
		if (inet_pton(AF_INET, "172.27.63.154", &serAddr.sin_addr) <= 0)  // 替换为服务器的局域网IP
		{
			printf("Invalid address / Address not supported\n");
			return 0;
		}
		if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{ //连接失败
			printf("connect error !");
			closesocket(sclient);
			return 0;
		}
		string data;
		printf("发送给服务器的消息:");
		cin >> data;
		const char* sendData;
		sendData = data.c_str(); //string转const char*
		//char * sendData = "你好，TCP服务端，我是客户端\n";
		send(sclient, sendData, strlen(sendData), 0);
		//send()用来将数据由指定的socket传给对方主机
	   //int send(int s, const void * msg, int len, unsigned int flags)
		//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
		//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0) {
			recData[ret] = 0x00;
			printf("收到的服务器消息: %s \n",recData);
		}
		closesocket(sclient);
	}
	WSACleanup();
	return 0;
}