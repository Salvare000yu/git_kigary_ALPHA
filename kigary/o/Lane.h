#pragma once
class Lane {
private:
	int startX;
	int startY;
	int judgeX;
	int judgeY;
	int judgeR;	//判定範囲
	int missR;	//ミスの範囲（判定範囲込み）

public:
	Lane(const int& startX, const int& startY, const int& judgeX, const int& judgeY, const int& judgeR, const int& missR);
	~Lane();

	int getStartX();
	int getStartY();
	int getJudgeX();
	int getJudgeY();
	int getJudgeR();
	int getMissR();
};

