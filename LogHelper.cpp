#include "stdafx.h"
#include "LogHelper.h"

CLogHelper::CLogHelper(const std::wstring& logFile):m_wstrLogFile(logFile)
{
	__Init();
}

CLogHelper::~CLogHelper()
{
	__Uninit();
}

void CLogHelper::__Init()
{
	m_pstreambuffer = std::cout.rdbuf();
	m_spOfstream = std::make_shared<std::ofstream>(m_wstrLogFile, std::ios::app);

	auto fileBuf = m_spOfstream->rdbuf();
	// 设置cout流缓冲区指针为out.txt的流缓冲区指针
	std::cout.rdbuf(fileBuf);
}

void CLogHelper::__Uninit()
{
	if (m_spOfstream)
	{
		m_spOfstream->flush();
		m_spOfstream->close();
	}
	if (m_pstreambuffer)
	{
		// 恢复cout原来的流缓冲区指针
		std::cout.rdbuf(m_pstreambuffer);
	}
}

