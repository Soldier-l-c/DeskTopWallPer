#pragma once
#define DEFAULT_PERIOD_TIME 1000*60*10
#define DEFAULT_IMAGE_URL "https://unsplash.it/1600/900?random"
class CommandlineParser
{
public:
	CommandlineParser(int32_t argc, char* argv[]);

	bool IsCallOnce() { return m_bIsCallOnce; };
	std::string GetImageUrl() { return m_strImageUrl; };
	int32_t GetPeriodTime() { return m_nPeriodTime; };
	int32_t GetPeriodNum() { return m_nPeriodNum; };

	void SetPeriodTime(int32_t time) { m_nPeriodTime = time; };

private:
	CommandlineParser() = delete;
	void __OutPutParser();

private:
	bool m_bIsCallOnce{ false };
	std::string m_strImageUrl{ DEFAULT_IMAGE_URL };
	int32_t m_nPeriodTime{ DEFAULT_PERIOD_TIME };
	int32_t m_nPeriodNum{ INT_MAX };
};