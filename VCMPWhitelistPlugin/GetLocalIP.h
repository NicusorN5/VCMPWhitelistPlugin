#pragma once

#if WIN32

#include <winsock.h>
#pragma comment(lib,"Ws2_32.lib")

#include <Windows.h>

/// <summary>
/// Returns the local IPs used by the machine
/// <para>I'm too stupid to write that on my own, therefore the code is taken from there https://tangentsoft.net/wskfaq/examples/ipaddr.html
/// </para>
/// </summary>
/// <returns>A list of strings allocated with operator new[]</returns>
char** GetLocalIPs(int& errorcode,size_t &l);

#endif

//Idk about linux variant lol
// (please help)