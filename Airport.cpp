#include "pch.h"
#include "Airport.h"
#include <iostream>
#include <vector>
#include "Samolot.h"
#include <memory>


using namespace std;

vector <Airport*> lotniska;

int RandomizeAirportIndex()  
{
	int give;
	do {
		give = rand() % (lotniska.size()+1);
	} while (give == 0);
	return give;

}



//CONSTR AND DECONSTR
Airport::Airport() :
	m_index_ap(lotniska.size()+1), m_waiting_ppl(200),m_no_lines(2)
{
	lotniska.push_back(this);
	cout << "Airport created with index no: " << m_index_ap << endl;
}
Airport::Airport(int lines) :
	m_index_ap(lotniska.size() + 1), m_waiting_ppl(200)

{
	m_no_lines = lines;
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
	przypisane_samoloty.push_back(m_tmp_plane);
	int pl_index = przypisane_samoloty.back()->get_plane_index();
	cout << "Airport: " << m_index_ap << " registered plane with index: " <<pl_index << endl;
	przypisane_samoloty.back()->fly_to_airport();
	przypisane_samoloty.back()->set_ap_index(m_index_ap);
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
		m_tmp_plane->set_status(waiting);
		cout << "     plane no: " << m_tmp_plane->get_plane_index() << " is flying" << endl;
		EventSchedule[m_tmp_plane->get_plane_index()-1] += (30*60);
		break;
	case status_t::waiting:
		m_tmp_plane->set_status(landing);
		cout << "     plane no: " << m_tmp_plane->get_plane_index() << " is waiting for landing" << endl;
		EventSchedule[m_tmp_plane->get_plane_index()-1] += (30*60);
		break;
	case status_t::landing:
		land(m_tmp_plane);
		m_tmp_plane->set_status(unloading);
		cout << "     plane no: " << m_tmp_plane->get_plane_index() << " landed" << endl;
		EventSchedule[m_tmp_plane->get_plane_index()-1] += (30*60);
		break;
	case status_t::unloading:
		unload(m_tmp_plane);
		m_tmp_plane->set_status(repairing);
		cout << "     plane no: " << m_tmp_plane->get_plane_index() << " was unloaded" << endl;
		EventSchedule[m_tmp_plane->get_plane_index()-1] += (30*60);
		break;
	case status_t::repairing:
		repair(m_tmp_plane);
		m_tmp_plane->set_status(refueling);
		cout << "     plane no: " << m_tmp_plane->get_plane_index() << " repaired" << endl;
		EventSchedule[m_tmp_plane->get_plane_index()-1] += (30*60);
		break;
	case status_t::refueling:
		refuel(m_tmp_plane);
		m_tmp_plane->set_status(loading);
		cout << "     plane no: " << m_tmp_plane->get_plane_index() << " refeueled" << endl;
		EventSchedule[m_tmp_plane->get_plane_index()-1] += (30*60);
		break;
	case status_t::loading:
		load(m_tmp_plane);
		m_tmp_plane->set_status(departing);
		cout << "     plane no: " << m_tmp_plane->get_plane_index() << " loaded" << endl;
		EventSchedule[m_tmp_plane->get_plane_index()-1] += (30*60);
		break;
	case status_t::departing:
		m_tmp_plane->set_status(flying_away);
		cout << "     plane no: " << m_tmp_plane->get_plane_index() << " is leaving" << endl;
		EventSchedule[m_tmp_plane->get_plane_index()-1] += (30*60);
		break;
	}
}
void Airport::do_routine()
{
	//FUNCTION ITERATES OVER VECTOR OF PRZYPISANE_SAMOLOTY, and does routine on everysingle one of them
	if (przypisane_samoloty.size() > 0)
		{
		for (int i = 0; i < przypisane_samoloty.size(); i++)
			{
			if (EventSchedule[(przypisane_samoloty[i]->get_plane_index())-1] == current_time)
				{
				do_routine_on_plane(przypisane_samoloty[i].get());
				if (przypisane_samoloty[i]->get_status() == flying_away)
					{
					take_off(przypisane_samoloty[i].get());
					przypisane_samoloty.erase(przypisane_samoloty.begin() + i);
					}
				}
			}
	}
	/////////////               UNCOMENT LATER ON !!!!!!!!!!!!!!! //////////////
	// else cout<<"    Airport no: "<<m_index_ap<<" is empty"<<endl; 





}
//ROUTINE SUB FUNCTIONS
void Airport::land(Samolot* m_tmp_plane) ///////////////// DO POPRAWKI
{
	do
	{
		m_tmp_plane->set_dest(RandomizeAirportIndex());

	} while ((m_tmp_plane->get_dest()) == m_index_ap);

	m_tmp_plane->set_src(m_index_ap);
	m_tmp_plane->fly_to_airport();
	//wyladuje samolot

}

void Airport::load(Samolot* m_tmp_plane)
{
	//load people to plane
	int cap{ m_tmp_plane->get_capacity() };
	int ppl_to_load;
	(cap <= m_waiting_ppl) ? (ppl_to_load = cap) : (ppl_to_load = m_waiting_ppl);
	m_tmp_plane->set_passengers(ppl_to_load);
	cout << "         Loaded : " << m_tmp_plane->get_passengers() << " passengers" << endl;
}

void Airport::unload(Samolot* m_tmp_plane)
{
	//unload ppl from plane
	int tmp_ppl_unloaded = m_tmp_plane->get_passengers();
	m_tmp_plane->set_passengers(0);
	cout << "         Unloaded: " << tmp_ppl_unloaded << " passengers" << endl;
}

void Airport::refuel(Samolot* m_tmp_plane)
{
	m_tmp_plane->set_fuel(1.00);
	cout << "         Refueled plane with index: " << m_tmp_plane->get_plane_index() << endl;
}

void Airport::repair(Samolot* m_tmp_plane)  //if plane maintenance below 80% repair it
{
	if (m_tmp_plane->get_tech_state() < 0.8)
	{
		m_tmp_plane->set_tech_state(1.00);
		cout << "         Repaired plane with index: " << m_tmp_plane->get_plane_index() << endl;
	}
	else
	{
		cout << "         No maintenance needed for plane: " << m_tmp_plane->get_plane_index() << endl;
	}
}

void Airport::take_off(Samolot* m_tmp_plane)
{
	int dest_index = m_tmp_plane->get_dest();
	m_tmp_plane->set_status(flying);
	int plane_index = m_tmp_plane->get_plane_index();
	cout << "Reassigning plane no: " << plane_index  << " from: " << m_index_ap << " to: " << dest_index << endl;
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

// int wait_in_hangar(int how_long, int how_long_left)
//     {
//         //sleep for x ticks, x1 - trackers of sleept time
//     }