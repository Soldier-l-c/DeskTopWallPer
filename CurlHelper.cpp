#include "stdafx.h"
#include "CurlHelper.h"
using std::cout;
using std::endl;

int CurlHelper::Init()
{
	static bool bInit = false;
	if (!bInit)
	{
		CURLcode ret = curl_global_init(CURL_GLOBAL_ALL);
		if (ret == CURLE_OK)
			bInit = true;
	}
	return TRUE;
}

void CurlHelper::UnInit()
{
	curl_global_cleanup();
}

size_t CurlHelper::CurlWiteDataToFileCallback(void *ptr,size_t size, size_t nmemb, void *stream)
{
	_WriteDataToFileCbAtom* pParam = (_WriteDataToFileCbAtom*)stream;

	double val;
	curl_easy_getinfo(pParam->pUrl, CURLINFO_SIZE_DOWNLOAD, &val); 

	DWORD dwWrittenBytes = 0;
	WriteFile(pParam->hFile,ptr,size * nmemb,&dwWrittenBytes,NULL);

	return dwWrittenBytes;
}

BOOL CurlHelper::DownloadToFile(const char* lpszUrl, LPCWSTR lpszDestFile, int* pResponse)
{
	if (lpszUrl == nullptr || lpszDestFile == nullptr || !(strlen(lpszUrl) || !wcslen(lpszDestFile)))
	{
		COUT_ERROR << "DownloadToFile, url is empty or dest file is empty.return";
		return 0;
	}

	auto strUrl = RepalceSpaceWidth20(lpszUrl);
	lpszUrl = strUrl.c_str();
	COUT_INFO << "Download url:[" << lpszUrl<<"]" << endl;

	if (PathFileExists(lpszDestFile))
	{
		auto res = DeleteFile(lpszDestFile);
		if (!res)
		{
			COUT_ERROR << "DownloadToFile, delete file failed.file: [" << CW2A(lpszDestFile) << " ] getlasterror:[" << GetLastError() <<" ]"<< endl;
		}
	}
		
	int nResponse = 0;
	for (int i = 0; i < m_nDownloadTryTimes; ++i)
	{
		nResponse = 0;

		CURL* curl = curl_easy_init();
		if (!curl) { continue; }

		// 设置超时 HTTPGET
		curl_easy_setopt(curl, CURLOPT_URL, lpszUrl);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		_WriteDataToFileCbAtom atom;
		atom.pUrl = curl;
		atom.pThis = this;
		atom.hFile = CreateFile(lpszDestFile, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);
		if (atom.hFile == INVALID_HANDLE_VALUE)
		{
			COUT_ERROR << "DownloadToFile, create file failed. hfile is INVALID_HANDLE_VALUE, dest file: [" << CW2A(lpszDestFile)<<"]" << endl;
			break;
		}

		/* send all data to this function  */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWiteDataToFileCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &atom);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
		curl_easy_setopt(curl, CURLOPT_HEADER, 0L);  //若启用，会将头文件的信息作为数据流输出
		//curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT,m_nDownloadTimeout);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);//设置默认超时间隔为30s
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); //是否抓取跳转后的页面

		curl_slist* pList = NULL;
		pList = curl_slist_append(pList, "Content-Type=text/html ");

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, pList);
	
		CURLcode nRet = curl_easy_perform(curl);
		CloseHandle(atom.hFile);

		if (nRet == CURLE_OK)
		{
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &nResponse);
			break;
		}
		else
		{
			long dResponseCode = 0;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &dResponseCode);
			nResponse = nRet;
			DeleteFile(lpszDestFile);
		}

		curl_easy_cleanup(curl);
	}

	if (pResponse)
		*pResponse = nResponse;

	return nResponse == 200;
}