/*
** Copyright (c) 2012, Romain Dura romain@shazbits.com
** 
** Permission to use, copy, modify, and/or distribute this software for any 
** purpose with or without fee is hereby granted, provided that the above 
** copyright notice and this permission notice appear in all copies.
** 
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES 
** WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF 
** MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY 
** SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 
** WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 
** ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR 
** IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
** NetDebugLog
** Client side logging functions to connect to NetDebugPlot
** Romain Dura
** http://www.shazbits.com/netdebuglog
*/

#include "NetDebugLog.h"

#ifdef NETLOG
#pragma comment(lib, "wsock32.lib")


/*
** Configuration
*/

static char* NetLogIPAddress = "127.0.0.1";
static unsigned short NetLogPort = 13000;
static bool NetLogEnabled = true;

void SetNetLogIPAddress(char* ipAddress)
{
	NetLogIPAddress = ipAddress;
}

void SetNetLogPort(unsigned short port)
{
	NetLogPort = port;
}

void SetNetLogEnabled(bool enabled)
{
	NetLogEnabled = enabled;
}


/*
** Logging internals
*/

static double NetLogFirstMessageTime = 0.0;
static bool NetLogResetFirstMessageTime = true;

struct NetLogPacket
{
	char name[16];
	double x;
	double y;
};

static double NetLogGetHiResTime()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	return (double)(t.QuadPart * 1000.0 / f.QuadPart) / 1000.0;
}

static double NetLogGetHiResElapsedTime()
{
	if (NetLogResetFirstMessageTime)
	{
		NetLogFirstMessageTime = NetLogGetHiResTime();
		NetLogResetFirstMessageTime = false;
	}
	return NetLogGetHiResTime() - NetLogFirstMessageTime;
}


/*
** Logging functions
*/

// noname, x is automatic (current time)
void NetLog(double yVal)
{
	if (NetLogEnabled)
		NetLog("noname", NetLogGetHiResElapsedTime(), yVal);
}

// noname
void NetLog(double timeVal, double yVal)
{
	if (NetLogEnabled)
		NetLog("noname", timeVal, yVal);
}

// x is automatic (current time)
void NetLog(const char* name, double yVal)
{
	if (NetLogEnabled)
		NetLog(name, NetLogGetHiResElapsedTime(), yVal);
}

// Disable warning 'sprintf': This function or variable may be unsafe. Consider using sprintf_s instead.
// sprintf_s adds non zero characters after the \0, sprintf doesn't
#pragma warning(push)
#pragma warning(disable: 4996)

void NetLog(const char* name, double timeVal, double yVal)
{
	if (NetLogEnabled)
	{
		static TCPClient tcpClient;

		bool sendMessage = true;
		if (!tcpClient.IsConnected())
		{
			sendMessage = tcpClient.Connect(NetLogIPAddress, NetLogPort);
			NetLogResetFirstMessageTime = !sendMessage;
		}
		if (sendMessage)
		{
			NetLogPacket packet = {0};
			sprintf(packet.name, "%s", name);
			packet.x = timeVal;
			packet.y = yVal;

			NetLogResetFirstMessageTime = !tcpClient.Send((const char*)&packet, sizeof(packet));
		}
	}
}

#pragma warning(pop)

/*
** TCP Client
*/

TCPClient::TCPClient()
: m_Socket(INVALID_SOCKET)
, EnableErrorLog(true)
, EnableMessageLog(false)
, m_Connected(false)
{
}

TCPClient::~TCPClient()
{
	Destroy();
}

bool TCPClient::Create()
{
	WSADATA wsaData;
	const unsigned short wVersionRequested = MAKEWORD( 2, 2 );
	const int err = WSAStartup(wVersionRequested, &wsaData);
	if (err || (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2))
	{
		if (EnableErrorLog)
			printf("TCPClient error: Could not find useable sock dll. Code %d.\n", WSAGetLastError());
		return false;
	}

	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Socket == INVALID_SOCKET)
	{
		if (EnableErrorLog)
			printf("TCPClient error: Could not initialize socket. Code %d.\n", WSAGetLastError());
		return false;
	}

	return true;
}

void TCPClient::Destroy()
{
	if (m_Socket != INVALID_SOCKET)
	{
		closesocket(m_Socket);
		m_Socket = INVALID_SOCKET;
		m_Connected = false;
	}
}

bool TCPClient::Connect(const char* hostname, unsigned short port)
{
	if (Create())
	{
		struct sockaddr_in addr;
		addr.sin_family = AF_INET ;
		addr.sin_port = htons(port);
		memset(&(addr.sin_zero), 0, 8);
		addr.sin_addr.s_addr = inet_addr(hostname);

		if (connect(m_Socket, (struct sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR)
		{
			if (EnableMessageLog)
				printf("TCPClient: Connected to %s:%d.\n", hostname, port);
			m_Connected = true;
			return true;
		}

		if (EnableErrorLog)
			printf("TCPClient error: Could not connect to %s:%d. Code %d.\n", hostname, port, WSAGetLastError());
	}

	Destroy();
	return false;
}

bool TCPClient::Send(const char* data, unsigned int size)
{
	int sentBytes = 0;
	int totalSentBytes = 0;
	
	while ((unsigned int)totalSentBytes < size)
	{
		sentBytes = send(m_Socket, data + sentBytes, size - sentBytes, 0);
		if (sentBytes == SOCKET_ERROR)
		{
			if (EnableErrorLog)
				fprintf(stderr, "TCPClient error: Could not send data. Code %d.\n", WSAGetLastError());
			m_Connected = false;
			return false;
		}

		if (EnableMessageLog)
			printf("TCPClient: Sent bytes %d\n", sentBytes);

		totalSentBytes += sentBytes;
	}

	return true;
}

#endif
