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
** Usage example for NetDebugLog
** Client side logging functions to connect to NetDebugPlot
** Romain Dura
** http://www.shazbits.com/netdebuglog
*/

#include <iostream>
#include "NetDebugLog/NetDebugLog.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable: 4127)
#else
#include <stdlib.h>
void Sleep(int ms)
{
	usleep(ms * 1000);
}
#pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

int main(int, char**)
{
	const int testMode = 0;
	static int delay = 33;

	// Those are default
	//SetNetLogIPAddress("127.0.0.1");
	//SetNetLogPort(13000);
	//SetNetLogEnabled(true);

	if (testMode == 0)
	{
		srand(0);
		while (true)
		{
			float val = (float)((rand() % 25) * ((rand() % 2) == 0 ? 1 : -1));
			NetLog(val);
			NetLog("test", val + (float)(rand() % 25));
			Sleep(delay);
		}
	}
	else
	{
		std::cout << "Enter series value" << std::endl;
		float val = 0.0f;
		while (std::cin >> val)
		{
			NetLog("seriesA", val);
			NetLog("seriesB", val+3);
			NetLog("seriesC", val+6);
			NetLog("seriesD", val+9);
			NetLog("seriesE", val+12);
			NetLog("seriesF", val+15);
			NetLog("seriesG", val+18);
			NetLog("seriesH", val+21);
		}
	}

	return 0;
}

#ifdef _WIN32
#pragma warning(pop)
#endif
