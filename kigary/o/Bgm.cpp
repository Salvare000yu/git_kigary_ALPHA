#include "Bgm.h"
#include "DxLib.h"

Bgm::Bgm(const int& bgmHandle, const int& bpm, const int& startDelaySample, const int& startTime, const int& nowTime, const bool playFlag) {
	this->bgmHandle = bgmHandle;
	this->bpm = bpm;
	this->startDelaySample = startDelaySample;
	this->startTime = startTime;
	this->nowTime = nowTime;
	this->playFlag = playFlag;
}
Bgm::~Bgm() {

}

int Bgm::getBgmHandle() { return bgmHandle; }
int Bgm::getBpm() { return bpm; }
int Bgm::getStartDelaySample() { return startDelaySample; }
int Bgm::getStartTime() { return startTime; }
int Bgm::getnowTime() { return nowTime; }
bool Bgm::getPlayFlag() { return playFlag; }

//開始したら0を返し、停止したら1を返す。その他は-1
int Bgm::playBgm() {
	if (playFlag == false) {
		SetCurrentPositionSoundMem(startDelaySample, bgmHandle);
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_BACK, false);
		startTime = GetNowCount();
		playFlag = true;
		return 0;
	} else if (CheckSoundMem(bgmHandle) == FALSE) {
		playFlag == false;
		return 1;
	} else {
		return -1;
	}
}