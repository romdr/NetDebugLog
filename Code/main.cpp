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
#include <tchar.h>

#include "NetDebugLog/NetDebugLog.h"

int _tmain(int argc, _TCHAR* argv[])
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
			int val = rand() % 25;
			val *= (rand() % 2 == 0 ? 1 : -1);
			NetLog((float)val);
			NetLog("test", (float)val + (rand() % 25));
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
