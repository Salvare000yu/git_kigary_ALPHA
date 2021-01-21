#include "DxLib.h"
#include "Keyboard.h"
#include "NotesData.h"
#include "Bgm.h"
#include "Notes.h"

#define mouthBotton KEY_INPUT_RETURN
#define stomachBotton KEY_INPUT_SPACE

const char TITLE[] = "K020G1187 竹内佑汰：タイトル";

const int WIN_WIDTH = 800; //ウィンドウ横幅
const int WIN_HEIGHT = 600;//ウィンドウ縦幅

int ads(const int& num);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);//ウィンドウサイズの手動では変更不可、かつウィンドウサイズに合わせた拡大不可にする
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

	Bgm* bgm = new Bgm(
		LoadSoundMem("data\\sound\\bgm_maoudamashii_cyber40 - (150-70bpm).ogg"),
		150.0,
		128
	);

	const int startX[laneNum] = { WIN_WIDTH, WIN_WIDTH / 4 };
	const int startY[laneNum] = { WIN_HEIGHT / 4, WIN_HEIGHT / 4 };

	const int judgeX[laneNum] = { startX[STOMACH], startX[STOMACH] };
	const int judgeY[laneNum] = { startY[STOMACH], WIN_HEIGHT / 4 * 3 };
	const int judgeR = 8;

	Notes* notes[notesNum][laneNum];
	for (int i = 0; i < notesNum; i++) {
		/*for (int j = 0; j < laneNum; j++) {
			notes[i][j] = new Notes(startX[j], startY[j], notesData[i][j]);
		}*/
		notes[i][MOUTH] = new Notes(startX[MOUTH], startY[MOUTH], notesData[i][MOUTH], 8 * 2, false, LoadGraph("data\\graphic\\notesMouth.png"));
		notes[i][STOMACH] = new Notes(startX[STOMACH], startY[STOMACH], notesData[i][STOMACH], 8 * 2, false, LoadGraph("data\\graphic\\notesStomach.png"));
	}
	const unsigned int notesColor[laneNum] = {
		GetColor(200,200,55),
		GetColor(200,55,200)
	};

	//画像などのリソースデータの変数宣言と読み込み

	//画像
	const int titleBack = LoadGraph("data\\graphic\\titleBack.png");
	const int playBack = LoadGraph("data\\graphic\\playBack.png");
	const int finishBack = LoadGraph("data\\graphic\\finishBack.png");

	//音
	const int sceneChangeSeHandle = LoadSoundMem("data\\sound\\Shortbridge29-1 - (silentCuts).ogg");
	ChangeVolumeSoundMem(128, sceneChangeSeHandle);

	//ゲームループで使う変数の宣言
	const unsigned int white = GetColor(200, 200, 200);
	const unsigned int green = GetColor(55, 200, 55);
	const unsigned int red = GetColor(200, 55, 55);
	const unsigned int blue = GetColor(55, 55, 200);

	int bright = 255;//フェードアウト用

	enum SCENE_NUM {
		TITLE,
		PLAY,
		FINISH
	};
	int nowScene = TITLE;
	bool fadeOutFlag = false;

	bool pushFlag[laneNum] = { false,false };
	int pushTime[laneNum] = { 0,0 };//キーを押した時間取得

	const int hitTime = 128;
	const int missTime = hitTime * 1.5;

	bool hitFlag[laneNum] = { false,false };
	bool missFlag[laneNum] = { false,false };


	// ゲームループ
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ProcessMessage() == 0) {
		//キーボード情報を更新
		key->updateKey();

		//画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		switch (nowScene) {
		case TITLE:
			DrawExtendGraph(0, 0, WIN_WIDTH - 1, WIN_HEIGHT - 1, titleBack, FALSE);

			DrawString(16, 16, "Press SPACE to Start...", green);
			if (fadeOutFlag == false && key->getKeys(KEY_INPUT_SPACE) == TRUE && key->getOldkeys(KEY_INPUT_SPACE) == FALSE) {
				PlaySoundMem(sceneChangeSeHandle, DX_PLAYTYPE_BACK);
				fadeOutFlag = true;
			}
			if (fadeOutFlag == true) {
				bright -= 2;
				if (bright <= 100) {
					bright = 255;
					fadeOutFlag = false;
					nowScene = PLAY;
				}
				SetDrawBright(bright, bright, bright);
			}
			break;//case TITLE:

		case PLAY:



			//-----更新処理
			bgm->playBgm();

			//---入力
			if (key->getKeys(mouthBotton) == TRUE && key->getOldkeys(mouthBotton) == FALSE) {
				pushFlag[MOUTH] = true;
				pushTime[MOUTH] = bgm->getNowTime();
			} else if (key->getKeys(mouthBotton) == FALSE) {
				pushFlag[MOUTH] = false;
			}


			if (key->getKeys(stomachBotton) == TRUE && key->getOldkeys(stomachBotton) == FALSE) {
				pushFlag[STOMACH] = true;
				pushTime[STOMACH] = bgm->getNowTime();
			} else if (key->getKeys(stomachBotton) == FALSE) {
				pushFlag[STOMACH] = false;
			}
			//---入力ここまで

			//移動
			for (int i = 0; i < notesNum; i++) {//ノーツの数だけ
				if (notes[i][MOUTH]->getAlive() == true) {
					notes[i][MOUTH]->
						updateNotesPositionX(
							1,
							judgeX[MOUTH],
							bgm->getNowTime(),
							i * bgm->oneCountTime(countBeat),
							1000,
							ads(
								judgeX[MOUTH] - startX[MOUTH]
							),
							1 / 1.5
						);
				}

				if (notes[i][STOMACH]->getAlive() == true) {
					notes[i][STOMACH]->
						updateNotesPositionY(
							-1,
							judgeY[STOMACH],
							bgm->getNowTime(),
							i * bgm->oneCountTime(countBeat),
							1000,
							ads(
								judgeY[STOMACH] - startY[STOMACH]
							),
							1 / 1.5
						);
				}
			}

			//判定
			for (int i = 0; i < notesNum; i++) {
				for (int j = 0; j < laneNum; j++) {
					if (pushFlag[j] == true) {
						if (
							pushTime[j] >= i * bgm->oneCountTime(countBeat) - hitTime
							&&
							pushTime[j] <= i * bgm->oneCountTime(countBeat) + hitTime) {
							//判定処理
							hitFlag[j] = true;
						} else if (
							pushTime[j] >= i * bgm->oneCountTime(countBeat) - missTime
							&&
							pushTime[j] <= i * bgm->oneCountTime(countBeat) + missTime) {
							//miss処理
							missFlag[j] = true;
						}
					}
				}
			}

			//-----描画処理
			DrawExtendGraph(0, 0, WIN_WIDTH - 1, WIN_HEIGHT - 1, playBack, FALSE);//背景画像

			DrawFormatString(16, 16, white, "nowTime : %d", bgm->getNowTime());

			//判定点描画
			DrawCircle(judgeX[MOUTH], judgeY[MOUTH], judgeR, notesColor[MOUTH]);
			DrawCircle(judgeX[STOMACH], judgeY[STOMACH], judgeR, notesColor[STOMACH]);

			//始点描画
			DrawCircle(startX[MOUTH], startY[MOUTH], 4, notesColor[MOUTH]);
			DrawCircle(startX[STOMACH], startY[STOMACH], 4, notesColor[STOMACH]);

			for (int i = 0; i < notesNum; i++) {

				notes[i][MOUTH]->draw(true, startX[MOUTH], judgeX[MOUTH]);
				notes[i][STOMACH]->draw(false, startY[STOMACH], judgeY[STOMACH]);

			}


			DrawFormatString(200, 0, red, "drawHitFlag[MOUTH] : %d, [STOMACH] : %d", hitFlag[MOUTH], hitFlag[STOMACH]);
			DrawFormatString(200, 20, red, "pushFlag[MOUTH] : %d, [STOMACH] : %d", pushFlag[MOUTH], pushFlag[STOMACH]);

			for (int i = 0; i < laneNum; i++) {
				if (hitFlag[i] == true) {
					DrawCircle(judgeX[i] + 20, judgeY[i] + 20, 8, red);
					hitFlag[i] = false;
				} else if (missFlag[i] == true) {
					DrawCircle(judgeX[i] + 20, judgeY[i] + 20, 8, blue);
					missFlag[i] = false;
				} else if (pushFlag[i] == true) {
					DrawCircle(judgeX[i] + 20, judgeY[i] + 20, 8, white);
					pushFlag[i] = false;
				}
			}

			break;//case PLAY:

		case FINISH:
			DrawExtendGraph(0, 0, WIN_WIDTH - 1, WIN_HEIGHT - 1, finishBack, FALSE);

			DrawString(16, 16, "FINISH!", green);
			DrawString(16, 16 + 20, "Press SPACE to Back Title...", green);
			if (fadeOutFlag == false && key->getKeys(KEY_INPUT_SPACE) == TRUE && key->getOldkeys(KEY_INPUT_SPACE) == FALSE) {
				PlaySoundMem(sceneChangeSeHandle, DX_PLAYTYPE_BACK);
				fadeOutFlag = true;
			}
			if (fadeOutFlag == true) {
				bright -= 2;
				if (bright <= 100) {
					bright = 255;
					fadeOutFlag = false;
					nowScene = TITLE;
				}
				SetDrawBright(bright, bright, bright);
			}
			break;//case FINISH:
		}
		//---------  ここまでにプログラムを記述  ---------//
		ScreenFlip();//（ダブルバッファ）裏面
		// 20ミリ秒待機（疑似60FPS）
		WaitTimer(20);
	}
	//keyboardクラスオブジェクト削除
	delete key;

	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}

int ads(const int& num) {
	if (num >= 0) {
		return num;
	} else {
		return -num;
	}
}