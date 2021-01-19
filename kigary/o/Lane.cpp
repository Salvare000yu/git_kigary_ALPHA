#include "Lane.h"
Lane::Lane(const int& startX, const int& startY, const int& judgeX, const int& judgeY, const int& judgeR, const int& missR) {
	this->startX = startX;
	this->startY = startY;
	this->judgeX = judgeX;
	this->judgeY = judgeY;
	this->judgeR = judgeR;
	this->missR = missR;
}
Lane::~Lane() {

}

int Lane::getStartX() { return startX; }
int Lane::getStartY() { return startY; }
int Lane::getJudgeX() { return judgeX; }
int Lane::getJudgeY() { return judgeY; }
int Lane::getJudgeR() { return judgeR; }
int Lane::getMissR() { return missR; }