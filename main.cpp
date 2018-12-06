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


void runner(int n_hours_to_simulate = 1)
{
	do
	{
		for (int i=0; i<EventSchedule.size(); i++)
			{
				if (EventSchedule[i] = current_time)
					{
						int has_to_do = samoloty[i] -> get_dest();
						cout<< current_time <<" ### AIRPORT no: "<<has_to_do<<" ### "<<endl;
						lotniska[has_to_do-1]->do_routine();

					}


			}



		
		current_time+=5*60;
	// } while (current_time <= init_time + 60*60*n_hours_to_simulate);
	}while(current_time <= 960422520);
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
