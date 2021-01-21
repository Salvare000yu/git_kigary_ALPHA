#pragma once
class Bgm {
private:
	int bgmHandle;
	double bpm;
	int volume;
	int startTime;
	int nowTime;
	int startDelaySample;
	bool playFlag;

public:
	Bgm(const int& bgmHandle, const double& bpm, const int& volume = 255, const int& startDelaySample = 0, const int& startTime = 0, const int& nowTime = 0, bool playFlag = false);
	~Bgm();

	int getNowTime();
	bool getPlayFlag();

	int oneCountTime(const int& countBeat = 8, const int& oneSecond = 1000);

	void playBgm();
};