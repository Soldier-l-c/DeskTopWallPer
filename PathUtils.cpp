#include "stdafx.h"
#include "PathUtils.h"
#define CHECK_NULL_PTR(ptr)\
	if(ptr == nullptr)\
	return false;

namespace PathUtils
{
	wstring  GetCurExeFullPath()
	{
		TCHAR szBuffer[1024] = { 0 };
		::GetModuleFileName(NULL, szBuffer, MAX_PATH);
		return szBuffer;
	}
	
	wstring  GetCurFullPath()
	{
		TCHAR szBuffer[1024] = { 0 };
		::GetModuleFileName(NULL, szBuffer, MAX_PATH);
		::PathRemoveFileSpec(szBuffer);

		return szBuffer;
	}

	wstring  GetCurExeCombinePath(const wchar_t* lpszCombinePath)
	{
		TCHAR szBuffer[1024] = { 0 };
		::GetModuleFileName(NULL, szBuffer, MAX_PATH);
		::PathRemoveFileSpec(szBuffer);

		TCHAR szDest[2048] = { 0 };
		::PathCombine(szDest, szBuffer, lpszCombinePath);
		return szDest;
	}

	void CreateDir(const wchar_t* lpszDir, bool bFileDir /*= true*/)
	{
		if (!(lpszDir && wcslen(lpszDir)))
			return;
		std::filesystem::path dir = lpszDir;
		std::error_code ec;
		if(bFileDir)
		{
			if (std::filesystem::exists(dir.parent_path()))
				return;
			std::filesystem::create_directories(dir.parent_path(), ec);
		}
		else
		{
			if (std::filesystem::exists(dir))
				return;
			std::filesystem::create_directories(dir, ec);
		}
	}

	bool IsPathExist(const wchar_t* lpszPath)
	{
		CHECK_NULL_PTR(lpszPath)
		std::filesystem::path dir = lpszPath;
		return std::filesystem::exists(dir);
	}

	std::wstring GetProgramDataPath()
	{
		wchar_t buffer[MAX_PATH+2] = { 0 };
		auto res = GetEnvironmentVariableW(L"ALLUSERSPROFILE", buffer, MAX_PATH);
		if (!res)
		{
			std::cout << "Get ProgramData path failed. GetLastError:" << GetLastError() << std::endl;
			return L"";
		}
			
		return buffer;
	}
	
};


