#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "VCMP.h"
#include "Whitelist.h"
#include "GetLocalIP.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

#ifdef WIN32
#define EXPORT __declspec(dllexport)

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);

#else
#define EXPORT
#endif

extern "C" EXPORT unsigned int VcmpPluginInit(PluginFuncs * pluginFuncs, PluginCallbacks * pluginCalls, PluginInfo * pluginInfo);

extern std::vector<std::string> IPs;

extern std::vector<std::string> Nicks;