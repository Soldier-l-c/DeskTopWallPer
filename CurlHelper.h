#pragma once

#include "./curl/curl.h"

class CurlHelper;
using namespace std;

typedef struct _WriteDataToFileCbAtom
{
	_WriteDataToFileCbAtom() : pUrl(0),pThis(0),hFile(0) {}
	
	CURL* pUrl;
	CurlHelper* pThis;
	HANDLE hFile;
}_WriteDataToFileCbAtom;

typedef struct _WriteDataToBufferCbAtom
{
	_WriteDataToBufferCbAtom() : pUrl(0),pThis(0),pBuffer(0),nTotalSize(0),nCurPos(0) {}

	CURL* pUrl;
	CurlHelper* pThis;
	BYTE* pBuffer;
	int nTotalSize;
	int nCurPos;
}_WriteDataToBufferCbAtom;

class CurlHelper
{
public:

	int Init();
	
	void UnInit();

	BOOL DownloadToFile(const char* lpszUrl, LPCWSTR lpszDestFile, int* pResponse);
public:

	static CurlHelper& GetInstance()
	{
		static CurlHelper curl_helper;
		curl_helper.Init();
		return curl_helper;
	}

protected:

	CurlHelper() : m_nDownloadTryTimes(3),m_nDownloadTimeout(30) { }

	static size_t CurlWiteDataToFileCallback(void *ptr,size_t size, size_t nmemb, void *stream);
	
	std::string RepalceSpaceWidth20(const std::string& url)
	{
		std::string res;
		for (auto iter : url)
		{
			if (iter == ' ')
			{
				res = res + "%20";
			}
			else res = res + iter;
		}
		return res;
	}

private:

	int m_nDownloadTryTimes;

	int m_nDownloadTimeout;
};

#define CURLHELPER_PTR	(CurlHelper::GetInstance())
