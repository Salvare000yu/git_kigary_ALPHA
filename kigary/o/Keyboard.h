#pragma once
class Keyboard {
private:
	char keys[256];
	char oldkeys[256];

public:
	Keyboard();
	~Keyboard();

	//inputKey = KEY_INPUT_�Ȃ�Ƃ�
	char getKeys(int inputKey);
	char getOldkeys(int inputKey);

	void updateKey();//�ŐV�L�[�{�[�h����O�t���[���̃L�[�{�[�h���ɂ��A�ŐV�̃L�[�{�[�h�����擾
};