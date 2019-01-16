#include "pch.h"
#include "Samolot.h"
#include <iostream>
#include <vector>

using namespace std;

//Global variables for indexing
time_t init_time = 960420420;
time_t current_time = init_time;
vector <shared_ptr<Samolot>> samoloty;
vector <time_t> EventSchedule;
int debug;


status_t RandomizeStatus()
{
	return (status_t)(1 + rand() % 6);
}

//Constructor
Samolot::Samolot() : m_dest(2), m_src(1), m_status(flying),  m_fuel(0.9), m_tech_state(0.8), m_index(samoloty.size()+1),m_ap_index(1), m_speed(10)
{
	cout << "Created plane with no:" << m_index << endl;
	samoloty.push_back(make_shared<Samolot>(this));
	EventSchedule.push_back(init_time);
	//cout <<	"Im plane with no:"<<m_index<<endl;
}
Samolot::Samolot(double fuel, double tech) :m_dest(2), m_src(1), m_status(), m_fuel(fuel), m_tech_state(tech), m_index(samoloty.size() + 1), m_ap_index(1), m_speed(10)
{
	cout << "Created plane with no:" << m_index << endl;
	samoloty.push_back(make_shared<Samolot>(this));
	EventSchedule.push_back(init_time);
	//cout << "Im plane with no:" << m_index << endl;
}

//COPYING CONSTRUTOR
Samolot::Samolot(Samolot* tmp_plane) :
		m_dest(tmp_plane->get_dest()), m_src(tmp_plane->get_src()), m_status(tmp_plane->get_status()), m_fuel(tmp_plane->get_fuel()),
		m_tech_state(tmp_plane->get_tech_state()), m_index(tmp_plane->get_plane_index()), m_ap_index(tmp_plane->get_ap_index()),m_speed(tmp_plane->get_speed())
{
	if (debug == 1)
		cout << "   Copying glorious plane with index: " << m_index << endl;
}

Samolot::~Samolot()
{
	if (debug == 1) cout << "Destroying plane no: " << m_index << endl;
}


//FUNCTIONS
void Samolot:: fly_to_airport()
{
	if (debug == 1) cout << "Hi, Im plane number: " << m_index << "\tIm flying to: " << m_dest << "\tfrom: " << m_src << endl;
}

//SETTERS AND GETTERS section
//DESTINATION
void Samolot::set_dest(int target_dest)
{
	m_dest = target_dest;
}
int Samolot::get_dest()
{
	return m_dest;
}

//SOURCE
void Samolot:: set_src(int src)
{
	m_src = src;
}
int Samolot::get_src()
{
	return m_src;
}

//INDEX
int Samolot::get_plane_index()
{
	return m_index;
}
int Samolot::get_ap_index()
{
	return m_ap_index;
}
void Samolot::set_ap_index(int index)
{
	m_ap_index = index;
}

//FUEL AND TECH STATE
double Samolot::get_fuel()
{
	return m_fuel;
}
void Samolot::set_fuel(double target_fuel)
{
	m_fuel = target_fuel;
}
double Samolot::get_tech_state()
{
	return m_tech_state;
}
void Samolot::set_tech_state(double target_state)
{
	m_tech_state = target_state;
}

//STATUS OF PLANE
status_t Samolot::get_status()
{
	return m_status;
}
void Samolot::set_status(status_t tmp_status)
{
	m_status = tmp_status;
}

int Samolot::get_speed()
{
	return m_speed;
}
//TEST FUNCTION
void Samolot::whereAmI()
{
	//Do test�w
	cout << "Im located at: " << m_src << endl;
}
void Samolot::whatAmIDoing()
{
	cout<<"I'm "<<get_status()<<" ,my dest "<<get_dest()<<" ,from "<<get_src()<<endl;


}
bool Samolot::call_emergency()
{

	if ((get_fuel()<= 0.5) || (get_tech_state() <= 0.75))
	{
		cout << "!!!Emergency calling for plane: " <<get_plane_index()<< endl;
		set_status(waiting);
		return true;
	}
	else
	{
		if (debug == 1) cout << "No emergency for plane: " << get_plane_index() << endl;
		return false;
	}
}
