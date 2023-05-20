#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
	score = "0000";
	lives = MARIO_LIVES;
	int tot_score = 0;
}


void	ScoreBoard::setScore(int score)
{
	this->tot_score += score;
	this->score = std::to_string(this->tot_score);
}

void	ScoreBoard::setLives(int exp_lives)
{

	this->lives -= exp_lives;

}

int ScoreBoard::getLives(void)
{
	return lives;
}
string ScoreBoard::getScore()
{
	return score;
}