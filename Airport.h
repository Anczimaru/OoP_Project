#pragma once
#include "pch.h"
#include "Samolot.h"
#include <vector>
#include <iostream>
#include <memory>
#include <ctime>

using namespace std;
class Airport;


extern vector <Airport*> lotniska;
extern vector <time_t> EventSchedule;

class Airport
{
private:
	int m_index_ap; //index of airport
	int m_waiting_ppl;
	vector <std::shared_ptr<Samolot>> przypisane_samoloty;

public:
	Airport();
	Airport(const Airport &airport);
	~Airport();
	void register_plane(Samolot * m_tmp_plane);
	void do_routine_on_plane(Samolot * m_tmp_plane);
	void do_routine();
	void land(Samolot * m_tmp_plane);
	void load(Samolot * m_tmp_plane);
	void unload(Samolot * m_tmp_plane);
	void refuel(Samolot * m_tmp_plane);
	void repair(Samolot * m_tmp_plane);
	void take_off(Samolot * m_tmp_plane);
	

};
