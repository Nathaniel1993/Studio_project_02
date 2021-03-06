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
bool Score::killedenemy = false;
bool Score::lostlive = false;

int Score::highscore_container[5] = { 0, 0, 0, 0, 0 };
int Score::enemyPoints = 200;
int Score::lifeLostPoints = 400;
int Score::multiplier_count = 0;
float Score::score_multiplier = 1.0f;

Score::Score()
{
}

Score::~Score()
{

}
void Score::calculate() //Calculate current score in scene(those with enemies) update
{
	//change score from string to double for calculation
	double num_score = stod(score_string);

	//===============================Scene01===================================
	//Combo kill(killed enemies while not losing life)
	if (killedenemy)
	{
		if (multiplier_count >= 5 && multiplier_count <= 10)
		{
			score_multiplier = 1.2f;
		}
		else if (multiplier_count >= 10 && multiplier_count <= 15)
		{
			score_multiplier = 1.3f;
		}
		else if (multiplier_count >= 15 && multiplier_count <= 20)
		{
			score_multiplier = 1.4f;
		}
		else if (multiplier_count >= 20)
		{
			score_multiplier = 1.5f;
		}
		num_score += (enemyPoints * score_multiplier);
		killedenemy = false;
		multiplier_count++;
	}
	//character lost a life
	if (lostlive)
	{
		if (num_score >= lifeLostPoints)
		{
			num_score -= lifeLostPoints;
		}
		else
		{
			num_score -= num_score;
		}
		multiplier_count = 0;
		score_multiplier = 1.0f;
		lostlive = false;
	}

	//change back to string
	score_string = to_string((int)num_score);
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
	else
	{
		cout << "Unable to open file" << endl;
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