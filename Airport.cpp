#include "pch.h"
#include "Airport.h"
#include "Tower.h"
#include "Point.h"
#include <iostream>
#include <vector>
#include "Samolot.h"
#include <memory>
#include <cmath>
#include <list>
#include <map>
#include <algorithm>


using namespace std;

//Variables
	vector <Airport*> lotniska;


//CONSTR AND DECONSTR
	Airport::Airport() :
		m_index_ap(lotniska.size()+1), m_waiting_ppl(200),m_no_lines(2),m_tower(this),m_position(0,0)
	{
		lotniska.push_back(this);
		cout << "Airport created with index no: " << m_index_ap << endl;
	}
	Airport::Airport(double x,double y ,int lines) :
		m_index_ap(lotniska.size() + 1), m_waiting_ppl(200),m_position(x,y),m_tower(this),m_no_lines(lines)

	{

		lotniska.push_back(this);
		cout << "Airport created with index no: " << m_index_ap << endl;
	}
//COPYING CONSTRUTOR
	Airport::Airport(const Airport &lotnisko) :
		m_index_ap(lotnisko.m_index_ap), m_waiting_ppl(lotnisko.m_waiting_ppl)
	{
		cout << "copying glorius airport with index: " << m_index_ap << endl;
	}

	Airport::~Airport()
	{
		cout << "Airport with index: " << m_index_ap << " was destroyed" << endl;
	}

//FUNCTIONS
	void Airport::register_plane(std::shared_ptr<Samolot> m_tmp_plane)
	//register plane so that airport knows that it has to manipulate that particular plane
	{
		int tmp_index = m_tmp_plane->get_plane_index(); //get index
		przypisane_samoloty.insert(std::make_pair(tmp_index, m_tmp_plane)); //pair it with *p and insert into ap
		std::map<int, std::shared_ptr<Samolot>>::iterator it = przypisane_samoloty.find(tmp_index);
		//ok so here, we are making sure that we registered plane properly and that it has been added to our map
 		if(it != przypisane_samoloty.end())
		{
			it->second->set_ap_index(m_index_ap);
			cout << "Airport: " << m_index_ap << " registered plane with index: " <<tmp_index<< endl;
			if (debug == 1)
			{
				cout<<"By iterator access check: ";
				it->second->fly_to_airport();
			}
			if (debug == 1)
			{
				cout<<"By Key acces check: ";
				przypisane_samoloty[tmp_index]->fly_to_airport();
			}
		}
	}



//ROUTINES
	void Airport::do_routine()
	/*Quite complicated, but first we assert that we have planes, then we create que, base on planes which are registered for particular airport
	After obtaining que, we look for planes, which are supposed to have done something in present time, if they do, we make them take action
	*/
	{
		std::vector<int> indexes_to_rm;
		//FUNCTION ITERATES OVER VECTOR OF PRZYPISANE_SAMOLOTY, and does routine on everysingle one of them
		if (przypisane_samoloty.size()) //make sure that we have planes to have fun with
			{
			std::cout << "		AIRPORT no: " << m_index_ap << endl;
			create_que(); //Bring Law and Order into succession of actions
			for(multimap<int, int>::const_reverse_iterator it = que.rbegin(); it != que.rend(); ++it) //well, just another iterator
				{
					if (EventSchedule[(it->second)-1] == current_time) //make sure plane needs attention
						{
						if (debug == 0) show_que();
						do_routine_on_plane(przypisane_samoloty[it->second].get()); //do proper stuff on plane
						if (przypisane_samoloty[it->second]->get_status() == flying_away) //if plane wants to quit allow it to do it
							{
							take_off(przypisane_samoloty[it->second].get()); //make plane quit it's life on present airport
							indexes_to_rm.push_back(it->second); //and it to trashing list
							}
						}
				}
			}
			/// REMOVING PLANES routine, but only after we do all stuff on them !!!!!!!!!
			if (indexes_to_rm.size() > 0) //make sure there is something on trashing list
				{
				for (int i = 0; i < indexes_to_rm.size(); i++)
					{
						przypisane_samoloty.erase(indexes_to_rm[i]);
					}
				}
	}

	void Airport::do_routine_on_plane(Samolot* m_tmp_plane)
	/* !!!!!!!!!!!!!!!!!!!!! Probably most important function in whole code !!!!!!!!!!!!!!
	It takes action depending on state of plane in FSM */
	{
		switch (m_tmp_plane->get_status())
		{
		case status_t::flying:
			cout << "     plane no: " << m_tmp_plane->get_plane_index() << " is flying, ";
			//set flight time of plane and it next event by calling this function
			get_flight_time(m_tmp_plane->get_src(), m_tmp_plane->get_plane_index(), 1);
			prioritize(m_tmp_plane);
			break;
		case status_t::waiting:
			cout << "     plane no: " << m_tmp_plane->get_plane_index() << " is waiting for landing" << endl;
			reserve_lane(m_tmp_plane);
			EventSchedule[m_tmp_plane->get_plane_index()-1] += (5*60);
			break;
		case status_t::landing:
			land(m_tmp_plane);
			m_tmp_plane->set_status(maintenance);
			cout << "     plane no: " << m_tmp_plane->get_plane_index() << " is landing" << endl;
			EventSchedule[m_tmp_plane->get_plane_index()-1] += (20*60);
			break;
		case status_t::maintenance:
			service(m_tmp_plane);
			m_tmp_plane->set_status(departing);
			cout << "     plane no: " << m_tmp_plane->get_plane_index() << " is being serviced" << endl;
			EventSchedule[m_tmp_plane->get_plane_index()-1] += (60*60);
			break;
		case status_t::departing:
			reserve_lane(m_tmp_plane);
			cout << "     plane no: " << m_tmp_plane->get_plane_index() << " is leaving" << endl;
			EventSchedule[m_tmp_plane->get_plane_index()-1] += (20*60);
			break;
		}
	}

//ROUTINE SUB FUNCTIONS
	void Airport::land(Samolot* m_tmp_plane)
	{
		//make plane land and clear its prior so it is not attention needing kid
		release_lane(m_tmp_plane);
		m_tmp_plane->clear_priority();
	}

	void Airport::service(Samolot* m_tmp_plane)
	{
		//do stuff on plane
		m_tmp_plane -> set_tech_state(1.0);
		m_tmp_plane ->set_fuel(1.0);
		m_tmp_plane -> increase_priority();
	}


	void Airport::take_off(Samolot* m_tmp_plane)
	{
		int dest_index;
		do{
			dest_index = (rand() % (lotniska.size())+1); //find proper next dst for our plane
		} while (dest_index == m_index_ap );
		//set a lot of stuff
		m_tmp_plane->set_dest(dest_index);
		m_tmp_plane->set_src(m_index_ap);
		m_tmp_plane->fly_to_airport();
		m_tmp_plane->clear_priority();
		int src_index =  m_tmp_plane ->get_src();
		release_lane(m_tmp_plane); //release lane after you are done
		m_tmp_plane->set_status(flying); //go to next state
		//tell me what have you done, now please
		int plane_index = m_tmp_plane->get_plane_index();
		cout << "Reassigning plane no: " << plane_index  << " from: " <<src_index << " to: " << dest_index << endl;
		lotniska[(dest_index - 1)]->register_plane(samoloty[plane_index-1]); //reassign it to next airport


	}
//Various getters for functionality of airport
	int Airport::get_airport_index()
	{
		return m_index_ap;
	}
	int Airport::get_airport_size()
	{
		return m_no_lines;
	}

	void Airport::show_occupancy()
	{
		cout << "Current state of lanes: \n";
		for (int i = 0; i < m_tower.lines; i++)
		{
			for (int j = 0; j < 1; j++) {
				cout << m_tower.m_lines[i][j] << " " << m_tower.m_lines[i][j + 1] << '\n';
			}
		}
	}

//CONDITIONAL REGISTER of plane
	void Airport::reserve_lane(Samolot* tmp_plane)
	{
		/* Fn used to reserve lane to allow plane to switch between states, it's status can't change unless it has free lane
		Fn allowed only for waiting and departing states*/
		int i = get_airport_size();
		int out = 0;
		int plane_index = tmp_plane ->get_plane_index();
		status_t state = tmp_plane->get_status();
		//we iterate over lanes, and if we find free lane we assign plane to lane
		if ((state == waiting) || (state == departing)) //assert state of plane
		{
			do{
				if (i == 0) //make sure we have free lanes, if we don't increase plane prior in futher iterations of AP work
				{
					cout << "	We cannot reserve a line for you plane: " << tmp_plane->get_plane_index() << endl;
					tmp_plane->increase_priority();
				}
				// if plane is waiting to land and we have free lane switch to landing state
				else if (state == waiting)
				{
					if (m_tower.m_lines[i - 1][1] == 0) //find free lane
					{
						tmp_plane->set_status(landing); //move to next state
						m_tower.m_lines[i - 1][1] = tmp_plane->get_plane_index(); //reserve lane
						out = 1; //give out msg
						cout << "	Reservation of line nr: " << m_tower.m_lines[i - 1][0] << " for plane nr: " << tmp_plane->get_plane_index() << endl;
					}
				}
				//if plane is waiting to take off assign it to lane, and to flying_away state
				else if (state == departing)
				{
					if (m_tower.m_lines[i - 1][1] == 0) //find free lane
					{
						tmp_plane->set_status(flying_away); //move to next state
						m_tower.m_lines[i - 1][1] == tmp_plane->get_plane_index(); //reserve lane
						out = 1; //give out msg
						cout << "	Reservation of line nr: " << m_tower.m_lines[i - 1][0] << " for plane nr: " << tmp_plane->get_plane_index() << endl;
						cout << "Plane ready to take off\n";
					}
				}
				i--;
			}while ((out == 0) && (i >= 0));
		}
		else cout<<"WRONG PLANE STATE"<<endl; //lol, why you do this
	if (debug == 1) show_occupancy();
	}

	void Airport::release_lane(Samolot* tmp_plane)
	/*Release lane after it is used by plane to either land or take off */
	{
		if ((tmp_plane->get_status() == flying_away) || (tmp_plane->get_status() == landing))
		{
			int reserved_nr = tmp_plane->get_plane_index();
			for (int i = 0; i < m_tower.lines; i++)
			{
				if (m_tower.m_lines[i][1] == reserved_nr)
				{
					m_tower.m_lines[i][1] = 0;
				}
			}
		}
		if (debug == 1) show_occupancy();
	}

	void Airport::prioritize(Samolot* tmp_plane)
	{
		/* Function used to check state of plane which is flying, if emerg == 1 then try to imediately reserve line */
		if (tmp_plane->get_status() == flying)
		{
			if ((rand()%10) == 0) tmp_plane->set_fuel(0.3);
			bool emerg = tmp_plane->call_emergency();
			if (emerg)
			{
				tmp_plane->set_status(waiting);
				reserve_lane(tmp_plane);
			}
			else
			{
				tmp_plane->set_status(waiting);
			}
		}
	}

	Point Airport::get_position()
	{
		return m_position;
	}

	double Airport::get_distane_from(int dest_index)
	{
		//As name suggests get distance between airports
		Point tmp_src_pos = get_position();
		Point tmp_dst_pos = lotniska[dest_index - 1]->get_position();
		return tmp_src_pos - tmp_dst_pos;
	}


	int Airport::get_flight_time(int dest_index, int plane_index, int set)
	/* get time for next action depending on distance between airports */
	{
		int distance = (int)get_distane_from(dest_index);
		int flight_time = ceil(distance / samoloty[plane_index-1]->get_speed());
		cout<< "estimated time of arrival: "<<flight_time<<endl;
		if (set == 1) EventSchedule[plane_index-1] += (flight_time*60);
		return flight_time;
	}

///QUE FUNCTIONS
	template <typename A, typename B>
	/* Template for sorting map by values, not by keys */
	multimap<B, A> flip_map(map<A,B> & src)
	{
		multimap<B,A> dst; //var init
		for(typename map<A, B>::const_iterator it = src.begin(); it != src.end(); ++it)
			{
				dst.insert(pair<B, A>(it -> second, it -> first));
			}
		return dst;
	}


	void Airport::create_que()
	{
		map<int,int> temp_que; //temp var init
		if (debug == 1) cout<<"Starting que creation"<<endl;
		//iterator creation for source map creation
		for(map<int, std::shared_ptr<Samolot>>::iterator it= przypisane_samoloty.begin(); it!=przypisane_samoloty.end(); it++)
		{
			temp_que.insert(std::make_pair(it->first, it->second->get_priority()));
		}
		que = flip_map(temp_que); //map sorted by values
	}

	int Airport::get_que_size()
	{
		return que.size();
	}

	void Airport::show_que()
	{
		cout<<"Printin que"<<endl;
		for(multimap<int, int>::const_reverse_iterator it = que.rbegin(); it != que.rend(); ++it)
        	cout << it -> first << " " << it -> second << endl;
	}
