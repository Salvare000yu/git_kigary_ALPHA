#pragma once
class Bgm {
private:
	int bgmHandle;
	int bpm;
	int startDelaySample;
	int startTime;
	int nowTime;
	bool playFlag;

public:
	Bgm(const int& bgmHandle, const int& bpm, const int& startDelaySample, const int& startTime, const int& nowTime, const bool playFlag = false);
	~Bgm();

	int getBgmHandle();
	int getBpm();
	int getStartDelaySample();
	int getStartTime();
	int getnowTime();
	bool getPlayFlag();

	int playBgm();
};

