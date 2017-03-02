#ifndef SCORE_H
#define SCORE_H

#include <string>
using std::string;

class Score
{
public:
	Score();
	~Score();
	static void calculate();
	static void highscoreboard();
	static void comparescore();
	static string score_string;
	
	static bool killedenemy;
	static bool lostlive;
	static bool highscoreset;

	static int highscore_container[5];
	static int multiplier_count;
	static float score_multiplier;

private:
	static int enemyPoints;
	static int lifeLostPoints;
	
};

#endif