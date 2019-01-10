#ifndef SAMOLOT_H
#define SAMOLOT_H
#include <iostream>
#include <vector>
#include <memory>

typedef enum {
	/*
	1 - flying, 2 - waiting, 3 - landing, 4 - unloading, 5 - repairs, 6 - refueling, 7 - loading, 8 - departing, 9 - hangar
	*/
	flying = 1,
	waiting = 2,
	landing = 3,
	unloading = 4,
	repairing = 5,
	refueling = 6,
	loading = 7,
	departing = 8,
	flying_away = 9
}status_t;

using namespace std;
class Samolot;
extern vector <shared_ptr<Samolot>> samoloty;
extern time_t init_time;
extern time_t current_time;
extern vector <time_t> EventSchedule;
extern int debug;


class Samolot
{
private:
	int m_dest, m_src; //indexes of airports
	int m_passengers; //no of passengers
	int m_capacity; // capacity of num of passengers
	int m_gate; //index of m_gate
	int m_index; //index of airplane
	/*
	1 - flying, 2 - waiting, 3 - landing, 4 - unloading, 5 - maintenance, 6 - repairs, 7 - refueling, 8 - loading, 9 - departing, 10 - hangar
	*/
	int m_ap_index;
	int m_airline; //index of airline
	int m_airstrip; // index of airstrip
	int m_speed; //velovity of a plane
	double m_fuel; // percentage of fuel in airplane
	double m_tech_state; //percentage of airplane maintenance
	status_t m_status;
public:
	Samolot();
	Samolot(double fuel, double tech);
	Samolot(Samolot* tmp_plane);
	~Samolot();
	void fly_to_airport();
	int get_dest();
	void set_dest(int target_dest);
	void set_src(int src);
	int get_src();
	void whereAmI();
	void whatAmIDoing();
	int get_plane_index();
	int get_ap_index();
	void set_ap_index(int index);
	int get_capacity();
	int get_passengers();
	void set_passengers(int target_passengers);
	double get_fuel();
	void set_fuel(double target_fuel);
	double get_tech_state();
	void set_tech_state(double target_state);
	status_t get_status();
	void set_status(status_t tmp_status);
	bool call_emergency();
	int get_speed();
	/*void set_status(int i);
	void increment_status();*/
	
};
#endif