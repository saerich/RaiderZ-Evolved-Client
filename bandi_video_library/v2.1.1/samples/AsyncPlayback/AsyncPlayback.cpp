////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// BandiVideoLibrary 2.1 Sample
/// 
/// Copyright(C) 2008-2010 BandiSoft.com All rights reserved.
///
/// Visit http://www.bandisoft.com for more information.
/// 
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>

#include "BandiVideoLibrary.h"
#include "BandiVideoTexture_DX9.h"

#pragma warning (disable:4996)

#define WINDOW_TEXT	"BandiVideo Async Playback"

#define MV_WIDTH	1024
#define MV_HEIGHT	768

LRESULT WINAPI WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_PAINT:
		{
			// ���������� ��� ĥ�ϱ�
			PAINTSTRUCT ps;
			HDC dc;
			dc = BeginPaint(hwnd, &ps);
			PatBlt(dc, 0, 0, 4096, 4096, BLACKNESS);
			EndPaint(hwnd, &ps);
		}
		return 0;

	case WM_ERASEBKGND:
		return 1;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



// ������ ����
static HWND CreatePlayerWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance)
{
	if(!hPrevInstance)
	{
		WNDCLASS wc;

		wc.style = 0;
		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(101));
		wc.hCursor = LoadCursor(0, IDC_ARROW);;
		wc.hbrBackground = 0;
		wc.lpszMenuName = 0;
		wc.lpszClassName = "AsyncPlayback";

		if(!RegisterClass(&wc))
		{
			return( 0 );
		}
	}

	return CreateWindow("AsyncPlayback", WINDOW_TEXT, 
						WS_CAPTION | WS_POPUP| WS_CLIPCHILDREN |
						WS_SYSMENU | WS_MINIMIZEBOX | WS_SIZEBOX,
						64, 64,
						64, 64,
						0, 0, hInstance,0);
}


// ������ ���� ũ�� ���
static void CalcWindowBorder(HWND hwnd, int &extra_width, int &extra_height)
{
	RECT r, c;

	GetWindowRect(hwnd, &r);
	GetClientRect(hwnd, &c);

	extra_width		= ( r.right - r.left ) - ( c.right - c.left );
	extra_height	= ( r.bottom - r.top ) - ( c.bottom - c.top );
}



int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	int extra_width, extra_height;

	// ���â �����ϱ�
	hwnd = CreatePlayerWindow(hInstance, hPrevInstance);
	if(!hwnd)
	{
		MessageBox(NULL, "Error creating window.", WINDOW_TEXT, MB_OK | MB_ICONSTOP);
		return 1;
	}

	CalcWindowBorder(hwnd, extra_width, extra_height);

	CBandiVideoLibrary		bvl;
	CBandiVideoDevice*		bvd = NULL;
	CBandiVideoTexture*		bvt = NULL;
	BVL_VIDEO_INFO			info;

	if(FAILED(bvl.Create(BANDIVIDEO_DLL_FILE_NAME, NULL, NULL)))
	{
		MessageBox(NULL, "Error creating BandiVideoLibrary.", WINDOW_TEXT, MB_OK | MB_ICONSTOP);
		DestroyWindow(hwnd);
		return 2;
	}

/*	// verify
	if(FAILED(bvl.Verify("BANDISOFT-TRIAL-200909", "ea92bc5b")))
	{
		// trial expired!!
		ASSERT(0);
	}*/

	if(FAILED(bvl.Open(lpCmdLine, TRUE)))
	{
		MessageBox(NULL, "Error opening file....", WINDOW_TEXT, MB_OK | MB_ICONSTOP);
		DestroyWindow(hwnd);
		return 3;
	}

	// ���� ũ�⿡ ���� âũ�� ����
	SetWindowPos(hwnd, 0, 0, 0, MV_WIDTH+extra_width, MV_HEIGHT+extra_height, SWP_NOMOVE);

	bvd = new CBandiVideoDevice_DX9();
	if(!bvd || FAILED(bvd->Open(hwnd)))
	{
		MessageBox(NULL, "Error opening device...", WINDOW_TEXT, MB_OK | MB_ICONSTOP);
		DestroyWindow(hwnd);
		if(bvd) delete bvd;
		return -1;
	}

	ShowWindow(hwnd, nCmdShow);

	do
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			BVL_STATUS		status;
			bvl.GetStatus(status);

			if(status == BVL_STATUS_READY)
			{
				// ����� �غ� �Ϸ�Ǿ��ٸ�, ��� ����
				bvl.GetVideoInfo(info);
				bvl.Play();

				if(bvt == NULL)
				{
					bvt = new CBandiVideoTexture_DX9((CBandiVideoDevice_DX9*)bvd);
					if(!bvt || FAILED(bvt->Open(info.width , info.height)))
					{
						if(bvt) delete bvt;
						bvt = NULL;
					}
				}
			}
			else if(status == BVL_STATUS_PLAYEND)
			{
				// ������ ����� �Ϸ�Ǿ�����, �ٽ� ����
				bvl.Close();
				bvl.Open(lpCmdLine, TRUE);
			}
			else if(status == BVL_STATUS_ERROR)
			{
				MessageBox(NULL, "Error playing file...", WINDOW_TEXT, MB_OK | MB_ICONSTOP);
				break;
			}

	
			// �� �������� ����� �ð��ΰ�?
			if(bvl.IsNextFrame())
			{
				INT		pitch;
				BYTE*	buf = bvt->Lock(pitch);
				if(buf)
				{
					// Get frame
					BVL_FRAME frame;
					frame.frame_buf = buf;
					frame.frame_buf_size = info.height*pitch;
					frame.pitch = pitch;
					frame.width = info.width;
					frame.height = info.height;
					frame.pixel_format = bvt->GetFormat();

					bvl.GetFrame(frame, TRUE);
					
					bvt->Unlock();

					// Show frame
					bvd->StartFrame();
					bvt->Draw(0, 0, MV_WIDTH, MV_HEIGHT);
					bvd->EndFrame();
				}
			}
			else
			{
				Sleep(1);
			}
		}
	}
	while(1);

	bvl.Destroy();

	if(bvd) 
	{
		bvd->Close();
		delete bvd;
	}

	if(bvt)
	{
		bvt->Close();
		delete bvt;
	}

	return 0;
}
