//=============================================================================
//
// fpsロックの機能 [fps.cpp]
// Author : 麦英泳
//
//=============================================================================
#include "fps.h"
#include "debugproc.h"
//*****************************************************************************
// グローバル変数:
//*****************************************************************************
#ifdef _DEBUG
//FPS表示関連
int		g_nFPS;			// 1秒のフレーム数（FPS）
int		g_nFrameCount;	// フレーム数カウンター
DWORD	dwFPSLastTime;	// 前回FPSを計算するときの時間
#endif

DWORD	dwExecLastTime;	// 前回処理を行うときの時間
DWORD	dwCurrentTime;	// 現在の時間


void InitFPS(void)
{
	timeBeginPeriod(1);				// タイマーの最小精度を1ミリ秒にする

#ifdef _DEBUG
	//FPS表示関連
	g_nFPS = 0;
	g_nFrameCount = 0;
	dwFPSLastTime = timeGetTime();
#endif

	dwExecLastTime = timeGetTime();
	

}

bool UpdateFPS(void)
{
	dwCurrentTime = timeGetTime();

#ifdef _DEBUG
	//FPS表示関連
	if ((dwCurrentTime - dwFPSLastTime) >= 500)								// 0.5秒ごとに、FPSを更新する
	{
		g_nFPS = g_nFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);	//1秒のフレーム数（FPS）に換算する
		g_nFrameCount = 0;
		dwFPSLastTime = dwCurrentTime;
		
	}
#endif

	//FPSロック機能
	if ((dwCurrentTime - dwExecLastTime) >= (1000 / FPS))					//1秒（1000ミリ秒）のいくつか分の間隔で処理を行う
	{
		dwExecLastTime = dwCurrentTime;
		
#ifdef _DEBUG
		//FPS表示関連
		g_nFrameCount++;	
#endif
		
		return true;
	}
	else
	{
		return false;
	}
}


void ShowFPS(void)
{
#ifdef _DEBUG
	//FPS表示関連
	PrintDebugProc("FPS:%d\n", g_nFPS);		//FPSを表示
#endif
}



void UnitFPS(void)
{
	timeEndPeriod(1);				// タイマーの最小精度を戻す
}


