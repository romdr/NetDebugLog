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

#pragma once

#define NETLOG
#ifdef NETLOG

#include <stdio.h>
#ifdef _WIN32
	#include <winsock2.h>
	#include <Ws2tcpip.h>
	#include <windows.h>
#else
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <string.h>
	#include <sys/time.h>
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define closesocket close
	typedef int SOCKET;
#endif
#include <time.h>


/*
** Configuration
*/

void SetNetLogIPAddress(char* hostname);
void SetNetLogPort(unsigned short port);
void SetNetLogEnabled(bool enabled);

/*
** Logging functions
*/

void NetLog(double yVal);										// noname, x is automatic (current time)
void NetLog(double timeVal, double yVal);						// noname
void NetLog(const char* name, double yVal);						// x is automatic (current time)
void NetLog(const char* name, double timeVal, double yVal);


/*
** TCP Client
*/

class TCPClient
{
public:
	TCPClient();
	~TCPClient();

	void Destroy();
	bool Connect(const char* hostname, unsigned short port);
	bool Send(const char* data, unsigned int size);
	bool IsConnected() const { return m_Connected; }

	bool EnableErrorLog;
	bool EnableMessageLog;

protected:
	bool Create();

	bool m_Connected;
	SOCKET m_Socket;
};

#else
#define SetNetLogIPAddress(hostname)
#define SetNetLogPort(port)
#define SetNetLogEnabled(enabled)
#define NetLog(yVal)
#define NetLog(timeVal, yVal)
#define NetLog(name, yVal)
#define NetLog(name, timeVal, yVal)
#endif
