#include "Notes.h"
#include "DxLib.h"
#include <cmath>

Notes::Notes(const int& posX, const int& posY, const bool alive, const int r, const bool drawFlag, const int graphHandle, const int graphX, const int graphY) {
	this->posX = posX;
	this->posY = posY;
	this->alive = alive;
	this->r = r;
	this->drawFlag = drawFlag;
	this->graphHandle = graphHandle;
	if (graphHandle == -1) {
		this->graphX = graphX;
		this->graphY = graphY;
	} else {
		GetGraphSize(this->graphHandle, &this->graphX, &this->graphY);
		this->r = this->graphX / 2;
	}
}
Notes::~Notes() {

}

bool Notes::getAlive() { return alive; }
int Notes::getGraphX() { return graphX; }
int Notes::getGraphY() { return graphY; }
int Notes::getPosX() { return posX; }
int Notes::getPosY() { return posY; }

void Notes::setR(const int r) { this->r = r; }

int Notes::notes2judgePointLength(const int& nowTime, const int& judgeTime, const int& oneSecond, const int& roadLength, const double& speed) {
	return (int)((judgeTime - nowTime) * (double)roadLength * speed) / oneSecond;
}

void Notes::updateNotesPositionX(const int directionNum, const int& judgePoint, const int& nowTime, const int& judgeTime, const int& oneSecond, const int& roadLength, const double& speed) {
	posX = judgePoint + notes2judgePointLength(nowTime, judgeTime, oneSecond, roadLength, speed) * directionNum;
}
void Notes::updateNotesPositionY(const int directionNum, const int& judgePoint, const int& nowTime, const int& judgeTime, const int& oneSecond, const int& roadLength, const double& speed) {
	posY = judgePoint + notes2judgePointLength(nowTime, judgeTime, oneSecond, roadLength, speed) * directionNum;
}


void Notes::drawNotes(const unsigned int color) {
	if (graphHandle == -1) {
		DrawCircle(posX, posY, r, color);
	} else {
		DrawExtendGraph(posX - r, posY - r, posX + r - 1, posY + r - 1, graphHandle, TRUE);
	}
}

bool Notes::checkDrawFlag(const bool moveXFlag, const int startPosition, const int judgePosition) {
	bool flag = false;
	if (startPosition > judgePosition) {
		if (moveXFlag) {
			if (startPosition >= posX) {
				flag = true;
			}
		} else {
			if (startPosition >= posY) {
				flag = true;
			}
		}
	} else {
		if (moveXFlag) {
			if (startPosition <= posX) {
				flag = true;
			}
		} else {
			if (startPosition <= posY) {
				flag = true;
			}
		}
	}
	return flag;
}

void Notes::draw(const bool moveXFlag, const int& startPosition, const int& judgePosition, const unsigned int color) {
	if (alive == true) {
		if (checkDrawFlag(moveXFlag, startPosition, judgePosition) == true) {
			drawNotes(color);
		}
	}
}