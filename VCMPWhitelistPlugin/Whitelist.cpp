#include "Whitelist.h"

uint8_t CheckPlayer(char* name, size_t name_s, const char* password, const char* ip)
{
	//Make a copy of the name, since the size_t parameter tells me this is not a null-terminated string
	char* namebuff = new char[name_s + 1];
	memcpy(namebuff, name, name_s);
	namebuff[name_s] = 0; //null-terminate the name string

	size_t numIPs = IPs.size();
	//check IP
	for (unsigned i = 0; i < numIPs; i++)
	{
		if(IPs[i] == ip) return 1;
	}

	size_t NumNicks = Nicks.size();
	//check nickname
	for (unsigned i = 0; i < NumNicks; i++)
	{
		if (Nicks[i] == namebuff) return 1;
	}

	//return false if not found
	return 0;
}
