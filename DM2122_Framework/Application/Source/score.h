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
	static bool powerOn;
	static bool doorsOpened;
	static bool gateOpened;
	static bool highscoreset;

	static int highscore_container[5];
	static int multiplier_count;
	static double score_multiplier;

private:
	static int itemPoints;
	static int enemyPoints;
	static int lifeLostPoints;
	static int powerSwitchPoints;
	static int doorSwitchPoints;
	static int gateButtonPoints;
	
	
};

#endif