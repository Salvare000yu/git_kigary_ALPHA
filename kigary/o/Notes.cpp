#include "Notes.h"
#include "DxLib.h"
#include <cmath>

Notes::Notes(const int& posX, const int& posY, const bool alive) {
	this->posX = posX;
	this->posY = posY;
	this->alive = alive;
}
Notes::~Notes() {

}

int Notes::getPosX() { return posX; }
int Notes::getPosY() { return posY; }
bool Notes::getAlive() { return alive; }

int Notes::notes2judgePointLength(const int& nowTime, const int& judgeTime, const int& oneSecond, const unsigned int& roadLength, const double& speed) {
	return (int)((judgeTime - nowTime) * (double)roadLength * speed) / oneSecond;
}

void Notes::update(const int& judgeX, const int& judgeY, const double& angle, const int& nowTime, const int& judgeTime, const int& oneSecond, const unsigned int& roadLength, const double& speed) {
	posX = cos(angle) * notes2judgePointLength(nowTime, judgeTime, oneSecond, roadLength, speed);
	posY = sin(angle) * notes2judgePointLength(nowTime, judgeTime, oneSecond, roadLength, speed);

}