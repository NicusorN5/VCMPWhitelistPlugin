#include "Main.h"

const char* PluginName = "Whitelist plugin";

std::vector<std::string> IPs;

std::vector<std::string> Nicks;

#ifdef WIN32
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            WSADATA data;
            WSAStartup(MAKEWORD(1, 1), &data);
            break;
        }
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
        {
            WSACleanup();
            break;
        }
    }
    return TRUE;
}
#endif

extern "C" EXPORT
unsigned int VcmpPluginInit(PluginFuncs * pluginFuncs, PluginCallbacks * pluginCalls, PluginInfo * pluginInfo)
{

    //VCMP specific stuff
    pluginCalls->OnIncomingConnection = CheckPlayer;

    strcpy(pluginInfo->name, PluginName);
    pluginInfo->apiMajorVersion = PLUGIN_API_MAJOR;
    pluginInfo->apiMinorVersion = PLUGIN_API_MINOR;
    pluginInfo->pluginVersion = 0;

    //attempt to load the file
    std::ifstream allowed_ips("allowed_ips.txt");
    if (allowed_ips.fail()) //if file doesn't exist
    {
        std::ofstream create_allowed_file("allowed_ips.txt");
        create_allowed_file << "127.0.0.1\n";//write the loopback localhost IP adress into the list by default
        

        //we also write the local IPs into the file
        //we don't know what is the real IP address, therefore we write them all

        #ifdef WIN32
        int err;
        unsigned NumIPs;
        char** local_ips =  GetLocalIPs(err, NumIPs);

        if (err == 0) //if GetLocalIPs worked
        {
            for (size_t i = 0; i < NumIPs; i++)
            {
                IPs.push_back(local_ips[i]);
                create_allowed_file << local_ips[i] << "\n";
            }
            create_allowed_file << std::flush;
        }
        else
        {
            //Report error and pretend nothing ever happened 
            std::cout << "Failed to get the local IP. Please modify allowed_ips.txt yourself and restart the server. \r\n";
            std::cout << "Error code: (WSA)" << WSAGetLastError() << " Secondary : << "<< err << "\r\n";
        }
        std::cout << "Created default allowed IPs in allowed_ips.txt ... \r\n";
        //create_allowed_file.close() not needed since destructor is called at the end of the scope
#endif
    }
    else
    {
        //Load IPs
        std::string curr_ip;
        while (std::getline(allowed_ips, curr_ip))
        {
            IPs.push_back(curr_ip);
        }
    }

    std::ifstream load_nicks("allowed_nicks.txt");
    if (load_nicks.fail()) //if file doesn't exist, save two random names
    {
        std::ofstream save_nicks("allowed_nicks.txt");
        save_nicks << "Player1\nPlayer2\n";
        //Push the names into the vector
        Nicks.push_back("Player1");
        Nicks.push_back("Player2");
        std::cout << "Created allowed_nicks.txt . Please modify it and restart the server... \r\n";
    }
    else
    {
        //Load nicks
        std::string curr_nick;
        while(std::getline(load_nicks, curr_nick))
        {
            Nicks.push_back(curr_nick);
        }
        std::cout << "Loaded allowed IPs and nicknames! \r\n";
    }
    return 1;
}
