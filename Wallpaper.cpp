#include "stdafx.h"
#include "Wallpaper.h"
#include "PathUtils.h"
#include "CurlHelper.h"
using std::wstring;

bool WallPaper::ChangeWallPaper(const std::string& imageUrl)
{
	auto res{ false };
	do
	{
		auto imagePath = WallPaper::GetImagePath();
		if (imagePath.empty())
			break;

		int response{ 0 };
		auto downloadRes = CurlHelper::GetInstance().DownloadToFile(imageUrl.c_str(), imagePath.c_str(), &response);
		COUT_INFO << "DownloadToFile response code:[" << response << "]" << std::endl;

		if (downloadRes && response == 200 && PathUtils::IsPathExist(imagePath.c_str()))
		{
			auto setRes = WallPaper::SetDesktopWallpaper(const_cast<const PWSTR>(imagePath.c_str()), WallPaper::WallpaperStyle::Fill);
			COUT_INFO << "Set wall paper res: [" << setRes << "]" << std::endl;
			if (setRes != ERROR_SUCCESS)break;
		}
		else
		{
			COUT_ERROR << "DownloadToFile failed," << "respone code:[" << response << "] file: [" << CW2A(imagePath.c_str()) << "] url:[" << imageUrl.c_str() << "]" << std::endl;
			break;
		}

		res = true;
	} while (false);

	COUT_INFO << "ChangeWallPaper res:[" << res << "]" << std::endl;
	COUT_EMPTY_LINE;

	return res;
}

HRESULT WallPaper::SetDesktopWallpaper(const PWSTR pszFile, WallpaperStyle style)
{
	HRESULT hr = S_OK;

	//设置壁纸风格和展开方式
	//在Control Panel\Desktop中的两个键值将被设置
	// TileWallpaper
	//  0: 图片不被平铺 
	//  1: 被平铺 
	// WallpaperStyle
	//  0:  0表示图片居中，1表示平铺
	//  2:  拉伸填充整个屏幕
	//  6:  拉伸适应屏幕并保持高度比
	//  10: 图片被调整大小裁剪适应屏幕保持纵横比

	//以可读可写的方式打开HKCU\Control Panel\Desktop注册表项
	HKEY hKey = NULL;
	hr = HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_CURRENT_USER,
		L"Control Panel\\Desktop", 0, KEY_READ | KEY_WRITE, &hKey));
	if (SUCCEEDED(hr))
	{
		wstring pszWallpaperStyle;
		wstring pszTileWallpaper;

		switch (style)
		{
		case WallpaperStyle::Tile:
			pszWallpaperStyle = L"0";
			pszTileWallpaper = L"1";
			break;

		case WallpaperStyle::Center:
			pszWallpaperStyle = L"0";
			pszTileWallpaper = L"0";
			break;

		case WallpaperStyle::Stretch:
			pszWallpaperStyle = L"2";
			pszTileWallpaper = L"0";
			break;

		case WallpaperStyle::Fit: // (Windows 7 and later)
			pszWallpaperStyle = L"6";
			pszTileWallpaper = L"0";
			break;

		case WallpaperStyle::Fill: // (Windows 7 and later)
			pszWallpaperStyle = L"10";
			pszTileWallpaper = L"0";
			break;
		}
		// 设置 WallpaperStyle 和 TileWallpaper 到注册表项.
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

	//通过调用Win32 API函数SystemParametersInfo 设置桌面壁纸
	/************************************************
	之前我们已经设置了壁纸的类型，但是壁纸图片的实际文件路径还没
	设置。SystemParametersInfo 这个函数位于user32.dll中，它支持
	我们从系统中获得硬件和配置信息。它有四个参数，第一个指明调用这
	个函数所要执行的操作，接下来的两个参数指明将要设置的数据，依据
	第一个参数的设定。最后一个允许指定改变是否被保存。这里第一个参数
	我们应指定SPI_SETDESKWALLPAPER，指明我们是要设置壁纸。接下来是
	文件路径。在Vista之前必须是一个.bmp的文件。Vista和更高级的系统
	支持.jpg格式
	*************************************************/
	//SPI_SETDESKWALLPAPER参数使得壁纸改变保存并持续可见。
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
			COUT_ERROR << "Path is not exist path: [" << buffer<<"]" <<std::endl;
			return L"";
		}
	}

	PathCombine(buffer, buffer, (std::to_wstring(time(nullptr)) + L"_image.jpg").c_str());

	return buffer;

}

