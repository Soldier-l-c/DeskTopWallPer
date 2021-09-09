#include "stdafx.h"
#include "CurlHelper.h"
#include "PathUtils.h"
#include "Wallpaper.h"
#include "util.h"
#include "LogHelper.h"
#define LOG_FILE PathUtils::GetCurFullPath()+L"\\WallPaper.log"
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 
int main(int argc, char* argv[])
{
	auto spLogHelper = std::make_shared<CLogHelper>(LOG_FILE);

	auto imagePath = WallPaper::GetImagePath();
	if (imagePath.empty())return -1;

	auto imageUrl = UtilBase::UtilUrl::GetUrlFromCommond(argc, argv);
	int response{ 0 };
	auto downloadRes = CurlHelper::GetInstance().DownloadToFile(imageUrl.c_str(), imagePath.c_str(), &response);
	COUT_INFO << "DownloadToFile response code:[" << response << "]" << std::endl;

	if (downloadRes && response==200 && PathUtils::IsPathExist(imagePath.c_str()))
	{
		//COUT_INFO << std::endl;
		COUT_INFO << "Set wall paper res: ["<< WallPaper::SetDesktopWallpaper(const_cast<const PWSTR>(imagePath.c_str()), WallPaper::WallpaperStyle::Fill) <<"]"<< std::endl;
	}
	else
	{
		COUT_ERROR << "DownloadToFile failed, file: [" << CW2A(imagePath.c_str()) << "] url:[" << imageUrl.c_str()<<"]" << std::endl;
	}
	COUT_INFO << std::endl;
	//system("pause");
}