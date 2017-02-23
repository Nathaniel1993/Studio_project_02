#include "score.h"

#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::stoi;
using std::to_string;
using std::ifstream;
using std::ofstream;
using std::swap;

string Score::score_string = "0";
bool Score::highscoreset = false;
int Score::highscore_container[5] = { 0, 0, 0, 0, 0 };
int Score::itempoints = 100;
int Score::enemypoints = 200;
int Score::lifelostpoints = 500;
bool Score::tookitem = false;
bool Score::killedenemy = false;
bool Score::lostlive = false;

Score::Score()
{
}

Score::~Score()
{

}
void Score::calculate() //Calculate current score in scene(those with enemies) update
{
	//change score from string to int for calculation
	int num_score = stoi(score_string);

	//pick up item that increase score
	if (tookitem == true)
	{
		num_score += itempoints;
		tookitem = false;
	}

	//killed an enemy
	if (killedenemy == true)
	{
		num_score += enemypoints;
		killedenemy = false;
	}

	//character lost a life
	if (lostlive == true)
	{
		if (num_score >= lifelostpoints)
		{
			num_score -= lifelostpoints;
		}
		else
		{
			num_score -= num_score;
		}
		lostlive = false;
	}

	//change back to string
	score_string = to_string(num_score);
}
void Score::highscoreboard() //Updates highscores which are recorded in an external text file - after game end / game over
{
	//Temporary string
	string line;

	//Read file
	ifstream myfile("Source//highscore.txt");
	if (myfile.is_open())
	{
		int i = 0;
		//Read file and place them into container line by line
		while (getline(myfile, line))
		{
			int num_line = stoi(line);
			highscore_container[i] = num_line;
			i++;
		}
		myfile.close();

		//Sorts out highscore
		comparescore();

		//Checks and update highscore if needed
		int currentscore = stoi(score_string);
		if (currentscore > highscore_container[4] && highscoreset == false) //check with lowest score in the record
		{
			highscore_container[4] = currentscore;
			highscoreset = true;
		}
		//Records highscore from sorted out container
		ofstream myFile("Source//highscore.txt");
		for (int h = 0; h < 5; h++)
		{
			myFile << highscore_container[h] << "\n"; //record highscore in multiple lines
		}
		myFile.close();
	}
}
void Score::comparescore() //Sorting out the highscores - called in highscoreboard()
{
	while ((highscore_container[0] < highscore_container[1]) ||
		(highscore_container[1] < highscore_container[2]) ||
		(highscore_container[2] < highscore_container[3]) ||
		(highscore_container[3] < highscore_container[4]))
	{
		int highscore_container_size = (sizeof(highscore_container) / sizeof(highscore_container[0])); //total byte size divide by byte size of element
		// 20 / 4 = 5
		for (int a = highscore_container_size - 1; a > 0; --a)
		{
			//4-3
			//3-2
			//2-1
			//1-0

			if (highscore_container[a] > highscore_container[a - 1]) //checks 1st with 2nd,then 2nd with 3rd,and so on
			{//if smaller,swap the two
				swap(highscore_container[a], highscore_container[a - 1]);
			}
			else if (a == 0) // if index a = 0, stop checking
			{
				break;
			}
			
		}
	}
}