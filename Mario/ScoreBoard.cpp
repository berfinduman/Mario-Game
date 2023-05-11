#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
	score = "0";
	lives = MARIO_LIVES;
}


void	ScoreBoard::setScore(int score)
{
	this->score = std::to_string(score);
}

void	ScoreBoard::setLives(int lives)
{
	this->lives = lives;

}

int ScoreBoard::getLives(void)
{
	return lives;
}
string ScoreBoard::getScore(void)
{
	return score;
}