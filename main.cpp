#include "pch.h"
#include <iostream>
#include "Samolot.h"
#include "Airport.h"
#include "Point.h"
#include <vector>
#include <ctime>
#include <string>

//Variables
using namespace std;
char time_buffer [80];
int always_print = 0;


void initialize()
{
	/* Takes care of assigning planes into proper places */
	cout<<"Starting initialization"<<endl;
	cout << " Size of samoloty: " << samoloty.size() << endl;
	// INITIAL PLANE ASSIGNING
	for (int i = 0; i < samoloty.size(); i++)
	{
		int dest_index = (samoloty[i]->get_dest());
		cout<<dest_index<<endl;
		lotniska[(dest_index - 1)]->register_plane(samoloty[i]);
	}
	cout << "\n \n Size of samoloty: " << samoloty.size() << endl;
	cout <<"######################## Finished initialization of objects ########################\n\n"<<endl;
}

void runner(int n_hours_to_simulate = 10)
{
	/*Simulate for some time */
	int selected_airport;
	do
	{
		int time_print_flag = 0; //variable for printing time only once
		if (always_print == 1)
		{
			strftime(time_buffer, 80, "%F %X", localtime(&current_time));
			std::cout << "\n" << time_buffer << "----------------------" << endl;
		}
		for (int i = 0; i < EventSchedule.size(); i++)
		{

			if (EventSchedule[i] == current_time) // IF TIME IS RIGHT DO STUFF
			{
				if (time_print_flag == 0) // if didnt print yet do it
				{
					if (always_print == 0)
					{
						strftime(time_buffer, 80, "%F %X", localtime(&current_time));
						std::cout << "\n" << time_buffer << "----------------------" << endl;
						time_print_flag = 1;
					}
				}
				// find proper ap to do stuff in proper time
				selected_airport = (samoloty[i]->get_ap_index());
				lotniska[selected_airport - 1]->do_routine();
			}


		}



		time_print_flag = 0; //clear flag
		current_time +=60; // MOVE INTO THE FUTURE
	} while (current_time <= init_time + 3600 * n_hours_to_simulate);
	std::cout << "######################## Finished simulation, cleaning up ########################\n\n" << endl;
}



void create_planes(int x) // create arbitraty amount of planes
{
	for (int i = 0; i < x; i++)
	{
		Samolot tmp_plane = new Samolot;

	}
}

double random_coordinate() // get random coordinates for airports
{
	return (-3000 + (rand() % 1500));
}
void create_airports(int x) // create arbitrary amount of airports
{
	for (int i = 0; i < x; i++)
	{
		Airport * tmp_airport = new Airport(random_coordinate(), random_coordinate(), 2);
	}
}

void clear_airports() // clearing memory after
{
	int delete_size = lotniska.size();
	for (int i = 0; i < delete_size; i++)
	{
		delete lotniska[i];
	}
}
int main()
{
	srand(time(NULL));

	debug = 0; //check debug mode
	always_print = 0; // if 1 writes in 5 min intervals, if 0 writes when needed
	//Airport Los_Angles(1500,-1500,5), Katowice(200,100,5), London(400,-400,5), Moscow(1000,2000,10);
	//Samolot p1,p2,p3,p4,p5,p6,p7;
	create_airports(4);
	create_planes(8);
	initialize();
	runner();
	clear_airports();

	return 0;
}
