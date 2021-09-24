#include "GetLocalIP.h"

#if WIN32

char** GetLocalIPs(int& errorcode,size_t &l)
{
	l = 0; //lenght is 0 if operation is failed.
	char hostname[80]; //local buffer for the hostname

	int r = gethostname(hostname, 80); //get hostname
	if (r == SOCKET_ERROR) //check for error
	{
		//epic fail
		errorcode = 1; //we failed to get the host name
		return nullptr;
	}

	hostent* ptrHostEnt = gethostbyname(hostname); //get hostname
	if (ptrHostEnt == nullptr)
	{
		//epic fail #2
		errorcode = 2; //we failed to get the host entity information
		return nullptr;
	}

	for (; ptrHostEnt->h_addr_list[l] != nullptr; l++)
	{
		l++;
	}

	char** rv = new char* [l]; //Allocate the string list (I'm still used to C-style strings)

	for (unsigned i = 0; i < l; i++) //loop each adress in the list
	{
		in_addr addr; //IP adress structure
		memcpy(&addr, ptrHostEnt->h_addr_list[i], sizeof(in_addr)); //copy IP
		rv[i] = inet_ntoa(addr); //since inet_ntoa points to a static buffer, deleting each string won't be necessary
	}
	errorcode = 0; //yay we got 'em
	return rv;
}

#endif