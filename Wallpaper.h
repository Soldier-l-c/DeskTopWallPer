#pragma once
namespace WallPaper
{
	enum class WallpaperStyle
	{
		Tile,//平铺
		Center,//居中
		Stretch,//拉伸
		Fit, //适应
		Fill//填充
	};

	bool ChangeWallPaper(const std::string& imageUrl);
	HRESULT SetDesktopWallpaper(const PWSTR pszFile, WallpaperStyle style);
	std::wstring GetImagePath();

}