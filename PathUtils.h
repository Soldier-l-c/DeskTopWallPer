#pragma once
using std::wstring;
namespace PathUtils
{
	wstring GetCurExeFullPath();
	wstring GetCurFullPath();
	wstring GetCurExeCombinePath(const wchar_t* lpszCombinePath);
	void CreateDir(const wchar_t* lpszDir, bool bFileDir = true); //bFileDir表示参数lpszDir是文件路径还是一个目录
	bool IsPathExist(const wchar_t* lpszPath);
	std::wstring GetProgramDataPath();
}

