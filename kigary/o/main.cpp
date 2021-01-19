#include "DxLib.h"
#include "Keyboard.h"
#include "NotesData.h"

const char TITLE[] = "hungerhythm~飢餓リズム~ メインシステム開発ラボ";

const int WIN_WIDTH = 990; //ウィンドウ横幅
const int WIN_HEIGHT = 700;//ウィンドウ縦幅

struct LANE_DATA {
	int startX;//始点X座標
	int startY;//始点Y座標
	int judgeX;//判定点X座標
	int judgeY;//判定点座標
};
int notes2judgePointLength(const int& nowTime, const int& judgeTime, const int& oneSecond, const unsigned int& roadLength, const double& speed = 1 / 1.5);

int ads(int num);
long int ads(long int num);



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetMainWindowText(TITLE);					// タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0);				//画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(55, 55, 55);		// 画面の背景色を設定する

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//クラスや構造体
	Keyboard* key = new Keyboard;

	struct LANE_DATA lane[laneNum];
	lane[MOUTH] = { WIN_WIDTH, 205, WIN_WIDTH / 4, 205 };
	lane[STOMACH] = { lane[MOUTH].judgeX, lane[MOUTH].judgeY, lane[MOUTH].judgeX, WIN_HEIGHT - 200 };


	//画像などのリソースデータの変数宣言と読み込み

	const int bgmHandle = LoadSoundMem("data\\sound\\bgm_maoudamashii_cyber40 - (150-70bpm).ogg");
	ChangeVolumeSoundMem(128, bgmHandle);
	int bpm = 150;
	int oneCountTime = 60000 / (bpm * countBeat);
	double notesSpeed = 1 / 1.5;//開始点から判定点までの時間(1/xでx秒)
	int startBgmTime = 0;
	int nowBgmTime = 0;
	bool startBgmFlag = false;

	//ゲームループで使う変数の宣言
	int notesR = 8;
	int notesX[notesNum][laneNum] = { 0 }, notesY[notesNum][laneNum] = { 0 };
	for (int i = 0; i < notesNum; i++) {
		notesX[i][MOUTH] = 0;
		notesY[i][MOUTH] = lane[MOUTH].judgeY;
		notesFlag[i][MOUTH] = notesData[i][MOUTH];

		notesY[i][STOMACH] = 0;
		notesX[i][STOMACH] = lane[STOMACH].judgeX;
		notesFlag[i][STOMACH] = notesData[i][STOMACH];
	}
	const int judgeR = notesR;//判定範囲
	const int missR = judgeR + 0;//ミスの範囲（判定範囲込み）


	const unsigned int notesColor[laneNum] = {
		GetColor(200, 200, 55),
		GetColor(200, 55, 200),
	};
	const unsigned int green = GetColor(55, 200, 55);

	enum SCENE {
		TITLE,
		PLAY,
		WIN,
		LOSE
	};
	int nowScene = TITLE;

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);//フォントにアンチエイリアスを掛ける
	ChangeFont("Segoe UI");

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//最新キーボード情報を前フレームのキーボード情報にし、最新のキーボード情報を取得
		key->updateKey();

		//画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//
		switch (nowScene) {
		case TITLE:
			//spaceを押して本題に入る
			DrawString(16, 16, "Press SPACE to Start...", green);
			if (key->getKeys(KEY_INPUT_SPACE)) { nowScene = PLAY; }
			break;

		case PLAY:
			//-----更新処理
			//bgmを流す
			if (startBgmFlag == false) {
				startBgmFlag = true;
				PlaySoundMem(bgmHandle, DX_PLAYTYPE_BACK, TRUE);
				startBgmTime = GetNowCount();
			}
			nowBgmTime = GetNowCount() - startBgmTime;

			//nowBgmTime = 1000;//指定時間[ms]のノーツ状況確認用(普段はコメントアウトする)

			//ノーツ座標更新
			for (int i = 0; i < notesNum; i++) {
				notesX[i][MOUTH] = lane[MOUTH].judgeX +
					notes2judgePointLength(
						nowBgmTime,
						i * oneCountTime,
						1000,
						ads(lane[MOUTH].startX - lane[MOUTH].judgeX),
						notesSpeed
					);
				notesY[i][STOMACH] = lane[STOMACH].judgeY -
					notes2judgePointLength(
						nowBgmTime,
						i * oneCountTime,
						1000,
						ads(lane[STOMACH].startY - lane[STOMACH].judgeY),
						notesSpeed
					);
			}

			//-----描画処理
			DrawFormatString(0, 0, GetColor(200, 200, 200), "nowBgmTime : %d", nowBgmTime);

			//口判定点と開始点描画
			//始点
			DrawTriangle(
				lane[MOUTH].startX, lane[MOUTH].startY + 5,
				lane[MOUTH].startX, lane[MOUTH].startY - 5,
				lane[MOUTH].startX - 10, lane[MOUTH].startY,
				notesColor[MOUTH],
				TRUE
			);
			DrawCircle(lane[MOUTH].judgeX, lane[MOUTH].judgeY, judgeR, notesColor[MOUTH]);
			DrawLine(lane[MOUTH].judgeX, 0, lane[MOUTH].judgeX, WIN_HEIGHT, notesColor[MOUTH]);
			DrawString(lane[MOUTH].judgeX + 4, lane[MOUTH].judgeY + 4, "Judge", notesColor[MOUTH]);
			//胃判定点描画
			//始点
			DrawTriangle(
				lane[STOMACH].startX - 5, lane[STOMACH].startY - 5,
				lane[STOMACH].startX + 5, lane[STOMACH].startY - 5,
				lane[STOMACH].startX, lane[STOMACH].startY + 5,
				notesColor[STOMACH],
				TRUE
			);
			DrawCircle(lane[STOMACH].judgeX, lane[STOMACH].judgeY, judgeR, notesColor[STOMACH]);
			DrawLine(0, lane[STOMACH].judgeY, WIN_WIDTH, lane[STOMACH].judgeY, notesColor[STOMACH]);
			DrawString(lane[STOMACH].judgeX + 2, lane[STOMACH].judgeY + 2, "Judge", notesColor[STOMACH]);

			//ノーツ描画
			for (int i = 0; i < notesNum; i++) {
				for (int lane = 0; lane < laneNum; lane++) {
					if (notesFlag[i][lane] == true) {
						DrawCircle(notesX[i][lane], notesY[i][lane], notesR, notesColor[lane]);
					}
				}
			}

			break;//switch文のcaseの最後
		case WIN:
			DrawString(16, 16, "You WIN!", green);
			DrawString(16, 16 * 3, "Press SPACE to back Title...", green);
			if (key->getKeys(KEY_INPUT_SPACE) == TRUE) {
				nowScene = TITLE;
			}
			break;
		case LOSE:
			DrawString(16, 16, "You LOSE...", green);
			DrawString(16, 16 * 3, "Press SPACE to back Title...", green);
			if (key->getKeys(KEY_INPUT_SPACE) == TRUE) {
				nowScene = TITLE;
			}
			break;
		}
		//---------  ここまでにプログラムを記述  ---------//
		ScreenFlip();//（ダブルバッファ）裏面
		// 20ミリ秒待機（疑似60FPS）
		WaitTimer(20);
	}
	delete key;
	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}

/*
道の始点から判定点の距離を返す関数
nowTime : 曲開始から今までの時間
judgeTime : ノーツが判定点に来る時間
oneSecond : nowTime, judgeTimeで扱う時間の単位での1秒
roadLength : 道の始点から判定点までの距離
speed : x秒→1/x
*/
int notes2judgePointLength(const int& nowTime, const int& judgeTime, const int& oneSecond, const unsigned int& roadLength, const double& speed) {
	return (int)((judgeTime - nowTime) * (double)roadLength * speed) / oneSecond;
}

int ads(int num) {
	if (num >= 0) { return num; } else { return -num; }
}

long int ads(long int num) {
	if (num >= 0) { return num; } else { return -num; }
}