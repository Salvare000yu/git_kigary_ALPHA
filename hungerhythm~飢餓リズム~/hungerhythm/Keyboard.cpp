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

//inputKey = KEY_INPUT_�Ȃ�Ƃ�
char Keyboard::getKeys(int inputKey) { return keys[inputKey]; }
char Keyboard::getOldkeys(int inputKey) { return oldkeys[inputKey]; }

void Keyboard::updateKey() {
	//�ŐV�̃L�[�{�[�h��񂾂������̂�O�t���[���̃L�[�{�[�h���ɂ���
	for (int i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	//�ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}