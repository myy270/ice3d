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
int		g_nFPS;				// 1秒のフレーム数（FPS）
int		g_nFrameCount;		// フレーム数カウンター
DWORD	g_dwFPSLastTime;	// 前回FPSを計算するときの時間
#endif

DWORD	g_dwExecLastTime;	// 前回処理を行うときの時間
DWORD	g_dwCurrentTime;	// 現在の時間

//=============================================================================
// 初期化処理
//=============================================================================
void InitFPS(void)
{
	timeBeginPeriod(1);				// タイマーの最小精度を1ミリ秒にする

#ifdef _DEBUG
	//FPS表示関連
	g_nFPS = 0;
	g_nFrameCount = 0;
	g_dwFPSLastTime = timeGetTime();
#endif

	g_dwExecLastTime = timeGetTime();
	
}

//=============================================================================
// 終了処理
//=============================================================================
void UnitFPS(void)
{
	timeEndPeriod(1);				// タイマーの最小精度を戻す
}

//=============================================================================
// 更新処理
//=============================================================================
bool UpdateFPS(void)
{
	g_dwCurrentTime = timeGetTime();

#ifdef _DEBUG
	//FPS表示関連
	if ((g_dwCurrentTime - g_dwFPSLastTime) >= 500)								// 0.5秒ごとに、FPSを更新する
	{
		g_nFPS = g_nFrameCount * 1000 / (g_dwCurrentTime - g_dwFPSLastTime);	//1秒のフレーム数（FPS）に換算する
		g_nFrameCount = 0;
		g_dwFPSLastTime = g_dwCurrentTime;
		
	}
#endif

	//FPSロック機能
	if ((g_dwCurrentTime - g_dwExecLastTime) >= (1000 / FPS))					//1秒（1000ミリ秒）のいくつか分の間隔で処理を行う
	{
		g_dwExecLastTime = g_dwCurrentTime;
		
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

//=============================================================================
// FPSを表示
//=============================================================================
void ShowFPS(void)
{
#ifdef _DEBUG
	//FPS表示関連
	PrintDebugProc("FPS:%d\n", g_nFPS);		//FPSを表示
#endif
}



