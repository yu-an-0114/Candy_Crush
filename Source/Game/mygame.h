#include "GameSystem.h"
namespace game_framework {
	class levelrank {
	public:
		static int value;
	};

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		int level = -1;
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		GameSystem game_system;
		int phase_start = 1;
		int phase_rank = 1;
	};

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		template <typename T>
		void object_move_with_mouse(T& click_object,CPoint point) {
			click_object[game_system.clickX][game_system.clickY].SetTopLeft(point.x - click_object[game_system.clickX][game_system.clickY].GetWidth() / 2, point.y - click_object[game_system.clickX][game_system.clickY].GetHeight() / 2);
		}
		template <typename T>
		bool oblect_click_mouse(T& click_object) {
			return click_object[game_system.clickX][game_system.clickY].isClick_CMovingBitmap(click_object[game_system.clickX][game_system.clickY], game_system.candy_start);
		}
		bool showEffect = false;
		int level = -1;
		GameSystem game_system;
		int scoreStar_place[2] = { 20, 60 };
		int phase = -1;
		int starNum = 0;
		bool pass = false;
		CSpecialEffect time;

	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int phase_run = 1;
		int phase_rank = 1;
	};


	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};
}