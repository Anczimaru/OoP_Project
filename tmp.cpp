// tmp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Samolot.h"
#include "Airport.h"
#include <vector>
#include <ctime>

vector <Samolot*> samoloty;
vector <Airport*> lotniska;


using namespace std;


void runner(int number_of_iterations = 10)
{

	// INITIAL PLANE ASSIGNING
	for (int i = 0; i < samoloty.size(); i++)
	{
		int dest_index = (samoloty[i]->get_dest());
		lotniska[(dest_index - 1)]->register_plane(samoloty[i]);


	}

	// MAIN RUNNER FOR ALL CODE/////////////////////////////////////////////////////
	for (int i = 0; i < number_of_iterations; i++)
	{
		for (int i = 0; i < lotniska.size(); i++)
		{
			lotniska[i]->do_routine();
		}
	}





}
int main()
{
	srand(time(NULL));
	Airport Los_Angles, Katowice, London;
	Samolot p1, p2;
	runner();
	cout << "\n \n" << "Size of samoloty: " << samoloty.size() << endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
