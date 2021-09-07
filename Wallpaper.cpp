#include "stdafx.h"
#include "Wallpaper.h"
#include "PathUtils.h"
using std::wstring;
HRESULT WallPaper::SetDesktopWallpaper(const PWSTR pszFile, WallpaperStyle style)
{
	HRESULT hr = S_OK;

	//���ñ�ֽ����չ����ʽ
	//��Control Panel\Desktop�е�������ֵ��������
	// TileWallpaper
	//  0: ͼƬ����ƽ�� 
	//  1: ��ƽ�� 
	// WallpaperStyle
	//  0:  0��ʾͼƬ���У�1��ʾƽ��
	//  2:  �������������Ļ
	//  6:  ������Ӧ��Ļ�����ָ߶ȱ�
	//  10: ͼƬ��������С�ü���Ӧ��Ļ�����ݺ��

	//�Կɶ���д�ķ�ʽ��HKCU\Control Panel\Desktopע�����
	HKEY hKey = NULL;
	hr = HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_CURRENT_USER,
		L"Control Panel\\Desktop", 0, KEY_READ | KEY_WRITE, &hKey));
	if (SUCCEEDED(hr))
	{
		wstring pszWallpaperStyle;
		wstring pszTileWallpaper;

		switch (style)
		{
		case Tile:
			pszWallpaperStyle = L"0";
			pszTileWallpaper = L"1";
			break;

		case Center:
			pszWallpaperStyle = L"0";
			pszTileWallpaper = L"0";
			break;

		case Stretch:
			pszWallpaperStyle = L"2";
			pszTileWallpaper = L"0";
			break;

		case Fit: // (Windows 7 and later)
			pszWallpaperStyle = L"6";
			pszTileWallpaper = L"0";
			break;

		case Fill: // (Windows 7 and later)
			pszWallpaperStyle = L"10";
			pszTileWallpaper = L"0";
			break;
		}
		// ���� WallpaperStyle �� TileWallpaper ��ע�����.
		DWORD cbData = lstrlen(pszWallpaperStyle.c_str()) * sizeof(TCHAR);
		hr = HRESULT_FROM_WIN32(RegSetValueEx(hKey, L"WallpaperStyle", 0, REG_SZ,
			reinterpret_cast<const BYTE*>(pszWallpaperStyle.c_str()), cbData));
		if (SUCCEEDED(hr))
		{
			cbData = lstrlen(pszTileWallpaper.c_str()) * sizeof(TCHAR);
			hr = HRESULT_FROM_WIN32(RegSetValueEx(hKey, L"TileWallpaper", 0, REG_SZ,
				reinterpret_cast<const BYTE*>(pszTileWallpaper.c_str()), cbData));
		}

		RegCloseKey(hKey);
	}

	//ͨ������Win32 API����SystemParametersInfo ���������ֽ
	/************************************************
	֮ǰ�����Ѿ������˱�ֽ�����ͣ����Ǳ�ֽͼƬ��ʵ���ļ�·����û
	���á�SystemParametersInfo �������λ��user32.dll�У���֧��
	���Ǵ�ϵͳ�л��Ӳ����������Ϣ�������ĸ���������һ��ָ��������
	��������Ҫִ�еĲ���������������������ָ����Ҫ���õ����ݣ�����
	��һ���������趨�����һ������ָ���ı��Ƿ񱻱��档�����һ������
	����Ӧָ��SPI_SETDESKWALLPAPER��ָ��������Ҫ���ñ�ֽ����������
	�ļ�·������Vista֮ǰ������һ��.bmp���ļ���Vista�͸��߼���ϵͳ
	֧��.jpg��ʽ
	*************************************************/
	//SPI_SETDESKWALLPAPER����ʹ�ñ�ֽ�ı䱣�沢�����ɼ���
	if (SUCCEEDED(hr))
	{
		if (!SystemParametersInfo(SPI_SETDESKWALLPAPER, 0,
			static_cast<PVOID>(pszFile),
			SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE))
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}
	}

	return hr;
}

std::wstring WallPaper::GetImagePath()
{
	auto programPath = PathUtils::GetProgramDataPath();
	if (programPath.empty())return L"";

	wchar_t buffer[MAX_PATH + 10]{ 0 };
	wstring imageName = L"DesktopWallper";
	PathCombine(buffer, programPath.c_str(), imageName.c_str());

	if (!PathUtils::IsPathExist(buffer))
	{
		PathUtils::CreateDir(buffer, false);
		if (!PathUtils::IsPathExist(buffer))
		{
			std::cout << "Path is not exist path:" << buffer <<std::endl;
			return L"";
		}
	}

	PathCombine(buffer, programPath.c_str(), (std::to_wstring(time(nullptr)) + L"_image.jpg").c_str());
	return buffer;

}
