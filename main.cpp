#include "pch.h"
#include <iostream>
#include "Samolot.h"
#include "Airport.h"
#include <vector>
#include <ctime>


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
	cout << "\n \n" << "Size of samoloty: " << samoloty.size() << endl;
	runner();
	
	return 0;
}
