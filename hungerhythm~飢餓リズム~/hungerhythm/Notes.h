#pragma once
class Notes {
private:
	int posX;
	int posY;
	int r;
	bool alive;
	bool drawFlag;
	int graphHandle;
	int graphX;
	int graphY;

public:
	Notes(const int& posX, const int& posY,  const bool alive, const int r = 8, const bool drawFlag = false, const int graphHandle = -1, const int graphX = 16, const int graphY = 16);
	~Notes();

	bool getAlive();
	int getGraphX();
	int getGraphY();
	int getPosX();
	int getPosY();

	void setR(const int r);

	int notes2judgePointLength(const int& nowTime, const int& judgeTime, const int& oneSecond, const int& roadLength, const double& speed = 1 / 1.5);

	/*
	directionNum : 1 or -1
	-> start - judge�̕���
	*/
	void updateNotesPositionX(const int directionNum, const int& judgePoint, const int& nowTime, const int& judgeTime, const int& oneSecond, const int& roadLength, const double& speed = 1 / 1.5);
	void updateNotesPositionY(const int directionNum, const int& judgePoint, const int& nowTime, const int& judgeTime, const int& oneSecond, const int& roadLength, const double& speed = 1 / 1.5);

	//color : graphHandle��-1�i�摜�Ȃ��j�̏ꍇ�̃m�[�c�̐F
	void drawNotes(const unsigned int color = 0);

	bool checkDrawFlag(const bool moveXFlag, const int startPosition, const int judgePosition);

	//color : graphHandle��-1�i�摜�Ȃ��j�̏ꍇ�̃m�[�c�̐F
	void draw(const bool moveXFlag, const int& startPosition, const int& judgePosition, const unsigned int color = 0U);
};