#pragma once

const int laneNum = 2;//���[���̐�(�����[���ƈ݃��[��)
enum LANE_TYPE {
	MOUTH,//��
	STOMACH//��
};

const int countBeat = 8;//�ꔏ�������̈ꔏ�P�ʂŕ������邩�icountBeat�J�E���g�Ɉ��ňꔏ���ɂȂ�j

bool notesData[][laneNum]{//{��,��}
	{1,0},//1
	{0,0},
	{0,0},
	{0,0},
	{0,1},
	{0,0},
	{0,0},
	{0,0},
	{1,0},//8
	{0,0},
	{0,0},
	{0,0},
	{0,1},
	{0,0},
	{0,0},
	{0,0},
	{1,0},//16
	{0,0},
	{0,0},
	{0,0},
	{0,1},
	{0,0},
	{0,0},
	{0,0},
	{1,0},//24
	{0,0},
	{0,0},
	{0,0},
	{0,1},
	{0,0},
	{0,0},
	{0,0},
	{1,0},//32
};
const int notesNum = sizeof(notesData) / sizeof(notesData[0]);//notesData�̍s�����擾
bool notesFlag[notesNum][laneNum] = { 0 };