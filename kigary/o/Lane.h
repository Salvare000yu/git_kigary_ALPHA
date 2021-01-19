#pragma once
class Lane {
private:
	int startX;
	int startY;
	int judgeX;
	int judgeY;
	int judgeR;	//����͈�
	int missR;	//�~�X�͈̔́i����͈͍��݁j

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

