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
	{
		//register plane so that airport knows that it has to manipulate that particular plane
		int tmp_index = m_tmp_plane->get_plane_index();
		przypisane_samoloty.insert(std::make_pair(tmp_index, m_tmp_plane));
		que.push_back(tmp_index);
		// if (EventSchedule[przypisane_samoloty.back()->get_plane_index()-1] == init_time) register_lane(przypisane_samoloty.back());
		std::map<int, std::shared_ptr<Samolot>>::iterator it = przypisane_samoloty.find(tmp_index);
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
			cout<<que.size()<<endl;
		}
	}



//ROUTINES
	void Airport::do_routine_on_plane(Samolot* m_tmp_plane)
	{
		//HEART OF ACTION IF DOES APRIOPRIATE ACTIONS DEPENDING ON STATUS OF PLANE
		//iterate over converted int status
		//taking apriopriate actions
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
			m_tmp_plane->set_status(flying_away);
			cout << "     plane no: " << m_tmp_plane->get_plane_index() << " is leaving" << endl;
			EventSchedule[m_tmp_plane->get_plane_index()-1] += (20*60);
			break;
		}
	}


	void Airport::do_routine()
	{
		std::vector<int> indexes_to_rm;
		//FUNCTION ITERATES OVER VECTOR OF PRZYPISANE_SAMOLOTY, and does routine on everysingle one of them
		if (que.size() > 0)
			{
			std::cout << "		AIRPORT no: " << m_index_ap << endl;
			std::list<int>::iterator it = que.begin();
			while(it != que.end())
				{
					if (EventSchedule[(przypisane_samoloty[*it]->get_plane_index())-1] == current_time)
						{

						if (debug == 1) cout<<"doing plane with index: "<<*it<<endl;
						do_routine_on_plane(przypisane_samoloty[*it].get());
						if (przypisane_samoloty[*it]->get_status() == flying_away)
							{
							if (debug == 1) show_que();
							take_off(przypisane_samoloty[*it].get());
							indexes_to_rm.push_back(*it);
							if (debug == 1) show_que();
							}
						}
				it++;
				}

			}

				/// REMOVING PLANES
			if (indexes_to_rm.size() > 0)
				{
				for (int i = 0; i < indexes_to_rm.size(); i++)
					{
						que.remove(indexes_to_rm[i]);
						przypisane_samoloty.erase(indexes_to_rm[i]);
					}
				}

	}


//ROUTINE SUB FUNCTIONS
	void Airport::land(Samolot* m_tmp_plane)
	{
		release_lane(m_tmp_plane);
	}

	void Airport::service(Samolot* m_tmp_plane)
	{
		//load people to plane
		m_tmp_plane -> set_tech_state(1.0);
		m_tmp_plane ->set_fuel(1.0);
	}


	void Airport::take_off(Samolot* m_tmp_plane)
	{
		int dest_index;
		do
		{
			dest_index = (rand() % (lotniska.size())+1);
		} while (dest_index == m_index_ap );
		m_tmp_plane->set_dest(dest_index);
		m_tmp_plane->set_src(m_index_ap);
		m_tmp_plane->fly_to_airport();
		int src_index =  m_tmp_plane ->get_src();
		release_lane(m_tmp_plane);
		m_tmp_plane->set_status(flying);
		int plane_index = m_tmp_plane->get_plane_index();
		cout << "Reassigning plane no: " << plane_index  << " from: " <<src_index << " to: " << dest_index << endl;
		lotniska[(dest_index - 1)]->register_plane(samoloty[plane_index-1]);


	}

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

//CONDITIONAL REGISTER
	bool Airport::reserve_lane(Samolot* tmp_plane)
	{
		int i = get_airport_size();
		// cout << "NUMBER OF LINES: " << i << endl;
		int out = 0;
		bool res;
		int plane_index = tmp_plane ->get_plane_index();
		do
		{

			if (i == 0)
			{
				cout << "	We cannot reserve a line for you plane: " << tmp_plane->get_plane_index() << endl;
				tmp_plane->set_status(waiting);
				res = 0;
			}
			else if ((tmp_plane->get_status() == waiting) && (i>0))
			{
				if (m_tower.m_lines[i - 1][1] == 0)
				{

					tmp_plane->set_status(landing);

					m_tower.m_lines[i - 1][1] = tmp_plane->get_plane_index();
					out = 1;
					cout << "	Reservation of line nr: " << m_tower.m_lines[i - 1][0] << " for plane nr: " << tmp_plane->get_plane_index() << endl;
					res = 1;
				}
				//to sie wgl kiedykolwiek wykonuje?????
				else if (m_tower.m_lines[i - 1][1] == tmp_plane->get_plane_index())
				{
					cout << "	A lane has been reserved for: " << tmp_plane->get_plane_index() << endl;
					tmp_plane->set_status(landing);
					out = 1;
				}

			}

			i--;

		} while ((out == 0) && (i >= 0));
	if (debug == 1) show_occupancy();
	}

	void Airport::release_lane(Samolot* tmp_plane)
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
		if ((rand()%5) == 0) tmp_plane->set_fuel(0.3);
		bool emerg = tmp_plane->call_emergency();
		if (emerg)
		{
			////// newpiece of code
			if (~(std::find(que.begin(), que.end(), tmp_plane->get_plane_index()) != que.end()));
			{
				que.push_back(tmp_plane->get_plane_index());
				cout<<"Added priority case for: "<<tmp_plane->get_plane_index()<<endl;
			}
			reserve_lane(tmp_plane);
		}
		else
		{
			tmp_plane->set_status(waiting);
		}
	}

	Point Airport::get_position()
	{
		return m_position;
	}

	double Airport::get_distane_from(int dest_index)
	{
		Point tmp_src_pos = get_position();
		Point tmp_dst_pos = lotniska[dest_index - 1]->get_position();
		return tmp_src_pos - tmp_dst_pos;
	}


	int Airport::get_flight_time(int dest_index, int plane_index, int set)
	{
		int distance = (int)get_distane_from(dest_index);
		int flight_time = ceil(distance / samoloty[plane_index-1]->get_speed());
		cout<< "estimated time of arrival: "<<flight_time<<endl;
		if (set == 1) EventSchedule[plane_index-1] += (flight_time*60);
		return flight_time;
	}

	int Airport::get_que_size(){return que.size();}

	void Airport::show_que()
	{
		for (int n:que){cout<<n<<" ";}
		cout<<" "<<endl;
	}
