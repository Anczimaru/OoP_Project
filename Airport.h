#ifndef AIRPORT_H
#define AIRPORT_H

#include "pch.h"
#include "Samolot.h"
#include "Tower.h"
#include "Point.h"
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>
#include <cmath>
#include <list>
#include <map>


using namespace std;


class Airport;

extern vector <Airport*> lotniska;
extern vector <time_t> EventSchedule;



class Airport
{
private:
	int m_index_ap; //index of airport
	int m_waiting_ppl;
	map <int, std::shared_ptr<Samolot>> przypisane_samoloty;
	list<int> que;
	int m_no_lines;
	Tower m_tower;
	Point m_position;

public:
	Airport();
	Airport(const Airport &airport);
	Airport(double x, double y,int lanes);
	~Airport();

	//List of priority plane indexes


	//Plane manipulation
	void register_plane(std::shared_ptr<Samolot>m_tmp_plane);
	void do_routine_on_plane(Samolot * m_tmp_plane);
	void do_routine();
	void land(Samolot * m_tmp_plane);
	void service(Samolot * m_tmp_plane);
	void take_off(Samolot * m_tmp_plane);

	//Lane operations
	bool reserve_lane(Samolot* tmp_plane);
	void release_lane(Samolot* tmp_plane);
	void prioritize(Samolot* tmp_plane);
	void register_lane(std::shared_ptr<Samolot>tmp_plane);

	//Getters
	Point get_position();
	int get_airport_index();
	int get_airport_size();
	int get_flight_time(int dest_index, int plane_index, int set);
	double get_distane_from(int dest_index);
	void show_occupancy();
	int get_que_size();
	void show_que();
};


#endif
