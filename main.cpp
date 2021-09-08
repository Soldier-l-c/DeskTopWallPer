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
	std::cout << "DownloadToFile response code:[" << response << "]" << std::endl;

	if (downloadRes && response==200 && PathUtils::IsPathExist(imagePath.c_str()))
	{
		std::cout << std::endl;
		std::cout << "Set wall paper res: ["<< WallPaper::SetDesktopWallpaper(const_cast<PWSTR>(imagePath.c_str()), WallPaper::WallpaperStyle::Fill) <<"]"<< std::endl;
	}
	else
	{
		std::cout << "DownloadToFile failed, file: [" << CW2A(imagePath.c_str()) << "] url:[" << imageUrl.c_str()<<"]" << std::endl;
	}

	system("pause");
}