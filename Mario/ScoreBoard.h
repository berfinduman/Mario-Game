#pragma once
#include "Common.h"

class ScoreBoard
{
	std::string score;
	int lives;
	int tot_score;

public:

	ScoreBoard();
	void setScore(int score);
	void setLives(int lives);
	int getLives();
	std::string getScore();

};