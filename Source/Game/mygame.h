#include "GameSystem.h"
namespace game_framework {
	class levelrank {
	public:
		static int value;
	};

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		int level = -1;
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		GameSystem game_system;
		int phase_start = 1;
		int phase_rank = 1;
	};

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
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
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int phase_run = 1;
		int phase_rank = 1;
	};


	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
	};
}