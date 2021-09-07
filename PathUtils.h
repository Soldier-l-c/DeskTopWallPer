#pragma once
using std::wstring;
namespace PathUtils
{
	wstring GetCurExeFullPath();
	wstring GetCurFullPath();
	wstring GetCurExeCombinePath(const wchar_t* lpszCombinePath);
	void CreateDir(const wchar_t* lpszDir, bool bFileDir = true); //bFileDir��ʾ����lpszDir���ļ�·������һ��Ŀ¼
	bool IsPathExist(const wchar_t* lpszPath);
	std::wstring GetProgramDataPath();
}

