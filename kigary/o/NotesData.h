#pragma once

const int laneNum = 2;//レーンの数(口レーンと胃レーン)
enum LANE_TYPE {
	MOUTH,//口
	STOMACH//胃
};

const int countBeat = 8;//一拍を何分の一拍単位で分割するか（countBeatカウントに一回で一拍毎になる）

bool notesData[][laneNum]{//{口,胃}
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
const int notesNum = sizeof(notesData) / sizeof(notesData[0]);//notesDataの行数を取得
bool notesFlag[notesNum][laneNum] = { 0 };