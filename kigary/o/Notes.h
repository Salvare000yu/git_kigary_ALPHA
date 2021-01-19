#pragma once
class Notes {
private:
	int posX;
	int posY;
	bool alive;

public:
	Notes(const int& posX, const int& posY, const bool alive = false);
	~Notes();

	int getPosX();
	int getPosY();
	bool getAlive();

	int notes2judgePointLength(const int& nowTime, const int& judgeTime, const int& oneSecond, const unsigned int& roadLength, const double& speed = 1 / 1.5);

	void update(const int& judgeX, const int& judgeY, const double& angle, const int& nowTime, const int& judgeTime, const int& oneSecond, const unsigned int& roadLength, const double& speed = 1 / 1.5);

};