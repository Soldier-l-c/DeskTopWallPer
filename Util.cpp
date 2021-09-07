#include "stdafx.h"
#include "util.h"
#define DEFAULT_IMAGE_URL "https://unsplash.it/1600/900?random"
std::string UtilBase::UtilUrl::GetUrlFromCommond(int argc, char* argv[])
{
	std::string url;
	if (argc < 2)url =  DEFAULT_IMAGE_URL;

	url = argv[1];
	std::cout << "Get Download url: [" << url << "]" << std::endl;
}
