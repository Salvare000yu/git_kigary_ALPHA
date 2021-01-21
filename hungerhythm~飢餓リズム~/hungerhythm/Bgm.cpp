#include "Bgm.h"
#include "DxLib.h"

Bgm::Bgm(const int& bgmHandle, const double& bpm, const int& volume, const int& startDelaySample, const int& startTime, const int& nowTime, bool playFlag) {
	this->bgmHandle = bgmHandle;
	this->volume = volume;
	ChangeVolumeSoundMem(this->volume, this->bgmHandle);
	this->bpm = bpm;
	this->startTime = startTime;
	this->nowTime = nowTime;
	this->startDelaySample = startDelaySample;
	this->playFlag = playFlag;
}
Bgm::~Bgm() {

}

int Bgm::getNowTime() { return nowTime; }
bool Bgm::getPlayFlag() { return playFlag; }

int Bgm::oneCountTime(const int& countBeat, const int& oneSecond) {
	return (60.0 * oneSecond) / (bpm * countBeat);
}

void Bgm::playBgm() {
	if (playFlag == false) {
		SetCurrentPositionSoundMem(startDelaySample, bgmHandle);
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_BACK, FALSE);
		startTime = GetNowCount();
		playFlag = true;
	}
	nowTime = GetNowCount() - startTime;
	if (CheckSoundMem(bgmHandle) == FALSE) {
		playFlag = false;
	}
}