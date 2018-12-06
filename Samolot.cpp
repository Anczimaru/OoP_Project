#include "pch.h"
#include "Samolot.h"
#include <iostream>
#include <vector>

using namespace std;

//Global variables for indexing
time_t init_time = 960420420;
time_t current_time = init_time;
vector <Samolot*> samoloty;
vector <time_t> EventSchedule;

//Constructor
Samolot::Samolot() :m_dest(1), m_src(2), m_capacity(80), m_passengers(60), m_status(flying), m_fuel(0.78), m_tech_state(0.99), m_index(samoloty.size()+1)
{
	samoloty.push_back(this);
	EventSchedule.push_back(init_time);
	cout <<	"Im plane with no:"<<m_index<<endl;
}

//Copying constructor
Samolot::Samolot(const Samolot &tmp_plane) :
	m_dest(tmp_plane.m_dest), m_src(tmp_plane.m_src), m_capacity(tmp_plane.m_capacity), m_passengers(tmp_plane.m_passengers),
	m_status(tmp_plane.m_status), m_fuel(tmp_plane.m_fuel), m_tech_state(tmp_plane.m_tech_state), m_index(tmp_plane.m_index)
{
	cout << "   Copying glorious plane with index: " << m_index << endl;
}


Samolot::~Samolot()
{
	//cout << "Usuwam kurwa samolot\n";
}


//FUNCTIONS
void Samolot:: fly_to_airport()
{
	cout << "Hi, Im plane number: " << m_index << "\tIm flying to: " << m_dest << "\tfrom: " << m_src << endl;
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

//PASSENGERS
int Samolot::get_capacity()
{
	return m_capacity;
}
int Samolot::get_passengers()
{
	return m_passengers;
}
void Samolot::set_passengers(int target_passengers)
{
	m_passengers = target_passengers;
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

////////////////////////////////   Czy potrzebujemy dw�ch funckji set_status() ???/////////////////////////////
status_t Samolot::get_status()
{
	return m_status;
}
void Samolot::set_status(status_t tmp_status)
{
	m_status = tmp_status;
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

