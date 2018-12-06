#include "pch.h"
#include <iostream>
#include "Samolot.h"
#include "Airport.h"
#include <vector>
#include <ctime>

using namespace std;


void initialize()
{
	// INITIAL PLANE ASSIGNING
	for (int i = 0; i < samoloty.size(); i++)
	{
		int dest_index = (samoloty[i]->get_dest());
		lotniska[(dest_index - 1)]->register_plane(samoloty[i]);
	}
	cout << "\n \n Size of samoloty: " << samoloty.size() << endl;
	cout <<"######################## Finished initialization of objects ########################\n\n"<<endl;
}


void runner(int n_hours_to_simulate = 5)
{
	do
	{
		for (int i=0; i<EventSchedule.size(); i++)
			{
				


			}



		
		current_time+=5*60;
	} while (current_time <= init_time + 60*60*n_hours_to_simulate);
	
		for (int i = 0; i < lotniska.size(); i++)
		{
			cout<<"### AIRPORT no: "<<i+1<<" ### "<<endl; //remeber about shifting number by +1(vector indexing)
			lotniska[i]->do_routine();
		}
		current_time +=(30*60);
	}
	cout<< "######################## Finished simulation, cleaning up ########################\n\n"<<endl;
}

int main()
{
	srand(time(NULL));
	Airport Los_Angles, Katowice, London;
	Samolot p1, p2;
	initialize();
	runner();
	
	return 0;
}
