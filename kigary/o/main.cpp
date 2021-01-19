#include "DxLib.h"
#include "Keyboard.h"
#include "NotesData.h"

const char TITLE[] = "hungerhythm~�Q�샊�Y��~ ���C���V�X�e���J�����{";

const int WIN_WIDTH = 990; //�E�B���h�E����
const int WIN_HEIGHT = 700;//�E�B���h�E�c��

struct LANE_DATA {
	int startX;//�n�_X���W
	int startY;//�n�_Y���W
	int judgeX;//����_X���W
	int judgeY;//����_���W
};
int notes2judgePointLength(const int& nowTime, const int& judgeTime, const int& oneSecond, const unsigned int& roadLength, const double& speed = 1 / 1.5);

int ads(int num);
long int ads(long int num);



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetMainWindowText(TITLE);					// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(55, 55, 55);		// ��ʂ̔w�i�F��ݒ肷��

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//�N���X��\����
	Keyboard* key = new Keyboard;

	struct LANE_DATA lane[laneNum];
	lane[MOUTH] = { WIN_WIDTH, 205, WIN_WIDTH / 4, 205 };
	lane[STOMACH] = { lane[MOUTH].judgeX, lane[MOUTH].judgeY, lane[MOUTH].judgeX, WIN_HEIGHT - 200 };


	//�摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	const int bgmHandle = LoadSoundMem("data\\sound\\bgm_maoudamashii_cyber40 - (150-70bpm).ogg");
	ChangeVolumeSoundMem(128, bgmHandle);
	int bpm = 150;
	int oneCountTime = 60000 / (bpm * countBeat);
	double notesSpeed = 1 / 1.5;//�J�n�_���画��_�܂ł̎���(1/x��x�b)
	int startBgmTime = 0;
	int nowBgmTime = 0;
	bool startBgmFlag = false;

	//�Q�[�����[�v�Ŏg���ϐ��̐錾
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
	const int judgeR = notesR;//����͈�
	const int missR = judgeR + 0;//�~�X�͈̔́i����͈͍��݁j


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

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);//�t�H���g�ɃA���`�G�C���A�X���|����
	ChangeFont("Segoe UI");

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//�ŐV�L�[�{�[�h����O�t���[���̃L�[�{�[�h���ɂ��A�ŐV�̃L�[�{�[�h�����擾
		key->updateKey();

		//��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//
		switch (nowScene) {
		case TITLE:
			//space�������Ė{��ɓ���
			DrawString(16, 16, "Press SPACE to Start...", green);
			if (key->getKeys(KEY_INPUT_SPACE)) { nowScene = PLAY; }
			break;

		case PLAY:
			//-----�X�V����
			//bgm�𗬂�
			if (startBgmFlag == false) {
				startBgmFlag = true;
				PlaySoundMem(bgmHandle, DX_PLAYTYPE_BACK, TRUE);
				startBgmTime = GetNowCount();
			}
			nowBgmTime = GetNowCount() - startBgmTime;

			//nowBgmTime = 1000;//�w�莞��[ms]�̃m�[�c�󋵊m�F�p(���i�̓R�����g�A�E�g����)

			//�m�[�c���W�X�V
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

			//-----�`�揈��
			DrawFormatString(0, 0, GetColor(200, 200, 200), "nowBgmTime : %d", nowBgmTime);

			//������_�ƊJ�n�_�`��
			//�n�_
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
			//�ݔ���_�`��
			//�n�_
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

			//�m�[�c�`��
			for (int i = 0; i < notesNum; i++) {
				for (int lane = 0; lane < laneNum; lane++) {
					if (notesFlag[i][lane] == true) {
						DrawCircle(notesX[i][lane], notesY[i][lane], notesR, notesColor[lane]);
					}
				}
			}

			break;//switch����case�̍Ō�
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
		//---------  �����܂łɃv���O�������L�q  ---------//
		ScreenFlip();//�i�_�u���o�b�t�@�j����
		// 20�~���b�ҋ@�i�^��60FPS�j
		WaitTimer(20);
	}
	delete key;
	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}

/*
���̎n�_���画��_�̋�����Ԃ��֐�
nowTime : �ȊJ�n���獡�܂ł̎���
judgeTime : �m�[�c������_�ɗ��鎞��
oneSecond : nowTime, judgeTime�ň������Ԃ̒P�ʂł�1�b
roadLength : ���̎n�_���画��_�܂ł̋���
speed : x�b��1/x
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