#include "stdafx.h"
#include "CurlHelper.h"
#include "PathUtils.h"
#include "Wallpaper.h"
#include "util.h"
#include "LogHelper.h"
#include "CommandlineParser.h"
#define LOG_FILE PathUtils::GetCurFullPath()+L"\\WallPaper.log"
#define PERIOD_TIME 1000*60*10
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

int main(int argc, char* argv[])
{
	auto spLogHelper = std::make_shared<CLogHelper>(LOG_FILE);
	if (UtilBase::Single::IsRunning())
	{
		COUT_ERROR << "Other process is running. return!!!" << std::endl;
		return -1;
	}

	CommandlineParser parser(argc, argv);

	auto periodNum = parser.IsCallOnce() ? 1 : parser.GetPeriodNum();
	parser.SetPeriodTime(parser.IsCallOnce() ? 0 : parser.GetPeriodTime());
	bool res{ true };

	while (periodNum-- && res)
	{
		res = WallPaper::ChangeWallPaper(parser.GetImageUrl());
		Sleep(res ? parser.GetPeriodTime() : 0);
	}

	COUT_INFO << "Exit!!!" << std::endl;
}