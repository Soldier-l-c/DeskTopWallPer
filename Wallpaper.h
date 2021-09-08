#pragma once
namespace WallPaper
{
	enum class WallpaperStyle
	{
		Tile,//ƽ��
		Center,//����
		Stretch,//����
		Fit, //��Ӧ
		Fill//���
	};
	HRESULT SetDesktopWallpaper(const PWSTR pszFile, WallpaperStyle style);
	std::wstring GetImagePath();
}