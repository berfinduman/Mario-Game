#pragma once
#include "Common.h"
class ScoreBoard
{
	string score;
	int lives;
public:
	ScoreBoard();
	void setScore(int score);
	void setLives(int lives);
	int getLives(void);
	string getScore();
};