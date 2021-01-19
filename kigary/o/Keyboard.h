#pragma once
class Keyboard {
private:
	char keys[256];
	char oldkeys[256];

public:
	Keyboard();
	~Keyboard();

	//inputKey = KEY_INPUT_なんとか
	char getKeys(int inputKey);
	char getOldkeys(int inputKey);

	void updateKey();//最新キーボード情報を前フレームのキーボード情報にし、最新のキーボード情報を取得
};