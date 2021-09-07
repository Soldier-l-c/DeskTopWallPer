#include "stdafx.h"
#include "CurlHelper.h"
#include "PathUtils.h"
#include "Wallpaper.h"
#include "util.h"
int main(int argc, char* argv[])
{
	auto imagePath = WallPaper::GetImagePath();
	if (imagePath.empty())return -1;

	auto imageUrl = UtilBase::UtilUrl::GetUrlFromCommond(argc, argv);
	int response{ 0 };
	auto downloadRes = CurlHelper::GetInstance().DownloadToFile(imageUrl.c_str(), imagePath.c_str(), &response);
	cout << "DownloadToFile response code:[" << response << "]" << endl;

	if (downloadRes && response==200)
	{
		cout << endl;
		cout << WallPaper::SetDesktopWallpaper(const_cast<PWSTR>(imagePath.c_str()), WallPaper::WallpaperStyle::Fill) << endl;
	}
	else
	{
		cout << "DownloadToFile failed, file: [" << CW2A(imagePath.c_str()) << "] url:[" << imageUrl.c_str()<<"]" << endl;
	}

	system("pause");
}