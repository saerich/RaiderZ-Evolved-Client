////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Youtube uploader
/// 
/// Copyright(C) 2008 BandiSoft.com All rights reserved.
///
/// Visit http://www.bandisoft.com for more information.
///
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#define UP_MAX_ID		128
#define UP_MAX_PWD		128
#define UP_MAX_TITLE	256
#define UP_MAX_DESC		512
#define UP_MAX_KEYWORD	128

// ���ε� ���� ����ü
struct SUploadInfo
{
	CHAR szID[UP_MAX_ID];				// Youtube Username
	CHAR szPWD[UP_MAX_PWD];				// Youtube Password

	WCHAR szFilePath[MAX_PATH];			// ���ε� ���� ���
	WCHAR szTitle[UP_MAX_TITLE];		// ����
	WCHAR szDesc[UP_MAX_DESC];			// ����
	WCHAR szKeyword[UP_MAX_KEYWORD];	// Ű����
};

#define STATUS_BUFFER_COUNT 2048

class CYoutubeUploader
{
public:
	CYoutubeUploader();
	~CYoutubeUploader();

	BOOL Upload(SUploadInfo *pInfo);						// ���ε�
	void Cancel();											// ���ε� ���

	BOOL IsUploading();										// ���ε����ΰ�?
	BOOL GetStatusString(LPTSTR lpStatus, int nBufferCnt);	// ���ε� ���� ���ڿ� ���ϱ�

protected:
	void UploadProc();
	static void _ThreadProc(void *param)
	{
		((CYoutubeUploader*)param)->UploadProc();
	};

	HANDLE m_hThread;

	SUploadInfo			m_info;		// ���ε� ����
	PROCESS_INFORMATION m_pi;		// ���ε� ���μ��� ����

	CHAR				m_sStatus[STATUS_BUFFER_COUNT+1];	// ���ε� ���� ���� ���ڿ�
	CRITICAL_SECTION	m_CritSec;
};
