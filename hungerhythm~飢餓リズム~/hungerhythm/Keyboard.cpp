#include "Keyboard.h"
#include "DxLib.h"

Keyboard::Keyboard() {
	for (int i = 0; i < 256; i++) {
		keys[i] = 0;
		oldkeys[i] = 0;
	}
}
Keyboard::~Keyboard() {

}

//inputKey = KEY_INPUT_なんとか
char Keyboard::getKeys(int inputKey) { return keys[inputKey]; }
char Keyboard::getOldkeys(int inputKey) { return oldkeys[inputKey]; }

void Keyboard::updateKey() {
	//最新のキーボード情報だったものを前フレームのキーボード情報にする
	for (int i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	//最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}