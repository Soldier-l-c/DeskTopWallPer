#pragma once
class CLogHelper
{
public:
	CLogHelper(const std::wstring& logFIle);
	~CLogHelper();

private:
	void __Init();
	void __Uinit();

private:
	std::streambuf* m_pstreambuffer{ nullptr };
	std::shared_ptr<std::ofstream> m_spOfstream{ nullptr };
	std::wstring m_wstrLogFile;
};