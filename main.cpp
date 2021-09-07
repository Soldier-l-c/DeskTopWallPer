#include "stdafx.h"
#include "CurlHelper.h"
#include "PathUtils.h"
#include "Wallpaper.h"

int main()
{
	auto imagePath = WallPaper::GetImagePath();
	if (imagePath.empty())return -1;

	int response{ 0 };
	auto downloadRes = CurlHelper::GetInstance().DownloadToFile("https://unsplash.it/1600/900?random", imagePath.c_str(), &response);
	if (downloadRes)
	{
		cout << endl;
		cout << WallPaper::SetDesktopWallpaper(const_cast<PWSTR>(imagePath.c_str()), WallPaper::WallpaperStyle::Fill) << endl;
	}

	system("pause");
}