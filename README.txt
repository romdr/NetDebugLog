NetDebugLog

NetDebugLog is an open source C++ client for NetDebugPlot (http://www.shazbits.com/netdebugplot). There are 1 .cpp and 1 .h files to include in your project to make it all work. It consists of a TCP client, a couple configuration and logging functions. It's currently implemented with Winsock and QueryPerformanceCounter (high resolution timer) but could easily be ported to other platforms. 


Example:
--------

#include <iostream>
#include "NetDebugLog/NetDebugLog.h"

int main(int argc, char* argv[])
{
	static int delay = 33;

	// Those are default
	//SetNetLogIPAddress("127.0.0.1");
	//SetNetLogPort(13000);
	//SetNetLogEnabled(false);

	srand(0);
	while (true)
	{
		float val1 = (float)((rand() % 25) * (rand() % 2 == 0 ? 1 : -1));
		float val2 = val1 + (float)(rand() % 25);

		NetLog(val1);
		NetLog("test", val2);

		Sleep(delay);
	}

	return 0;
}


Romain Dura
http://www.shazbits.com/netdebuglog
