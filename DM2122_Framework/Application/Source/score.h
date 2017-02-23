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
	
	static bool tookitem;
	static bool killedenemy;
	static bool lostlive;
	static int highscore_container[5];
	static bool highscoreset;
	static int multiplier_count;
	static double score_multiplier;

private:
	static int itempoints;
	static int enemypoints;
	static int lifelostpoints;
	
	
};

#endif