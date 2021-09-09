#pragma once
#ifndef STDAFX_H
#define STDAFX_H
#pragma once
#include <iostream>
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <list>
#include <random>
#include <fstream>

#include <intshcut.h>
#include <shobjidl_core.h>
#include <ShlObj.h>
#include <atlstr.h>

#include <unordered_map>
#include <Ws2tcpip.h>
#include <iphlpapi.h>
#include <Tcpestats.h>
#include <Mstcpip.h>
#include <tlhelp32.h>
#include <io.h>
#include <atlstr.h>
#include <tchar.h>
#include <Psapi.h>
#include <psapi.h>   
#include <Pdh.h>
#include <time.h>
#include <stdio.h>
#include <Winternl.h>
#define INFO_ 20
#define ERROR_ 35
#define COUT_INFO std::cout<<time(nullptr)<<"  "<<std::to_string(INFO_)+"\t"
#define COUT_ERROR std::cout<<time(nullptr)<<"  "<<std::to_string(ERROR_)+"\t"
#endif // !STDAFX_H
