#include "stdafx.h"
#include "CommandlineParser.h"
#define C_IMAGE_URL		"image_url="
#define C_OERIOD_TIME	"period_time="
#define C_IS_CALL_ONCE	"call_once="
#define C_NUM_OF_PERIOD	"period_num="
CommandlineParser::CommandlineParser(int argc, char* argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		std::string strArg = argv[i];
		if (strArg.find(C_IMAGE_URL) == 0)
		{
			m_strImageUrl = strArg.substr(strlen(C_IMAGE_URL));
		}
		else if (strArg.find(C_OERIOD_TIME) == 0)
		{
			m_nPeriodTime = atoi(strArg.substr(strlen(C_OERIOD_TIME)).c_str());
		}
		else if (strArg.find(C_IS_CALL_ONCE) == 0)
		{
			m_bIsCallOnce = atoi(strArg.substr(strlen(C_IS_CALL_ONCE)).c_str()) > 0;
		}
		else if (strArg.find(C_NUM_OF_PERIOD) == 0)
		{
			m_nPeriodNum = atoi(strArg.substr(strlen(C_NUM_OF_PERIOD)).c_str());
		}
	}

	__OutPutParser();
}

void CommandlineParser::__OutPutParser()
{
	COUT_INFO << "OutPutParser Image Url:[" << m_strImageUrl << "]" << std::endl;
	COUT_INFO << "OutPutParser Period Time:[" << m_nPeriodTime << "]" << std::endl;
	COUT_INFO << "OutPutParser Period Num:[" << m_nPeriodNum<< "]" << std::endl;
	COUT_INFO << "OutPutParser Call Once:[" << m_bIsCallOnce << "]" << std::endl;
}
