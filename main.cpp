#include "pch.h"
#include <iostream>
#include "Samolot.h"
#include "Airport.h"
#include "Tower.h"
#include <vector>
#include <ctime>

using namespace std;
char time_buffer [80];


void initialize()
{
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
	int selected_airport;
	do
	{
		int time_print_flag=0;
		for (int i=0; i<EventSchedule.size(); i++)
			{
				
				if (EventSchedule[i] <= current_time)
					{
						if (time_print_flag==0)
							{
							strftime(time_buffer,80,"%F %X",localtime(&current_time));
							cout<<time_buffer<<"----------------------"<<endl;
							time_print_flag =1;
							}
						selected_airport = (samoloty[i]->get_ap_index());
						cout<<"		AIRPORT no: "<<selected_airport<<endl;
						lotniska[selected_airport-1]->do_routine();

					}


			}



		time_print_flag =0;
		current_time+=5*60;
	}while(current_time <= init_time+3600*n_hours_to_simulate);
	cout<< "######################## Finished simulation, cleaning up ########################\n\n"<<endl;
}

int main()
{
	srand(time(NULL));
	Airport Chujkowo(5);
	Airport Dupowo(7);
	Tower t(&Dupowo);
	Samolot p1, p2, p3;
	t.reserve_line(&Dupowo, &p1);
	t.reserve_line(&Dupowo, &p2);
	t.reserve_line(&Dupowo, &p3);
	t.show_occupancy();
	Airport Los_Angles, Katowice, London;
	initialize();
	runner();
	
	return 0;
}
