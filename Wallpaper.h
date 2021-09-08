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
	HRESULT SetDesktopWallpaper(const PWSTR pszFile, WallpaperStyle style);
	std::wstring GetImagePath();
}