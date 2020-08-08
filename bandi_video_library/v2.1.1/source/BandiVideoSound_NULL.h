	////////////////////////////////////////////////////////////////////////////////////////////////////
///		
/// BandiVideoLibrary 2.0
/// 
/// Copyright(C) 2008-2009 BandiSoft.com All rights reserved.
///
/// Visit http://www.bandisoft.com for more information.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "bandivid.h"

class CBandiVideoSound_NULL : public IBandiVideoSound
{
public:
	CBandiVideoSound_NULL();
	virtual ~CBandiVideoSound_NULL();

	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void **ppv) { return E_NOTIMPL; };
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	// IBandiVideoSound
	HRESULT		Open(INT channels, INT samplerate, IBandiVideoSoundCB *callback);
	void		Close();
	HRESULT		Start();
	HRESULT		Stop();
	HRESULT		Pause(BOOL pause);
	HRESULT		GetTime(INT64 &time);
	HRESULT		SetVolume(INT volume);

protected:
	static unsigned WINAPI InitialThreadProc(LPVOID param)
	{
		CBandiVideoSound_NULL *p = (CBandiVideoSound_NULL*)param;
		return p->ThreadProc();		
	};
	UINT		ThreadProc();

	HRESULT		PlayNULL();
	LONGLONG	CalcTime();

	LONG		m_ref_count;

	LONGLONG	m_freq_units;		// �ʴ� ī���� ����(1000 �̸� ms���� ī������)
	LONGLONG	m_init_count;		// �ʱ� ī����

	LONGLONG	m_start_time;		// ���� �ð�
	BOOL		m_playing;

	CRITICAL_SECTION	m_crit_sec;
	BOOL				m_crit_sec_inited;

	HANDLE				m_hevent;
	HANDLE				m_hthread;
	UINT				m_thread_id;

	IBandiVideoSoundCB*	m_callback;
};
